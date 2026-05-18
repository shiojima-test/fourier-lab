// SchooMy フーリエ変換ラボ — 音センサ用スケッチ
// オレンジボードの A5 にスクーミー音センサーを接続して、analogRead 値を
// 1 行 1 サンプルで 9600 bps シリアル送信する。
// ブラウザ側 (https://shiojima-test.github.io/fourier-lab/) の
// 「音」ピルを選んで「USB接続」ボタンから接続する。

#include <SchooMyUtilities.h>
SchooMyUtilities scmUtils = SchooMyUtilities();

void setup() {
  Serial.begin(9600);
  scmUtils.soundSensorBegin(A5);
}

void loop() {
  Serial.println(analogRead(A5));
}
