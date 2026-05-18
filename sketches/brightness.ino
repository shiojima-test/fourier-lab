// SchooMy フーリエ変換ラボ — 明るさセンサ用スケッチ
// CdS セルから kΩ 換算した明るさ値を 9600 bps シリアル送信する。
// ブラウザ側 (https://shiojima-test.github.io/fourier-lab/) の
// 「明るさ」ピルを選んで「USB接続」ボタンから接続する。

#include <SchooMyUtilities.h>
SchooMyUtilities scmUtils = SchooMyUtilities();

float _sbeGetBrightness(int pinNumber, int res, float vol) {
  pinMode(pinNumber, INPUT);
  float cds_ad = analogRead(pinNumber);
  float cds_v = cds_ad * vol / res;
  float v_res = vol - cds_v;
  if (v_res < 0.01) {
    v_res = 0.01;
  }
  return 10000 * cds_v / v_res / 1000;
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println(_sbeGetBrightness(A5, 1023, 5));
}
