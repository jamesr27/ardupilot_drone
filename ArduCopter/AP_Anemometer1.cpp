// James Reeves
//
// Anemometer front end app
//
//

#include "copter.h"   // Includes anemometer.h


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
  // Fire off the backend


  // Update public variables.




  // Debug
  updated = true;
  u = 1.123;
  v = 2.123;
  w = 3.123;
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
