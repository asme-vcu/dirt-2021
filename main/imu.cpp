/* IMU Sensor Submodule Implementation */
#include"imu.h"
#include"consts.h"

IMU::IMU() {
	mpu = Adafruit_MPU6050();
}

void IMU::setup() {
#if MPU_ENABLED
	// Begin MPU setup & calibration

	while(!mpu.begin()) {
		Serial.println("Searching for MPU6050...");
		delay(10);
	}
	Serial.println("MPU6050 Found!");

	// Set accelerometer range

	mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
	Serial.print("Accelerometer range set to: ");
	switch (mpu.getAccelerometerRange()) {
	case MPU6050_RANGE_2_G:
		Serial.println("+-2G");
		break;
	case MPU6050_RANGE_4_G:
		Serial.println("+-4G");
		break;
	case MPU6050_RANGE_8_G:
		Serial.println("+-8G");
		break;
	case MPU6050_RANGE_16_G:
		Serial.println("+-16G");
		break;
	}

	// Set Gyroscope range

	mpu.setGyroRange(MPU6050_RANGE_500_DEG);
	Serial.print("Gyro range set to: ");
	switch (mpu.getGyroRange()) {
	case MPU6050_RANGE_250_DEG:
		Serial.println("+- 250 deg/s");
		break;
	case MPU6050_RANGE_500_DEG:
		Serial.println("+- 500 deg/s");
		break;
	case MPU6050_RANGE_1000_DEG:
		Serial.println("+- 1000 deg/s");
		break;
	case MPU6050_RANGE_2000_DEG:
		Serial.println("+- 2000 deg/s");
		break;
	}

	// Set filter bandwidth

	mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
	Serial.print("Filter bandwidth set to: ");
	switch (mpu.getFilterBandwidth()) {
	case MPU6050_BAND_260_HZ:
		Serial.println("260 Hz");
		break;
	case MPU6050_BAND_184_HZ:
		Serial.println("184 Hz");
		break;
	case MPU6050_BAND_94_HZ:
		Serial.println("94 Hz");
		break;
	case MPU6050_BAND_44_HZ:
		Serial.println("44 Hz");
		break;
	case MPU6050_BAND_21_HZ:
		Serial.println("21 Hz");
		break;
	case MPU6050_BAND_10_HZ:
		Serial.println("10 Hz");
		break;
	case MPU6050_BAND_5_HZ:
		Serial.println("5 Hz");
		break;
	}
#endif
}

void IMU::run() {
	mpu.getEvent(&acc, &gyro, &temp);
}

float IMU::getPitch() {
	return 0;
}

float IMU::getYaw() {
	return 0;
}

float IMU::getRoll() {
	return 0;
}

uint16_t IMU::getAccelX() {
	return 0;
}

uint16_t IMU::getAccelY() {
	return 0;
}

uint16_t IMU::getAccelZ() {
	return 0;
}

void IMU::printDebug() {
	Serial.print("Angular Velocity X: ");
	Serial.print(gyro.gyro.x);
	Serial.print(" Y: ");
	Serial.print(gyro.gyro.y);
	Serial.print(" Z: ");
	Serial.print(gyro.gyro.z);
	Serial.println(" rad/s");

	Serial.print("Acceleration X: ");
	Serial.print(acc.acceleration.x);
	Serial.print(" Y: ");
	Serial.print(acc.acceleration.y);
	Serial.print(" Z: ");
	Serial.print(acc.acceleration.z);
	Serial.println(" m/s^2");

	Serial.print("Temperature: ");
	Serial.print(temp.temperature);
	Serial.println(" degC");
}
