// Arduino RBD Timer Library v1.3.0 Example - A three second interval timer that prints to serial.
// https://github.com/dst78/arduinolib_RBD_MicroTimer
// Forked    2019 Dominique Stender
// Copyright 2016 Alex Taujenis
// MIT License

#include <RBD_MicroTimer.h> // https://github.com/dst78/arduinolib_RBD_MicroTimer

RBD::MicroTimer timer;

void setup() {
  Serial.begin(115200);
  timer.setTimeout(3000);
  timer.restart();
}

void loop() {
  if(timer.onRestart()) {
    Serial.println("Three seconds passed");
  }
}
