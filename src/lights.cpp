#include "lights.hpp"
#include "autoSelect/selection.h"
#include "pros/misc.hpp"
#include "pros/rtos.hpp"
#include <fstream>
#include <iostream>
#include <string>

using namespace balls;

unsigned char *Lights::readBMP(const char *filename) {
  int i;
  FILE *f = fopen(filename, "rb");
  unsigned char info[54];

  // read the 54-byte header
  fread(info, sizeof(unsigned char), 54, f);

  // extract image height and width from header
  int width = *(int *)&info[18];
  int height = *(int *)&info[22];

  // allocate 3 bytes per pixel
  int size = 3 * width * height;
  unsigned char *data = new unsigned char[size];

  // read the rest of the data at once
  fread(data, sizeof(unsigned char), size, f);
  fclose(f);

  return data;
}

void Lights::rotate(){

  leftDriveLED.clear();
  leftDriveLED.set_pixel(0x600060, 0); leftDriveLED.set_pixel(0x990099, 1);
  leftDriveLED.set_pixel(0x990099, 2); leftDriveLED.set_pixel(0x600060, 3);
  leftDriveLED.cycle(*leftDriveLED, 5);

  rightDriveLED.clear();
  rightDriveLED.set_pixel(0x600060, 0); rightDriveLED.set_pixel(0x990099, 1);
  rightDriveLED.set_pixel(0x990099, 2); rightDriveLED.set_pixel(0x600060, 3);
  rightDriveLED.cycle(*rightDriveLED, 5);
}

void Lights::setColor(int auton) {

  if (auton > 0) {
    intakeLED.set_all(sylib::Addrled::rgb_to_hex(200, 0, 0));
    underglowLED.set_all(sylib::Addrled::rgb_to_hex(200, 0, 0));
    leftDriveLED.set_all(sylib::Addrled::rgb_to_hex(200, 0, 0));
    rightDriveLED.set_all(sylib::Addrled::rgb_to_hex(200, 0, 0));
  }
  else if (auton < 0) {
    intakeLED.set_all(sylib::Addrled::rgb_to_hex(0, 0, 200));
    underglowLED.set_all(sylib::Addrled::rgb_to_hex(0, 0, 200));
    leftDriveLED.set_all(sylib::Addrled::rgb_to_hex(0, 0, 200));
    rightDriveLED.set_all(sylib::Addrled::rgb_to_hex(0, 0, 200));
  }
  else {
    intakeLED.set_all(0x600060);
    underglowLED.set_all(0x600060);
    leftDriveLED.set_all(0x600060);
    rightDriveLED.set_all(0x600060);
    for (int i=17; i<28; i++) {
      underglowLED.set_pixel(0x990099, i);
    }
  }
}

void Lights::loadFile() {
  if (selector::auton < 0) {
    doinkerAnimData = readBMP("/usd/doinkerAnim.BMP");
  } else if (selector::auton > 0) {
    doinkerAnimData = readBMP("/usd/doinkerAnim2.BMP");
  }
}

void Lights::loop() {
  doinkerAnimTimestep = 32;
  doinkerAnimData = readBMP("/usd/doinkerAnim.BMP");

  while (true) {

      /*
      if (!pros::competition::is_autonomous() && !pros::competition::is_disabled()) {
        // find what frame in the animation we are
        if (!doinker.getState()) {
          doinkerAnimTimestep++;
          if (doinkerAnimTimestep > 31) {
            doinkerAnimTimestep = 31;
          }
        } else {
          doinkerAnimTimestep--;
          if (doinkerAnimTimestep < 0) {
            doinkerAnimTimestep = 3;
          }
        }
        // retrieve the value of each pixel for that frame
        for (int i = 0; i < 32; i++) {
          doinkerLED.set_pixel(sylib::Addrled::rgb_to_hex(
                  doinkerAnimData[3 * (i * 32 + doinkerAnimTimestep)],
                  doinkerAnimData[3 * (i * 32 + doinkerAnimTimestep) + 1],
                  doinkerAnimData[3 * (i * 32 + doinkerAnimTimestep) + 2]
                  ), i); // index of the pixel in the strip
        }
      }
      */
      pros::delay(18);
  }
}