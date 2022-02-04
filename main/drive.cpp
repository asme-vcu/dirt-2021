/* Drive submodule implementation */
#include"drive.h"
#include"consts.h"

Drive::Drive(IMU& imu, RC& rc) : _imu(imu), _rc(rc) {
    _prevVelocity.left  = 0.0f;
    _prevVelocity.right = 0.0f;
}

void Drive::setup() {
    _esc_l.attach(DRIVE_ESC_L_PIN, PWM_MIN, PWM_MAX);
    _esc_r.attach(DRIVE_ESC_R_PIN, PWM_MIN, PWM_MAX);

    _prevTime = millis();
}

void Drive::run() {
    Velocity speed = getTarget();

    _tractionControl = _rc.getTractionControl();
    _gyroControl     = _rc.getGyroscopeCorrect();

    // Get variables needed for traction control
    _dt = millis() - _prevTime;
    _dv.left  = speed.left  - _prevVelocity.left;
    _dv.right = speed.right - _prevVelocity.right;

    // Apply modifications to our target speed
    // based on algorithms
    speed = applyTractionControl(speed); // h1(t)
    speed = applyGyroControl(speed);     // h2(t)
    
    // Series convolution
    // y(t) = x1(t) * h1(t) * h2(t)

    setSpeed(speed);

    // Record this velocity for later
    _prevVelocity = speed;
    _prevTime = millis();
}

Drive::Velocity Drive::getTarget() {
    // get inputs
    long thi = constrain(_rc.getThrust(), 1000, 2000);
    long tui = constrain(_rc.getTurn(),  1000, 2000);
    RC::speed speed_control = _rc.getSpeed();

    // map them to floats
    float th = (thi - 1000.0f)/1000.0f;
    float tu = (tui - 1000.0f)/1000.0f;

    // get speed target weight
    float c;
    switch(speed_control) {
        case RC::speed::high:
            c = 1.0f;
            break;
        case RC::speed::medium:
            c = 0.66f;
            break;
        case RC::speed::low:
            c = 0.33f;
            break;
    }

    // apply input weights
    const float a = DRIVE_THRUST_WEIGHT;
    const float b = DRIVE_TURN_WEIGHT;

    Velocity v;

    // mapping from input space to output space
    v.left  = c * (a*th + b*tu)/(a+b);
    v.right = c * (a*th - b*tu)/(a+b);

    return v;
}

void Drive::setSpeed(Velocity v) {
    long left, right;

    // test if motors need to stop for any reason
    if(shouldHalt()) {
        // 1500 is half-way between 1000 and 2000
        // for bidirectional ESC's this means stop
        left = right = 1500;
    } else {
        // remap float (0, 1) to long (1000, 2000)
        left  = (v.left  * 1000) + 1000;
        right = (v.right * 1000) + 1000;

        // constrain values
        left  = constrain(left,  1000, 2000);
        right = constrain(right, 1000, 2000);
    }

    // write values to motors
    _esc_l.writeMicroseconds(left);
    _esc_r.writeMicroseconds(right);
}

bool Drive::shouldHalt() {
    // check for controller connection and stop switch
    return _rc.isDisconnected() || _rc.isHalted();
}

Drive::Velocity Drive::applyTractionControl(Velocity v) {
#if DRIVE_TRACTION_CONTROL_ENABLED
    // Must be enabled
    if(!traction_control) return v;

    // TODO
#else
    return v;
#endif
}

Drive::Velocity Drive::applyGyroControl(Velocity v) {
#if DRIVE_GYRO_CONTROL_ENABLED
    // Must be enabled
    if(!gyroControl) return v;

    // TODO
#else
    return v;
#endif
}

void Drive::printDebug() {
    Serial.println("[Drive Module]");
    Serial.print("Halt: "); Serial.print(shouldHalt());
    Serial.print(" TCE: "); Serial.print(_tractionControl);
    Serial.print(" GEE: "); Serial.println(_gyroControl);

    // these values are actually current, printDebug() is after run()
    Serial.print("VL: ");  Serial.print(_prevVelocity.left);
    Serial.print(" VR: "); Serial.println(_prevVelocity.right);

    Serial.print("dv: ");  Serial.print(_dv.left);
    Serial.print(", ");    Serial.print(_dv.right);
    Serial.print(" dt: "); Serial.println(_dt);
}
