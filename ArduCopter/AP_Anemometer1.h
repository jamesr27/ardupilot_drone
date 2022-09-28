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

class Anemometer1_Backend  // Note that this will include the serial stuff, I'm not separating that into to classes.
{
public:




};


class Anemometer2_Backend
{

};

class Anemometer1
{
public:
  static Anemometer1 *_singleton;
  float u;
  float v;
  float w;
  bool updated;
  bool serialStarted = false;

  void update();

  uint8_t serial_instance;
  void init_serial(uint8_t _serial_instance);
  bool get_reading() ; //was virtual = 0

  static Anemometer1 *getInstance() {
    _singleton = new Anemometer1;
    return _singleton;
  }

 //static Anemometer1 *get_singleton(void) { return _singleton; }

private:
  char linebuf[50];           // legacy protocol buffer
  char bytes1[6];
  char bytes2[6];
  char bytes3[6];
  uint8_t linebuf_len;        // legacy protocol buffer length
  bool partialMessage = false;
  float sign1 = 1.0;
  float sign2 = 1.0;
  float sign3 = 1.0;


protected:
    // I remove the virtuals from the below, I don't think that we need them.
    // baudrate used during object construction:
    uint32_t initial_baudrate(uint8_t _serial_instance);// const; // was virtual

    // the value 0 is special to the UARTDriver - it's "use default"
    uint16_t rx_bufsize() const { return 0; }   // was virtual
    uint16_t tx_bufsize() const { return 0; }   // was virtual

    AP_HAL::UARTDriver *uart = nullptr;


};

// I don't know what the fuck the below does, but I assume they are just using this class as like a static class or something.
// We don't really instantiate it. I just follow suit...
// Singletons or something like that...

// Anemometer1 *anemometer1();



class Anemometer2
{
  friend class Anemometer2_Backend;

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
