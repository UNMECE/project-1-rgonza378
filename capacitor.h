#ifndef CAPACITOR_H
#define CAPACITOR_H

struct _capacitor {
    double *time;
    double *voltage;
    double *current;
    double C;  // Capacitance value
};
typedef struct _capacitor Capacitor;

void initialize_capacitor(Capacitor* cap, int num_timesteps);
void solve_constant_current(Capacitor* cap, int num_timesteps, double dt);
void solve_constant_voltage(Capacitor* cap, int num_timesteps, double dt, double R);
void free_capacitor(Capacitor* cap);

#endif

