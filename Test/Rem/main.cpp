#include "Rem.h"
#include <cmath>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>
#include <unordered_set>
#include <queue>
#include <map>
#include <numeric>
#include <omp.h>
#include <random>
#include <mpi.h>

int main(int argc, char* argv[]) {
    int L_MIN =256;
    int L_MAX =256;
    float T_MIN=0.2 ;
    float T_MAX=2.8;
    float T_STEP=0.2;
    float J=1.0;
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);



    // Broadcast parameters to all other processes
    MPI_Bcast(&L_MIN, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&L_MAX, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&T_MIN, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&T_MAX, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&T_STEP, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&J, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);

    std::vector<float> ITVector = {30};
    float IT;



    // Broadcast ITVector to all processes
    // Size of ITVector needs to be shared first
    int itVectorSize = ITVector.size();
    MPI_Bcast(&itVectorSize, 1, MPI_INT, 0, MPI_COMM_WORLD);
    ITVector.resize(itVectorSize);
    MPI_Bcast(ITVector.data(), itVectorSize, MPI_FLOAT, 0, MPI_COMM_WORLD);

    int L = L_MIN;
    for(int i = 0; i < ITVector.size(); i++) {
        if (rank == 0) {
            std::cout << "Simulation start for L = " << L << std::endl;
        }
        Rem simulation(J, L, T_MIN, T_MAX, T_STEP, ITVector[i]);
        simulation.simulate_phase_transition(argc, argv);
        // After the simulation loop in the main function
        if(rank ==0){
            simulation.store_results_to_file();
        }
        L *= 2;
    }

    MPI_Finalize();
    return 0;
}
