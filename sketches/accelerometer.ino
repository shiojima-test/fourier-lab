// SchooMy フーリエ変換ラボ — 加速度・角度センサ (MPU6050) 用スケッチ
// I2C で MPU6050 を読み、3 軸合成の加速度絶対値を 9600 bps シリアル送信する。
// ブラウザ側 (https://shiojima-test.github.io/fourier-lab/) の
// 「加速度」ピルを選んで「USB接続」ボタンから接続する。

#include <SchooMyUtilities.h>
#include <Wire.h>
SchooMyUtilities scmUtils = SchooMyUtilities();

int MPU6050_ADDR = 0x68;
#define MPU6050_SMPLRT_DIV   0x19
#define MPU6050_CONFIG       0x1a
#define MPU6050_GYRO_CONFIG  0x1b
#define MPU6050_ACCEL_CONFIG 0x1c
#define MPU6050_PWR_MGMT_1   0x6b
int16_t raw_acc_x, raw_acc_y, raw_acc_z, raw_t, raw_gyro_x, raw_gyro_y, raw_gyro_z;
float acc_x, acc_y, acc_z, acc_angle_x, acc_angle_y;
float absAccelerometer;

void accelerometerWireRead() {
  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU6050_ADDR, 14, true);
  raw_acc_x = Wire.read() << 8 | Wire.read();
  raw_acc_y = Wire.read() << 8 | Wire.read();
  raw_acc_z = Wire.read() << 8 | Wire.read();
  raw_t = Wire.read() << 8 | Wire.read();
  raw_gyro_x = Wire.read() << 8 | Wire.read();
  raw_gyro_y = Wire.read() << 8 | Wire.read();
  raw_gyro_z = Wire.read() << 8 | Wire.read();
}

void accelerometerAddressSetup() {
  byte error, address;
  int nDevices = 0;
  for (address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0) {
      if (address < 16) MPU6050_ADDR = address;
      nDevices++;
    }
  }
}

void calcAcceleration() {
  acc_x = ((float)raw_acc_x) / 16384.0;
  acc_y = ((float)raw_acc_y) / 16384.0;
  acc_z = ((float)raw_acc_z) / 16384.0;
  absAccelerometer = pow(pow(acc_x, 2) + pow(acc_y, 2) + pow(acc_z, 2), 0.5);
}

void accelerometerAccelerationSetup() {
  accelerometerAddressSetup();
  accelerometerWireRead();
  calcAcceleration();
}

float acceleration() {
  accelerometerWireRead();
  calcAcceleration();
  return absAccelerometer;
}

void setup() {
  Serial.begin(9600);
  Wire.begin();
  accelerometerAccelerationSetup();
}

void loop() {
  Serial.println(acceleration());
}
