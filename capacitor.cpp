#include "capacitor.h"
#include <iostream>

void initialize_capacitor(Capacitor* cap, int num_timesteps) {
    cap->time = new double[num_timesteps];
    cap->voltage = new double[num_timesteps];
    cap->current = new double[num_timesteps];
    cap->C = 100e-12;

    cap->time[0] = 0.0;
    cap->voltage[0] = 0.0;
    cap->current[0] = 1e-2;
}

void solve_constant_current(Capacitor* cap, int num_timesteps, double dt) {
    for (int t = 1; t < num_timesteps; ++t) {
        cap->time[t] = t * dt;
        cap->voltage[t] = cap->voltage[t-1] + cap->current[t-1] * dt / cap->C;

        if (t % 200 == 0) {
            std::cout << "Time: " << cap->time[t] 
                      << " Voltage: " << cap->voltage[t] 
                      << " Current: " << cap->current[t-1] << std::endl;
        }
    }
}

void solve_constant_voltage(Capacitor* cap, int num_timesteps, double dt, double R) {
    double V0 = 10.0;
    cap->current[0] = V0 / R;

    for (int t = 1; t < num_timesteps; ++t) {
        cap->time[t] = t * dt;
        cap->current[t] = cap->current[t-1] - cap->current[t-1] * dt / (R * cap->C);

        if (t % 200 == 0) {
            std::cout << "Time: " << cap->time[t] 
                      << " Voltage: " << V0 
                      << " Current: " << cap->current[t] << std::endl;
        }
    }
}

void free_capacitor(Capacitor* cap) {
    delete[] cap->time;
    delete[] cap->voltage;
    delete[] cap->current;
}

