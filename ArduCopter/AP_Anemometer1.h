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
  float u;
  float v;
  float w;
  bool updated;

  void update();

  uint8t serial_instance;
  void init_serial(uint8t serial_instance);
  virtual bool get_reading(uint16_t &reading_cm) = 0;

private:
  char linebuf[50];           // legacy protocol buffer
  char bytes1[7];
  char bytes2[7];
  char bytes3[7];
  uint8_t linebuf_len;        // legacy protocol buffer length
  bool partialMessage = false;

protected:
    // baudrate used during object construction:
    virtual uint32_t initial_baudrate(uint8_t serial_instance) const;

    // the value 0 is special to the UARTDriver - it's "use default"
    virtual uint16_t rx_bufsize() const { return 0; }
    virtual uint16_t tx_bufsize() const { return 0; }

    AP_HAL::UARTDriver *uart = nullptr;

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
