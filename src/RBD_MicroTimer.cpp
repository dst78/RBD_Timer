// Arduino RBD Timer Library v1.3.0 - Manage many timed events.
// https://github.com/dst78/arduinolib_RBD_MicroTimer
// Forked    2019 Dominique Stender
// Copyright 2016 Alex Taujenis
// MIT License

#include <Arduino.h>
#include <RBD_MicroTimer.h> // https://github.com/dst78/arduinolib_RBD_MicroTimer

namespace RBD {
  MicroTimer::MicroTimer() {}

  MicroTimer::MicroTimer(unsigned long value) {
    setTimeout(value);
  }

  void MicroTimer::setTimeout(unsigned long value) {
    _timeout = (value > 0) ? value : 1;
  }

  unsigned long MicroTimer::getTimeout() {
    return _timeout;
  }

  void MicroTimer::setHertz(int value) {
    // possible to do: manage setHertz in micros() for higher resolution
    _hertz   = constrain(value, 1, 1000);
    _timeout = (unsigned long)(1000 / _hertz);
  }

  int MicroTimer::getHertz() {
    return _hertz;
  }

  void MicroTimer::restart() {
    _waypoint         = millis();
    _state            = ACTIVE;
    _has_been_active  = false;
    _has_been_expired = false;
  }

  void MicroTimer::stop() {
    _state = STOPPED;
  }

  bool MicroTimer::isActive() {
    _updateState();
    return _state == ACTIVE;
  }

  bool MicroTimer::isExpired() {
    _updateState();
    return _state == EXPIRED;
  }

  bool MicroTimer::isStopped() {
    return _state == STOPPED;
  }

  bool MicroTimer::onRestart() {
    if(isExpired()) {
      restart();
      return true;
    }
    return false;
  }

  bool MicroTimer::onActive() {
    if(!_has_been_active && isActive()) {
      return _has_been_active = true;
    }
    return false;
  }

  bool MicroTimer::onExpired() {
    if(!_has_been_expired && isExpired()) {
      return _has_been_expired = true;
    }
    return false;
  }

  unsigned long MicroTimer::getValue() {
    return millis() - _waypoint;
  }

  unsigned long MicroTimer::getInverseValue() {
    return _timeout - getValue();
  }

  int MicroTimer::getPercentValue() {
    if(_timeout == 0) {return 0;}
    return getValue() / float(_timeout) * 100;
  }

  int MicroTimer::getInversePercentValue() {
    return 100 - getPercentValue();
  }


  // private

  void MicroTimer::_updateState() {
    if(_state == ACTIVE && getValue() >= _timeout) {
      _state = EXPIRED;
    }
  }
}
