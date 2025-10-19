#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

struct _capacitor
{
		double *time; // time array
		double *voltage; // voltage array
		double *current; // cuurent array
		double C; // capacitance value
};
typedef struct _capacitor Capacitor;

//Prototype Functions to be called back to later in code
void simulate_constant_current(Capacitor *cap, double I_const, double dt, int N);
void simulate_constant_voltage(Capacitor *cap, double R, double V0, double dt, int N);
void print_results(Capacitor *cap, int N, const string &title);

//Start of main function
int main()
{
		double dt = 1e-10; //Time step in seconds
		double tfinal = 5e-6; //Final time in seconds
		int N = static_cast<int>(tfinal / dt); //number of timesteps, being 50000
		double R = 1e3; //1k ohm
		double C = 100e-12; //100pF
		double I_const = 1e-2; //10m Amps
		double V0 = 10.0; //10Volts

		Capacitor cap;
		cap.C = C;
		cap.time = new double[N];
		cap.voltage = new double[N];
		cap.current = new double[N];

		cout << fixed << setprecision(6);


		simulate_constant_current(&cap, I_const, dt, N);
		print_results(&cap, N, "Constant Current Source (Charging Capacitor)");


		simulate_constant_voltage(&cap, R, V0, dt, N);
		print_results(&cap, N, "Constant Voltage Source (RC Circuit)");

//Frees allocated memory

		delete[] cap.time;
		delete[] cap.voltage;
		delete[] cap.current;

		return 0;
}


void simulate_constant_current(Capacitor *cap, double I_const, double dt, int N)
{
		cap->time[0] = 0.0;
		cap->voltage[0] = 0.0;
		cap->current[0] = I_const;

		for (int i = 1; i < N; i++)
		{
				cap->time[i] = cap->time[i -1] + dt;
				cap->voltage[i] = cap->voltage[i - 1] + cap->current[i - 1] * dt / cap->C;
				cap->current[i] = I_const;
		}
}


void simulate_constant_voltage(Capacitor *cap, double R, double V0, double dt, int N)
{
		cap->time[0] = 0.0;
		cap->voltage[0] = 0.0;
		cap->current[0] = V0 / R;

		for (int i = 1; i < N; i++)
		{
				cap->time[i] = cap->time[i -1] + dt;
				cap->current[i] = cap->current[i - 1] - (cap->current[i - 1] * R * cap->C * dt);
				cap->voltage[i] = V0 - cap->current[i] * R;
		}
}

//This ouputs results for every 200 timesteps
void print_results(Capacitor * cap, int N, const string &title)
{
		cout << "\n---------------------------------------\n";
		cout << title << endl;
		cout << "---------------------------------------\n";
		cout << "Time (s)\tVoltage (V)\tCurrent (A)\n";

		for (int i = 0; i < N; i += 200)
		{
				cout << cap->time[i] << "\t" << cap->voltage[i] << "\t" << cap->current[i] << endl;
		}
}
