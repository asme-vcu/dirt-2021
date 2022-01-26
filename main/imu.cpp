/* IMU Sensor Submodule Implementation */
#include"imu.h"
#include"consts.h"

volatile bool IMU::mpuInterrupt = false;
IMU* IMU::instance = new IMU;

IMU* IMU::getInstance() {
    if(!instance) {
        instance = new IMU;
    }
    return instance;
}

IMU::IMU() {
    dmpReady = false;
    mpuInterrupt = false;
    mpu = new MPU6050(IMU_AD0_PIN ? 0x69 : 0x68);
}

void IMU::dmpDataReady() {
    mpuInterrupt = true;
}

void IMU::setup() {
    // join I2C bus (I2Cdev library doesn't do this automatically)
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
	Wire.begin();
	Wire.setClock(400000); // 400kHz I2C clock. Comment this line if having compilation difficulties
#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
	Fastwire::setup(400, true);
#endif

	// initialize device
	Serial.println(F("Initializing I2C devices..."));
	mpu->initialize();
	pinMode(IMU_INT_PIN, INPUT);
	
	delay(1000);

	// verify connection
	Serial.println(F("Testing device connections..."));

    goodConnection = mpu->testConnection();
	Serial.println(goodConnection ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));

    if(!goodConnection) {
        return;
    }

    // wait for ready
#if IMU_DMP_HLT
	Serial.println(F("\nSend any character to begin DMP programming and demo: "));
	while (Serial.available() && Serial.read()); // empty buffer
	while (!Serial.available()) {delay(100);}    // wait for data
	while (Serial.available() && Serial.read()); // empty buffer again
#endif

	// load and configure the DMP
	Serial.println(F("Initializing DMP..."));
	devStatus = mpu->dmpInitialize();

	// supply your own gyro offsets here, scaled for min sensitivity
	mpu->setXGyroOffset(65);
	mpu->setYGyroOffset(5);
	mpu->setZGyroOffset(26);
	mpu->setXAccelOffset(282);
	mpu->setYAccelOffset(-4542);
	mpu->setZAccelOffset(1002);
	// make sure it worked (returns 0 if so)
	if (devStatus == 0) {
		// Calibration Time: generate offsets and calibrate our MPU6050
		mpu->CalibrateAccel(6);
		mpu->CalibrateGyro(6);
		Serial.println();
		mpu->PrintActiveOffsets();
		// turn on the DMP, now that it's ready
		Serial.println(F("Enabling DMP..."));
		mpu->setDMPEnabled(true);

		// enable Arduino interrupt detection
		Serial.print(F("Enabling interrupt detection (Arduino external interrupt "));
		Serial.print(digitalPinToInterrupt(IMU_INT_PIN));
		Serial.println(F(")..."));
		attachInterrupt(digitalPinToInterrupt(IMU_INT_PIN), dmpDataReady, RISING);
		mpuIntStatus = mpu->getIntStatus();

		// set our DMP Ready flag so the main loop() function knows it's okay to use it
		Serial.println(F("DMP ready! Waiting for first interrupt..."));
		dmpReady = true;

		// get expected DMP packet size for later comparison
		packetSize = mpu->dmpGetFIFOPacketSize();
	} else {
		// ERROR!
		// 1 = initial memory load failed
		// 2 = DMP configuration updates failed
		// (if it's going to break, usually the code will be 1)
		Serial.print(F("DMP Initialization failed (code "));
		Serial.print(devStatus);
		Serial.println(F(")"));
	}
}

void IMU::run() {
    if(!goodConnection) return;

	// if programming failed, don't try to do anything
	if (!dmpReady) {
			Serial.print("DMP not ready...");
			return;
	}

    mpu->dmpGetCurrentFIFOPacket(fifoBuffer);
    
    mpu->dmpGetQuaternion(&q, fifoBuffer);
    mpu->dmpGetGravity(&gravity, &q);
    
    mpu->dmpGetYawPitchRoll(ypr, &q, &gravity);
    
    mpu->dmpGetAccel(&aa, fifoBuffer);
    mpu->dmpGetLinearAccel(&aaReal, &aa, &gravity);
}

float IMU::getPitch() {
	if(!goodConnection) return 0.0;

    return ypr[0] * 180 / M_PI;
}

float IMU::getYaw() {
	if(!goodConnection) return 0.0;

    return ypr[1] * 180 / M_PI;
}

float IMU::getRoll() {
	if(!goodConnection) return 0.0;

    return ypr[2] * 180 / M_PI;
}

uint16_t IMU::getAccelX() {
	if(!goodConnection) return 0;

    return aaReal.x;
}

uint16_t IMU::getAccelY() {
	if(!goodConnection) return 0;

    return aaReal.x;
}

uint16_t IMU::getAccelZ() {
	if(!goodConnection) return 0;

    return aaReal.x;
}

void IMU::printDebug() {
	if(!goodConnection) return;

    Serial.print("ypr\t");    Serial.print(ypr[0] * 180 / M_PI); Serial.print("\t");
                              Serial.print(ypr[1] * 180 / M_PI); Serial.print("\t");
                              Serial.print(ypr[2] * 180 / M_PI); Serial.println();
    
    Serial.print("areal\t");  Serial.print(aaReal.x);           Serial.print("\t");
                              Serial.print(aaReal.y);           Serial.print("\t");
                              Serial.print(aaReal.z);           Serial.println();
}
