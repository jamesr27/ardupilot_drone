// James Reeves
//
// Anemometer front end app
//
//

#include "copter.h"   // Includes anemometer.h
#include <AP_SerialManager/AP_SerialManager.h>
#include <ctype.h>

extern const AP_HAL::HAL& hal;

// We're going to have one method for this: update().
// We call that, we read the serial through the backend/driver, we return the answer. Done.
// I bet it won't be that simple though.
// Oh, and I'm going to try and do the backend functions in this file...
// And where do we define this anemometer class? Here.
// Where do we instantiate them? Do the namespace pointer thing in AP_Anemometer1.h

// Didn't really need these, removed.

// bool Copter::read_anemometer1() {
//     anemometer1.update();   // Fire off the backend to update anmxxx.u, .v, .z, updated.
//
//     return anemometer1.updated;   // A bool. True if there is a new value, false if not.
// }
//
// bool Copter::read_anemometer2() {
//     anemometer2.update();   // Fire off the backend to update anm.u, .v, .z, updated.
//
//     return anemometer2.updated;   // A bool. True if there is a new value, false if not.
// }



// The anemometer class update functions
void Anemometer1::update() {
  // Fire off the backend. Read the serial data and process.
  updated =   get_reading();

  // Update public variables.
  // Should have been done in the get_reading function.



  // Debug
  updated = true;
  // u = 1.123;
  // v = 2.123;
  // w = 3.123;
}


// The anemometer class update functions
void Anemometer2::update() {
  // Fire off the backend


  // Update public variables.




  // Debug
  updated = true;
  u = 4.123;
  v = 5.123;
  w = 6.123;
}


// Anemometer1 *Anemometer1::_singleton;
//
// Anemometer1 *anemometer1()
// {
//     return Anemometer1::get_singleton();
// }
//
// Anemometer2 *Anemometer2::_singleton;
//
// Anemometer2 *anemometer2()
// {
//     return Anemometer2::get_singleton();
// }


//
// Backend functions. We are lazyish and call these manually to init serail ports.
// The backend read bytes method is called by the update method, which is called from Copter.cpp
//

void Anemometer1::init_serial(uint8_t _serial_instance)
{
  uart = AP::serialmanager().find_serial(AP_SerialManager::SerialProtocol_None, _serial_instance);
  if (uart != nullptr) {
      uart->begin(initial_baudrate(_serial_instance), rx_bufsize(), tx_bufsize());
  }
}

uint32_t Anemometer1::initial_baudrate(const uint8_t _serial_instance) //const
{
    return AP::serialmanager().find_baudrate(AP_SerialManager::SerialProtocol_None, _serial_instance);
}

bool Anemometer1::get_reading()
{
    if (uart == nullptr) {
        return false;
    }

    // Are there byte available?
    int16_t nbytes = uart->available();
    // I add a 2 in here, because I only want to process if there are at least two bytes in the buffer (there's an edge case that can occur when only 1 byte is in the buffer that I am lazily trying to avoid).
    if (nbytes <= 2){
      updated = false;
      return false;
    }

    // Some working vars/flags.
    bool _foundBeginning = false;
    char c = '\x00';  // Give it an initial value.

    // Read bytes in while loop and terminate once we have our data (may happen early)
    while (nbytes-- > 0){
      // We only read if we are not continuing from a previous go around (we definitely are seeking for a new message)
      if (!partialMessage){
        c = uart->read();
      }

      //
      // Do some logic
      //
      // If we had a partial message, we need to just restart hoping that more bytes have been added.
      // Find '\x02Q' This is the start of our data.
      //
      //

      if (c == '\x02'){
        _foundBeginning = true;
      }

      // If we get here we can now process numbers. We need to change nbytes, and check that we have received enough of the message to do something with.
      if ((_foundBeginning && c == 'Q') || partialMessage){
        // Step 1: If we have more than 25 bytes in the buffer. If not we need to stash and read again. I stashing in the receive buffer for now. I think this is fine, but ugly. Who gives a shit though.
        if (nbytes > 25){
          // Get the ','
          c = uart->read();
          nbytes--;

          // Get reading 1
          for (int i = 0; i < 7 ;i++){
            bytes1[i] = uart->read(); nbytes--;
          }
          // Get the ','
          c = uart->read();
          nbytes--;
          // Get reading 2
          for (int i = 0; i < 7 ;i++){
            bytes2[i] = uart->read(); nbytes--;
          }
          // Get the ','
          c = uart->read();
          nbytes--;
          // Get reading 3
          for (int i = 0; i < 7 ;i++){
            bytes3[i] = uart->read(); nbytes--;
          }
          _foundBeginning = false;
          partialMessage = false;
          updated = true;
        }
        else { // Terminate while loop, but set a flag so that we know we need to redo some stuff.
          partialMessage = true;
          updated = false;
          nbytes = 0;        // I think this forces us out.
          break;
        }
      }
    }


    // Assigns to class variables

    // Parsing our bytesX char arrays.
    // Format is:
    //  '+UUU.UU'

    // Debug
    u = 10;
    v = 11;
    w = 12;

    return true;

}
