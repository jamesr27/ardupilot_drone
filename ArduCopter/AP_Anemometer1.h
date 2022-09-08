// James ServoRelayEvents
//
// Simple implementation of anemometer 1, connected via uart.
//
#pragma once

#include <AP_HAL/AP_HAL.h>

bool read_anemometer1();
bool read_anemometer2();

// Anemometer class. We're going to be very lazy and non-OOP complaint And
// make duplicate classes for each anemometer.
class Anemometer1
{
  //friend class Anemometer1_backend;    // Include when we get to the backend

public:
  float u;
  float v;
  float w;
  bool updated;

  void update();

//   static Anemometer1 *get_singleton(void) { return _singleton; }
//
// private:
//     static Anemometer1 *_singleton;
};

// I don't know what the fuck the below does, but I assume they are just using this class as like a static class or something.
// We don't really instantiate it. I just follow suit...
// Singletons or something like that...

// Anemometer1 *anemometer1();



class Anemometer2
{
  //friend class Anemometer2_backend;    // Include when we get to the backend

public:
  float u;
  float v;
  float w;
  bool updated;

  void update();
//   static Anemometer2 *get_singleton(void) { return _singleton; }
//
// private:
//     static Anemometer2 *_singleton;
};



// Anemometer2 *anemometer2();
