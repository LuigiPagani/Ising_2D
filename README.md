# Benchmarking Strategies for Parallel 2D Ising Model Simulation     
This project implements the 2D-Ising model simulation using C++ and offers parallel computation using MPI (for distributed memory systems), OpenMP (for multicore CPUs), and CUDA (for NVIDIA GPUs). It models the magnetic dipole moments of atomic "spins" on a lattice, simulating phase transitions in ferromagnetic materials. 

## Features
2D Ising Model simulation with periodic boundary conditions.

- Serial simulation in C++ via the Wolff algorithm.
- Parallel simulation via the Metroplis Hastings Algorithm on a single NVIDIA GPU.
- Parallel simulation via the Swendsen Wang Algorithm Parallelized with OpenMP.
- (Hybrid) parallel computation utilizing MPI and OpenMP, for the Simulation via the  Replica Exchange method, where each replica is simulated on a different MPI process via the parallelized Swendsen-Wang Algorithm with OneMP.
- Configurable parameters such as lattice size, temperature range, and number of iterations.

## Prerequisites

- g++ 11.2.0
- Open MPI 4.1.2
- Make 4.3
- CUDA compute capability higher than 6.1 and CUDA 12.1.

## Building and running the tests

**For the Wolff program**
```bash
cd Test/Wolff
make
./Wprogram
make clean
```

**For the SwendsenWangParallel program**
```bash
cd Test/SwendsenWangParallel
make
./SWprogram
make clean
```
**For the Rem (Replica Exchange Method) Program**
The REM Program has been tested for simulating 2 replicas across two processes. Tailor the `mpirun` command for your system, adjusting `--map-by` to 'socket' or 'node' based on your hardware configuration.

```bash
cd Test/Rem
make
mpirun -np 2 ./REMprogram
make clean
```

**For GPU-accelerated Parallelization with CUDA:**
```bash
cd Test/MetropolisCuda
nvcc -std=c++17 MetropolisCuda.cu -o MCprogram
./MCprogram
```
The results ares stored in output files called N.txt, where $N=L \times L$ is the lattice size parameter, except for the CUDA program which prints the results on screen. 






