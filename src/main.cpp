#include <chrono>
#include <iostream>
#include <thread>

#include "ahrs/ahrs.h"
#include "ahrs/ahrs_sensors.h"
#include "minimu/i2c_device.h"
#include "minimu/lis3mdl_magmeter.h"
#include "minimu/lsm6_imu.h"

class MinimuImuGyro : public ahrs::Sensor {
   public:
    MinimuImuGyro(minimu::Lsm6_imu& imu) : imu{imu} {}
    ahrs::sensor_readout read() override {
        auto g = imu.read_gyro();
        return {g.x, g.y, g.z};
    }

   private:
    minimu::Lsm6_imu& imu;
};

class MinimuImuAcc : public ahrs::Sensor {
   public: MinimuImuAcc(minimu::Lsm6_imu& imu) : imu{imu} {}
    ahrs::sensor_readout read() override {
        auto a = imu.read_acc();
        return {a.x, a.y, a.z};
    }

   private:
    minimu::Lsm6_imu& imu;
};

class MinimuMag : public ahrs::Sensor {
   public:
    MinimuMag(minimu::Lis3mdl_magmeter& mag) : mag{mag} {}
    ahrs::sensor_readout read() override {
        auto m = mag.read();
        return {m.x, m.y, m.z};
    }

   private:
    minimu::Lis3mdl_magmeter& mag;
};

int main() {
    minimu::Lsm6_imu li{1, minimu::sa0_state::sa0_high};
    minimu::Lis3mdl_magmeter lm{1, minimu::sa0_state::sa0_high};

    MinimuImuAcc acc{li};
    MinimuImuGyro gyro{li};
    MinimuMag mag{lm};

    double dt = 0.005;
    ahrs::Ahrs ahrs{gyro, acc, mag, dt};
    std::cout << "Calibrating imu\n";
    ahrs.calibrate_imu();
    std::cout << "Calibrating mag\n";
    ahrs.calibrate_mag(5000);
    std::cout << "Calibration finished\n";

    while (true) {
        std::this_thread::sleep_for(std::chrono::duration<double>(dt));
        auto readout = ahrs.update();
        std::cout << "x: " << readout.x << '\t' << "y: " << readout.y << '\t'
                  << "z: " << readout.z << '\n';
    }
}
