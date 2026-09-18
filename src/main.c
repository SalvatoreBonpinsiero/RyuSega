#include <genesis.h>

#define BOARD_X      2
#define BOARD_Y      3
#define BOARD_W      36
#define BOARD_H      22
#define MAX_LEN      256

#define TILE_EMPTY   0
#define TILE_BORDER  1
#define TILE_HEAD    2
#define TILE_BODY    3
#define TILE_TAIL    4
#define TILE_PEARL   5
#define TILE_PETAL   6

typedef struct {
    s16 x;
    s16 y;
} Point;

typedef enum {
    DIR_UP,
    DIR_DOWN,
    DIR_LEFT,
    DIR_RIGHT
} Direction;

static Point snake[MAX_LEN];
static u16 snake_len = 4;
static Direction dir = DIR_RIGHT;
static Direction next_dir = DIR_RIGHT;
static Point pearl;
static u32 score = 0;
static u16 combo = 0;
static bool game_over = false;
static u16 scroll_offset = 0;

static const u16 anime_palettes[64] = {
    0x0000, 0x0211, 0x0422, 0x0633, 0x0844, 0x0A55, 0x0D77, 0x0FFF,
    0x0224, 0x0448, 0x066C, 0x088E, 0x0527, 0x0739, 0x0A5C, 0x0E9F,
    0x0000, 0x0040, 0x0080, 0x00C0, 0x00E4, 0x02F8, 0x08FC, 0x0CFF,
    0x002A, 0x004E, 0x027E, 0x06BE, 0x00EE, 0x04FE, 0x08FE, 0x0FFF,
    0x0000, 0x0204, 0x0408, 0x081E, 0x0A3F, 0x0D7F, 0x0FAF, 0x0FFF,
    0x004E, 0x008F, 0x02BF, 0x04EF, 0x08EE, 0x0CEE, 0x0EEE, 0x0FFF,
    0x0000, 0x0002, 0x0006, 0x000A, 0x000E, 0x022E, 0x046E, 0x06AE,
    0x006E, 0x00AE, 0x02EF, 0x04FF, 0x08FF, 0x0CFF, 0x0EFF, 0x0FFF
};

static void load_custom_tiles(void) {
    static const u32 border_tile[8] = {
        0x33333333, 0x31111113, 0x31222213, 0x31200213,
        0x31200213, 0x31222213, 0x31111113, 0x33333333
    };
    static const u32 head_tile[8] = {
        0x01000010, 0x03100130, 0x13311331, 0x13733731,
        0x13733731, 0x03333330, 0x01322310, 0x00111100
    };
    static const u32 body_tile[8] = {
        0x00222200, 0x02111120, 0x21333312, 0x21377312,
        0x21377312, 0x21333312, 0x02111120, 0x00222200
    };
    static const u32 tail_tile[8] = {
        0x00022000, 0x00233200, 0x02311320, 0x02311320,
        0x00233200, 0x00022000, 0x00011000, 0x00000000
    };
    static const u32 pearl_tile[8] = {
        0x00122100, 0x01233210, 0x02333320, 0x02332110,
        0x01221000, 0x00110000, 0x00011000, 0x00000000
    };

    VDP_loadTileData(border_tile, TILE_BORDER, 1, CPU);
    VDP_loadTileData(head_tile,   TILE_HEAD,   1, CPU);
    VDP_loadTileData(body_tile,   TILE_BODY,   1, CPU);
    VDP_loadTileData(tail_tile,   TILE_TAIL,   1, CPU);
    VDP_loadTileData(pearl_tile,  TILE_PEARL,  1, CPU);
}

static void sfx_eat(void) {
    PSG_setFrequency(0, 1100);
    PSG_setEnvelope(0, 15);
    PSG_setFrequency(1, 1450);
    PSG_setEnvelope(1, 15);
}

static void sfx_crash(void) {
    PSG_setFrequency(0, 150);
    PSG_setEnvelope(0, 15);
    PSG_setFrequency(1, 90);
    PSG_setEnvelope(1, 15);
}

static void sfx_silence(void) {
    PSG_setEnvelope(0, 0);
    PSG_setEnvelope(1, 0);
    PSG_setEnvelope(2, 0);
    PSG_setEnvelope(3, 0);
}

static void draw_tile(u16 x, u16 y, u16 tile_idx, u16 pal) {
    VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(pal, FALSE, FALSE, FALSE, tile_idx), x, y);
}

static void spawn_pearl(void) {
    bool collides;
    do {
        collides = false;
        pearl.x = BOARD_X + (random() % BOARD_W);
        pearl.y = BOARD_Y + (random() % BOARD_H);

        for (u16 i = 0; i < snake_len; i++) {
            if (snake[i].x == pearl.x && snake[i].y == pearl.y) {
                collides = true;
                break;
            }
        }
    } while (collides);

    draw_tile(pearl.x, pearl.y, TILE_PEARL, PAL2);
}

static void update_hud(void) {
    char str[32];
    VDP_setTextPalette(PAL2);
    VDP_drawText("== RYUJIN DEN: 龍神伝 ==", 8, 1);

    sprintf(str, "KI: %06ld", score);
    VDP_setTextPalette(PAL1);
    VDP_drawText(str, 2, 26);

    sprintf(str, "COMBO: x%02d", combo);
    VDP_setTextPalette(PAL3);
    VDP_drawText(str, 28, 26);
}

static void screen_shake(void) {
    for (u16 i = 0; i < 6; i++) {
        VDP_setHorizontalScroll(BG_A, (i % 2 == 0) ? 6 : -6);
        SYS_doVBlankProcess();
    }
    VDP_setHorizontalScroll(BG_A, 0);
}

static void init_stage(void) {
    VDP_clearPlane(BG_A, TRUE);
    VDP_clearPlane(BG_B, TRUE);

    for (u16 x = BOARD_X - 1; x <= BOARD_X + BOARD_W; x++) {
        draw_tile(x, BOARD_Y - 1, TILE_BORDER, PAL3);
        draw_tile(x, BOARD_Y + BOARD_H, TILE_BORDER, PAL3);
    }
    for (u16 y = BOARD_Y; y < BOARD_Y + BOARD_H; y++) {
        draw_tile(BOARD_X - 1, y, TILE_BORDER, PAL3);
        draw_tile(BOARD_X + BOARD_W, y, TILE_BORDER, PAL3);
    }

    update_hud();
}

static void reset_game(void) {
    sfx_silence();
    snake_len = 4;
    dir = DIR_RIGHT;
    next_dir = DIR_RIGHT;
    score = 0;
    combo = 0;
    game_over = false;

    init_stage();

    s16 sx = BOARD_X + 8;
    s16 sy = BOARD_Y + 10;
    for (u16 i = 0; i < snake_len; i++) {
        snake[i].x = sx - i;
        snake[i].y = sy;
        u16 tile = (i == 0) ? TILE_HEAD : ((i == snake_len - 1) ? TILE_TAIL : TILE_BODY);
        draw_tile(snake[i].x, snake[i].y, tile, PAL1);
    }

    spawn_pearl();
}

int main() {
    VDP_init();
    PAL_setColors(0, anime_palettes, 64, CPU);
    load_custom_tiles();

    reset_game();

    u16 frame = 0;
    u16 sfx_timer = 0;

    while (1) {
        u16 joy = JOY_readJoypad(JOY_1);

        if (!game_over) {
            if ((joy & BUTTON_UP) && dir != DIR_DOWN)    next_dir = DIR_UP;
            if ((joy & BUTTON_DOWN) && dir != DIR_UP)    next_dir = DIR_DOWN;
            if ((joy & BUTTON_LEFT) && dir != DIR_RIGHT) next_dir = DIR_LEFT;
            if ((joy & BUTTON_RIGHT) && dir != DIR_LEFT) next_dir = DIR_RIGHT;
        } else {
            if (joy & BUTTON_START) {
                reset_game();
            }
        }

        scroll_offset++;
        VDP_setHorizontalScroll(BG_B, scroll_offset >> 1);

        if (sfx_timer > 0) {
            sfx_timer--;
            if (sfx_timer == 0) sfx_silence();
        }

        if (!game_over && (++frame >= 5)) {
            frame = 0;
            dir = next_dir;

            Point next_head = snake[0];
            switch (dir) {
                case DIR_UP:    next_head.y--; break;
                case DIR_DOWN:  next_head.y++; break;
                case DIR_LEFT:  next_head.x--; break;
                case DIR_RIGHT: next_head.x++; break;
            }

            if (next_head.x < BOARD_X || next_head.x >= BOARD_X + BOARD_W ||
                next_head.y < BOARD_Y || next_head.y >= BOARD_Y + BOARD_H) {
                game_over = true;
            }

            for (u16 i = 0; i < snake_len && !game_over; i++) {
                if (next_head.x == snake[i].x && next_head.y == snake[i].y) {
                    game_over = true;
                }
            }

            if (game_over) {
                sfx_crash();
                sfx_timer = 30;
                screen_shake();

                VDP_setTextPalette(PAL3);
                VDP_drawText(">>> ANATA WA SHINDA <<<", 8, 11);
                VDP_setTextPalette(PAL0);
                VDP_drawText("PRESS [START] TO REINCARNATE", 6, 13);
            } else {
                bool ate = (next_head.x == pearl.x && next_head.y == pearl.y);

                if (!ate) {
                    draw_tile(snake[snake_len - 1].x, snake[snake_len - 1].y, TILE_EMPTY, PAL0);
                } else {
                    if (snake_len < MAX_LEN) snake_len++;
                    combo++;
                    score += 100 * combo;
                    sfx_eat();
                    sfx_timer = 8;
                    update_hud();
                    spawn_pearl();
                }

                for (s16 i = snake_len - 1; i > 0; i--) {
                    snake[i] = snake[i - 1];
                }
                snake[0] = next_head;

                draw_tile(snake[0].x, snake[0].y, TILE_HEAD, PAL1);
                if (snake_len > 1) {
                    draw_tile(snake[1].x, snake[1].y, TILE_BODY, PAL1);
                }
                if (snake_len > 2) {
                    draw_tile(snake[snake_len - 1].x, snake[snake_len - 1].y, TILE_TAIL, PAL1);
                }
            }
        }

        SYS_doVBlankProcess();
    }

    return 0;
}
