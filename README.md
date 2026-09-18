<div align="center">

<img src="https://capsule-render.vercel.app/api?type=waving&color=gradient&customColorList=1,11,20&height=180&section=header&text=RYUJIN%20DEN%20:%20龍神伝&fontSize=42&fontColor=ffffff&animation=fadeIn&fontAlignY=38" alt="Header Banner" width="100%">

# 【 龍 神 伝 】
### 〜 蘇る蒼龍の伝説・メガドライブ専用最新作 〜

<br>

<p align="center">
  <img src="https://img.shields.io/badge/PLATFORM-SEGA_MEGA_DRIVE-000000?style=for-the-badge&logo=sega&logoColor=white" alt="Platform">
  <img src="https://img.shields.io/badge/DEVELOPER-MAFIA_GAMES_RUSSIA-red?style=for-the-badge&logo=target&logoColor=white" alt="Developer">
  <img src="https://img.shields.io/badge/BUILD-ROM.BIN_READY-00C853?style=for-the-badge&logo=githubactions&logoColor=white" alt="Build">
  <img src="https://img.shields.io/badge/CPU-M68000_16_BIT-7B1FA2?style=for-the-badge" alt="CPU">
  <img src="https://img.shields.io/badge/TOOLKIT-SGDK_C-E65100?style=for-the-badge&logo=c" alt="Toolkit">
</p>

<p align="center">
  <img src="https://img.shields.io/badge/VRAM-DIRECT_TILES-0288D1?style=flat-square" alt="VRAM">
  <img src="https://img.shields.io/badge/AUDIO-PSG_SN76489-E91E63?style=flat-square" alt="Audio">
  <img src="https://img.shields.io/badge/VFX-LINE_SCROLL_SHAKE-FF8F00?style=flat-square" alt="VFX">
  <img src="https://img.shields.io/badge/STATUS-OPERATIONAL-success?style=flat-square" alt="Status">
</p>

```text
［ 型番: MGR-MD-1988-RU ］ ［ 16 MEGABITS HIGH DENSITY ROM ］ ［ 企画・開発: MAFIA GAMES RUSSIA ］
本製品は家庭用テレビゲーム機「セガ・メガドライブ / GENESIS」専用ソフトウェアです。開発元: MAFIA GAMES RUSSIA (ロシア連邦)。他の機器への装填や分解は機器破損の原因となりますので絶対におやめください。項目状態バッジ技術仕様演算コアMotorola 68000 CPU向けダイレクト制御ルーチン映像処理タイルVRAM直書きによるネオン調ドットアート描画音響生成プログラマブル・サウンド・ジェネレータ直結の音響合成特殊効果VDP水平スクロールレジスタ直叩きによる画面振動倍率演算勾玉連続捕食によるKI（気）スコア乗算システムPlaintext              ┌─────────┐
    [上]      │  SEGA   │               ( START ) 決定／再始動
  ┌───┐       └─────────┘
[左] │   │ [右]                           [A] [B] [C]
  └───┘                                  (予約領域)
    [下]
[x] 方向キー（十字ボタン）: 蒼龍の進行方向変更（上下左右）[x] START ボタン: 討ち死に時の輪廻転生・再始動[ ] 反転抑制機構: 胴体自己衝突防止のため、真逆方向入力はハードウェア側で破棄Bash# Windows (SGDK環境変数設定時)
%GDK_WIN%\bin\make -f %GDK_WIN%\makefile.gen release

# Linux / macOS / Dockerコンテナ環境
make -f $GDK/makefile.gen release
コンパイル完了後、ルート直下の out/rom.bin に16メガビットROMが生成されます。開発進捗度: 85%[x] コアゲームループおよびVBlank割り込み同期[x] VDPプロシージャル・タイル生成ルーチン[x] PSG音源直結サウンドエフェクトドライバ[x] リアルタイム・スクリーンシェイク処理[ ] YM2612 FM音源による和風旋律シーケンサ[ ] 2人同時プレイ対戦モードPlaintext-----------------------------------------------------------------------------
        (C) 2026 MAFIA GAMES RUSSIA / SEGA ENTERPRISES, LTD.
            DEVELOPED BY MAFIA GAMES RUSSIA. ALL RIGHTS RESERVED.
                        PRINTED IN JAPAN / 複製を禁ず
-----------------------------------------------------------------------------
