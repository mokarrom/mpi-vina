#mpiVINA: MPI based parallel implementation of Autodock Vina
-------------------------------------------------------------------------
mpiVINA is an open-source parallelization of AutoDock Vina, which massively reduces the time of virtual screening by using compute clusters or network of computers. It is developed based on MPI and intended for distributed memory environment. The goal of mpiVINA is to reduce the overall time of screening ligand data set. AutoDock Vina is the primary docking program of mpiVINA.

In MPIVina, protein-ligand docking is distributed into different nodes of a computational cluster where each node performs docking of a single ligand against a target receptor. Distribution of ligand set allows docking multiple ligands in multiple nodes concurrently.

MPIVINA reduces the overall time of doing virtual screening dramatically than the traditional virtual screening approach by using parallel processing. It also reduces the magnitude and complexity of the screening problem and focuses on drug discovery and optimization efforts on the most promising leads. 

#Requirements
Availability of any MPI implementation (e.g., [Open MPI](http://www.open-mpi.org/), [MPICH](https://www.mpich.org/))

#Usage
1. Put all the ligand files (*pdbqt format*) in the `Ligand` directory.
2. Put your configuration file and target receptor in the `Vina` directory.
3. To build and run the program type `./runMpiVINA.bash` in CLI. The corresponding Makefile and bash script will do the remaining job. Check the `mpiVina.log` for output.


#Reference
For more information and performance details, please find the technical report in `docs` directory.
