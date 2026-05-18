# 🌊 SchooMy フーリエ変換ラボ v1.0

スクーミーオレンジボードのセンサー値を Web Serial API で取り込み、ブラウザ上で **「元の波形 → スペクトル → 分解 sin 波」** の 3 つを同時にリアルタイム表示する Web アプリです。

> 「ギザギザの振動 = 綺麗な sin 波たちの合成」をその場で見て体感する授業ツール。

## 公開URL

**https://shiojima-test.github.io/fourier-lab/**

## 何が見られるか

1. **① 元の波形** — オレンジボードから届いた直近 2 秒間の生データ
2. **② スペクトル** — FFT 結果 (周波数 vs 強度)、最大ピークをオレンジで強調
3. **③ 分解 sin 波** — 上位 3 本の sin 波と、それを足し合わせた合成波 (破線)

③ の破線 (合成波) と ① の波形がほぼ同じ形になることが、フーリエ変換の本質体験です。

## 使い方 (生徒向け)

1. オレンジボードに対応スケッチ ([`sketches/`](./sketches/) 参照) を **スクーミーIDE** で書き込む
2. オレンジボードを PC と USB ケーブルで接続
3. **Chrome / Edge** で [https://shiojima-test.github.io/fourier-lab/](https://shiojima-test.github.io/fourier-lab/) を開く
4. 上部のセンサー選択ピル (🔊音 / 📈加速度 / 💡明るさ / 🧲磁気) からスケッチに対応するものを選ぶ
5. 「🔌 USB接続」を押してポートを選ぶ
6. 3 つのグラフが 0.5 秒ごとに自動更新される。センサーを叩いたり光を当てたりして波形を変えてみよう

## 4 種類のスケッチ

| センサー | スケッチ |
|---|---|
| 音 | [sketches/sound.ino](./sketches/sound.ino) |
| 加速度 (MPU6050) | [sketches/accelerometer.ino](./sketches/accelerometer.ino) |
| 明るさ (CdS) | [sketches/brightness.ino](./sketches/brightness.ino) |
| 磁気 | [sketches/magnet.ino](./sketches/magnet.ino) |

すべて 9600 bps、改行区切りで 1 行 1 値を送信します。ブラウザ側はその数値を読み取って 3 つのグラフを描画します。

## 対応ブラウザ

Web Serial API 対応のものに限ります。

| ブラウザ | 対応 |
|---|---|
| Chrome (PC / Mac / Chromebook) | ✅ |
| Edge (PC / Mac) | ✅ |
| Opera (PC) | ✅ |
| Safari / Firefox | ❌ |
| iOS / Android スマートフォン | ❌ |

## 内部仕様 (技術メモ)

- 受信したサンプルは `{value, t (performance.now)}` で直近 5 秒分リングバッファに保持
- 0.5 秒ごとに直近 2 秒分のサンプルを取り出し、平均サンプリング間隔から **実効サンプリングレート fs** を算出
- 2 秒間を fs に合わせて等間隔化 (線形補間) → 平均値を引いて中心化 → Hann 窓 → FFT (Cooley-Tukey radix-2, N = 256/512/1024 から自動選択)
- FFT 結果から上位 3 本のピーク (隣接ビンは局所極大に圧縮) を抽出し、`A_k cos(2π f_k t + φ_k)` で sin 波を再構築
- スペクトルは振幅の最大値で正規化したリニア相対表示。位相・対数軸は表示しない (シンプル維持)

## バージョン履歴

- **v1.0 (2026-05)** 初版リリース。音・加速度・明るさ・磁気の 4 センサに対応。リアルタイム波形・スペクトル・分解 sin 波の 3 連表示。

## ライセンス

MIT License © スクーミー株式会社 (SchooMy, Inc.)
