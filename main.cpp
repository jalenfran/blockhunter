// Imports every library we need
#include "FEHLCD.h"
#include "FEHUtility.h"
#include "FEHSD.h"
#include "libraries/DrawHandler.h"
#include <math.h>

int main() {

    // Creates DrawHandler object (the WorkHorse)
    DrawHandler drawer;

    while (true){

        // Runs the program indefinitely
        drawer.run();
    }
}