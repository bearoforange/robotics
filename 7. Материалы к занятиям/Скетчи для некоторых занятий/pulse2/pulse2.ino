#include <iarduino_SensorPulse.h>

iarduino_SensorPulse Pulse(A0); 

int prevtime = 0;
void setup() {
  Serial.begin(9600);
  Pulse.begin();
  prevtime = millis();
}

void loop() {
  if (Pulse.check(ISP_VALID) == ISP_CONNECTED)
  {
    //prevtime = millis();
    Serial.println(Pulse.check(ISP_PULSE));
  }
}
