/* IMU Sensor Submodule Implementation */
#include"imu.h"
#include"consts.h"

IMU::IMU(LEDController& leds) : _leds(leds) {
	_mpu = Adafruit_MPU6050();
}

void IMU::setup() {
#if MPU_ENABLED
	// Begin MPU setup & calibration

	pinMode(LED_IMU, OUTPUT);

	bool imuFound = false, blink = false;
	uint32_t imuTimer = millis(), debugTimer = imuTimer;
	
	// wait max 2 minutes
	_leds.imu().blink();
	while(millis() < imuTimer + 30*1000 && !imuFound) {
		// detect IMU
		if(_mpu.begin()) {
			imuFound = true;
		} else {
			_leds.run();
#if DEBUG_ENABLED
			// print info and blink LED
			if(millis() > debugTimer + 500) {
				debugTimer = millis();
				Serial.println("Searching for MPU6050...");
			}
#endif
		}
		delay(10);
	}

	// IMU Failed to initialize

	if(!imuFound) {
#if DEBUG_ENABLED
		Serial.println("MPU6050 Not Found...");
#endif
		_leds.imu().off();
		return;
	}

	// IMU is working at this point...
	_leds.imu().on();
	_enabled = imuFound;

#if DEBUG_ENABLED
	Serial.println("MPU6050 Found!");
#endif

	// Set accelerometer range

	_mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
	Serial.print("Accelerometer range set to: ");
	switch (_mpu.getAccelerometerRange()) {
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

	_mpu.setGyroRange(MPU6050_RANGE_500_DEG);
	Serial.print("Gyro range set to: ");
	switch (_mpu.getGyroRange()) {
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

	_mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
	Serial.print("Filter bandwidth set to: ");
	switch (_mpu.getFilterBandwidth()) {
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
	if(!_enabled) return;

	_mpu.getEvent(&_acc, &_gyro, &_temp);
}

float IMU::getPitch() {
	if(!_enabled) return 0;

	return 0;
}

float IMU::getYaw() {
	if(!_enabled) return 0;

	return 0;
}

float IMU::getRoll() {
	if(!_enabled) return 0;

	return 0;
}

float IMU::getAccelX() {
	if(!_enabled) return 0;

	return _acc.acceleration.x;
}

float IMU::getAccelY() {
	if(!_enabled) return 0;

	return _acc.acceleration.y;
}

float IMU::getAccelZ() {
	if(!_enabled) return 0;

	return _acc.acceleration.z;
}

float IMU::getVelocityX() {
	if(!_enabled) return 0;

	return _gyro.gyro.x;
}

float IMU::getVelocityY() {
	if(!_enabled) return 0;

	return _gyro.gyro.y;
}

float IMU::getVelocityZ() {
	if(!_enabled) return 0;

	return _gyro.gyro.z;
}

void IMU::printDebug() {
	if(!_enabled) return;

	Serial.println("[IMU Module]");
	
	Serial.print("Angular Velocity X: ");
	Serial.print(_gyro.gyro.x);
	Serial.print(" Y: ");
	Serial.print(_gyro.gyro.y);
	Serial.print(" Z: ");
	Serial.print(_gyro.gyro.z);
	Serial.println(" rad/s");

	Serial.print("Acceleration X: ");
	Serial.print(_acc.acceleration.x);
	Serial.print(" Y: ");
	Serial.print(_acc.acceleration.y);
	Serial.print(" Z: ");
	Serial.print(_acc.acceleration.z);
	Serial.println(" m/s^2");

	Serial.print("Temperature: ");
	Serial.print(_temp.temperature);
	Serial.println(" degC");
}

bool IMU::getEnabled() {
#if !MPU_ENABLED
	return false;
#else
	return _enabled;
#endif
}
