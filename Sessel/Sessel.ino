#include <SoftwareSerial.h>
#include <CPPM.h>

#define TX1 7
#define TX0 9

#define NUM_CHANNELS 6

SoftwareSerial mySerial0(99, TX0);
SoftwareSerial mySerial1(99, TX1);

int16_t whichPixel = 0;

void setup() {
  mySerial1.begin(115200);
  mySerial0.begin(115200);

  mySerial0.end();
  mySerial1.end();
  CPPM.begin(NUM_CHANNELS);
}

int16_t speedr = 0;
int16_t speedl = 0;

void loop() {

  if (CPPM.ok()) {
    int16_t channels[3];
    CPPM.read(channels);
    
    int lenk = channels[0] - 127;
    int speed = channels[1] - 127;

    speedl = (speed + lenk ) * (channels[2] / 255.0); //speed
    speedr = (speed - lenk ) * (channels[2] / 255.0); //speed

    speedr = constrain(speedr, -127, 127);
    speedl = -constrain(speedl, -127, 127);

    mySerial1.write(speedr >> 8);
    mySerial1.write(speedr & 0xFF);

    mySerial0.write(speedl >> 8);
    mySerial0.write(speedl & 0xFF);

    CPPM._synced = false;
    
    delay(10);
  }
}
