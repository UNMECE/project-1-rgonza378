#include "capacitor.h"
#include <iostream>

int main() {
    const int num_timesteps = 50000;  // Total number of timesteps
    const double dt = 1e-10;          // Time step (seconds)
    const double R = 1e3;             // Resistance (1 kΩ)
    Capacitor cap;                    // Capacitor structure

    initialize_capacitor(&cap, num_timesteps);

    std::cout << "Solving constant current case...\n";
    solve_constant_current(&cap, num_timesteps, dt);

    std::cout << "Solving constant voltage case...\n";
    solve_constant_voltage(&cap, num_timesteps, dt, R);

    free_capacitor(&cap);

    return 0;
}

