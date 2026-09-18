<div align="center">

# 竜の道 — RYŪ: THE DRAGON WAY

**セガメガドライブ／Genesis向け 和風レトロ・スネークアーケード**

[![Build Sega Genesis ROM](https://github.com/your-username/ryu-genesis/actions/workflows/build.yml/badge.svg)](https://github.com/your-username/ryu-genesis/actions/workflows/build.yml)
![Platform](https://img.shields.io/badge/Platform-Sega%20Genesis%20%2F%20Mega%20Drive-000000.svg?style=flat-square&logo=sega)
![Language](https://img.shields.io/badge/Language-C%20%2F%20SGDK-red.svg?style=flat-square)
![License](https://img.shields.io/badge/License-MIT-blue.svg?style=flat-square)

<p align="center">
  <i>古の龍となり、知恵の宝珠を喰らい、果てなき道を昇天せよ。</i>
</p>

---

</div>

## ⛩️ 概要

**『竜の道』(RYŪ)** は、Motorola 68000 (16-bit) アーキテクチャ向けに **SGDK (Sega Genesis Development Kit)** を用いて開発された、メガドライブ専用の古典的スネークゲームです。

プレイヤーは神聖なる蒼龍を操り、盤上に現れる「知恵の宝珠」を集めて身体を成長させます。自身の尾や境界に触れることなく、最高得点を目指してください。

---

## 🎮 操作方法

メガドライブ標準の3ボタン／6ボタンパッドに対応しています。

| ボタン | 動作 |
| :--- | :--- |
| **十字キー (D-Pad)** | 龍の移動方向を変更（上下左右） |
| **START ボタン** | ゲームオーバー時の再挑戦・リセット |

> **心得:** 進行方向と正反対への急旋回はできません。

---

## 📁 ディレクトリ構成

```text
.
├── .github/
│   └── workflows/
│       └── build.yml       # 自動ビルド用 GitHub Actions CI
├── inc/                    # ヘッダーファイル (.h)
├── res/                    # リソース定義ファイル (.res / 画像・音源)
├── src/
│   └── main.c              # ゲーム本編ソースコード
└── README.md
