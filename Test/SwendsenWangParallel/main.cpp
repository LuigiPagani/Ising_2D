#include "SwendsenWangParallel.h"
#include <cmath>
#include <cstdlib>
#include <vector>
#include <iostream>


int main() {

    int L_MIN =256;
    int L_MAX =256;
    float T_MIN=0.2 ;
    float T_MAX=2.8;
    float T_STEP=0.2;
    float J=1.0;
    
    std::vector<float> ITVector = {30};



    int L = L_MIN;
    for(int i = 0; i < ITVector.size(); i++) {
         std::cout<<"Simulation start for L = "<<L<<std::endl;
        SwendsenWangParallel simulation(J, L, T_MIN, T_MAX, T_STEP, ITVector[i]);
        simulation.simulate_phase_transition();
        std::cout<<"Simulation done for L = "<<L<<std::endl;
        simulation.store_results_to_file();
        L *= 2;
    }
    
    }
