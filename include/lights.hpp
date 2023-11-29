#include "Solenoid.hpp"
#include "TaskWrapper.hpp"
#include "main.h"
#include <atomic>
#include <cmath>
#include <iostream>

namespace balls {

class Lights : public ryan::TaskWrapper {

private:

  enum class State { Disabled, Driver, Skills};
  State gameState = State::Disabled;
  int doinkerAnimTimestep;
  unsigned char *doinkerAnimData;
  sylib::Addrled &underglowLED;
  sylib::Addrled &intakeLED;
  sylib::Addrled &rightDriveLED;
  sylib::Addrled &leftDriveLED;

public:
    Lights(sylib::Addrled &underglowLED, sylib::Addrled &intakeLED, sylib::Addrled &leftDriveLED, sylib::Addrled &rightDriveLED)
        : underglowLED(underglowLED), intakeLED(intakeLED), leftDriveLED(leftDriveLED), rightDriveLED(rightDriveLED) 
        {};
        
    void init();
    void loop() override;
    void rotate();
    void setColor(int auton);
    void loadFile();
    unsigned char* readBMP(const char* filename);
    
};
} // namespace balls