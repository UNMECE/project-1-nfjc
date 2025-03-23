#include <iostream>
#include <iomanip>
#include <cmath>

// Struct used throughout program to store and calculate voltage & current values.
struct Capacitor {
    double* time;
    double* voltage;
    double* current;
    double C;
};

// Declaring constants to be used in my code.
const double dt = 1e-10;
const double T_final = 5e-6;
const int num_timesteps = 50000;
const double R = 1e3;
const double C_value = 100e-12;
const double I_constant = 1e-2;
const double V0 = 10.0;

// Function that initializes the capacitor and its associated values.
void setupCapacitor(Capacitor& cap) {
    cap.C = C_value;
    cap.time = new double[num_timesteps]();
    cap.voltage = new double[num_timesteps]();
    cap.current = new double[num_timesteps]();
}

// Constant current function that houses the main loop for constant current calculations.
void constantCurrent(Capacitor& cap) {
//Initializing cap values all to zero and the current value to the given constant(1e-2).
    cap.time[0] = 0;
    cap.voltage[0] = 0;
    cap.current[0] = I_constant;
//The main loop that follows the equations given in the instructions.
    for (int i = 1; i < num_timesteps; i++) {
        cap.time[i] = i * dt;
        cap.voltage[i] = cap.voltage[i - 1] + cap.current[i - 1] * dt / cap.C;
        cap.current[i] = I_constant;
//Every 200 timesteps it prints out a reading. For a total of 250 outputs.
        if (i % 200 == 0) {
            std::cout << "t = " << cap.time[i] << " s, V = " 
                      << cap.voltage[i] << " V" << std::endl;
        }
    }
}

// Similar function but for constant voltage calculattions.
void constantVoltage(Capacitor& cap) {
//Initializing cap values again.    
    cap.time[0] = 0;
    cap.current[0] = V0 / R;
    cap.voltage[0] = 0;
//Main constant voltage loop similar to before.
    for (int i = 1; i < num_timesteps; i++) {
        cap.time[i] = i * dt;
        cap.current[i] = cap.current[i - 1] - (cap.current[i - 1] / (R * cap.C)) * dt;
        cap.voltage[i] = V0 - cap.current[i] * R;
//Every 200 timesteps it gives another reading for another 250 outputs.
        if (i % 200 == 0) {
            std::cout << "t: " << cap.time[i] << " s | Vc: " << cap.voltage[i] 
                      << " V | I: " << cap.current[i] << " A" << std::endl;
        }
    }
}

// Function to free allocated memory after code has been ran to avoid memory leaks.
void clearCapMemorySpace(Capacitor& cap) {
    delete[] cap.time;
    delete[] cap.voltage;
    delete[] cap.current;
}

int main() {
//Initializing valeus at runtime.    
    Capacitor cap;
    setupCapacitor(cap);
//Constant Current function call
    std::cout << "Constant Current Charging:" << std::endl;
    constantCurrent(cap);
//Constant Voltage function call.
    std::cout << "\nConstant Voltage Charging:" << std::endl;
    constantVoltage(cap);
//Clearing memory and finishing my project! :).
    clearCapMemorySpace(cap);
    return 0;
}

