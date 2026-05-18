// SchooMy フーリエ変換ラボ — 磁気センサ用スケッチ
// A5 に磁気センサを接続し、analogRead 値を 1 行 1 サンプルで
// 9600 bps シリアル送信する。
// ブラウザ側 (https://shiojima-test.github.io/fourier-lab/) の
// 「磁気」ピルを選んで「USB接続」ボタンから接続する。

#include <SchooMyUtilities.h>
SchooMyUtilities scmUtils = SchooMyUtilities();

void setup() {
  Serial.begin(9600);
  pinMode(A5, INPUT);
}

void loop() {
  Serial.println(analogRead(A5));
}
