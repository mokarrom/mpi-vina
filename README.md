# MPI-Vina: MPI based parallel implementation of Autodock Vina
--------------------------------------------------
MPI-Vina is an open-source parallelization of AutoDock Vina, which massively reduces the time of virtual screening by using compute clusters or network of computers. It is developed based on MPI and intended for distributed memory environment. The goal of MPI-Vina is to reduce the overall time of screening ligand data set. AutoDock Vina is the primary docking program of MPI-Vina.

In MPI-Vina, protein-ligand docking is distributed into different nodes of a computational cluster where each node performs docking of a single ligand against a target receptor. Distribution of ligand set allows docking multiple ligands in multiple nodes concurrently.

MPI-Vina reduces the overall time of doing virtual screening dramatically than the traditional virtual screening approach by using state-of-the-art parallel processing. It also reduces the magnitude and complexity of the screening problem and focuses on drug discovery and optimization efforts on the most promising leads. 

Requirements
------------
Availability of any MPI implementation (e.g., [Open MPI](http://www.open-mpi.org/), [MPICH](https://www.mpich.org/)).

Usage
-----
1. Convert your target receptor (i.e., protein) and all ligands into *pdbqt format* format (using any traditional tools).
2. Put all the ligand files in the `Ligand` directory.
3. Put your configuration file (`conf.txt`) and target receptor in the `Vina` directory.
4. To build and run the program type `./runMpiVINA.bash` in CLI (use `gridEngineJobScript.sh` for Gride Engine schedular). The corresponding Makefile and Shell script will do the remaining job. 
5. All output files are placed in the `Output` directory.
     -  `MpiVina.log` file contains summary of the parallel procesing.
     -  `SortedResult` file contains *binding affinity* of all ligands in sorted order.
     -  `<ligand_name>.pdbqt.pdbqt` & `<ligand_name>.pdbqt.txt` files contain the detailed result of individual ligand.

Reference
---------
For more details (e.g., implementation, performance, etc.), the reader is reffered to the technical report available in `docs` directory.

Acknowledgement
---------------
Computational resources are provided by ACENET, the regional advanced research computing consortium for universities in Atlantic Canada. ACENET is funded by the Canada Foundation for Innovation (CFI), the Atlantic Canada Opportunities Agency (ACOA), and the provinces of Newfoundland & Labrador, Nova Scotia, and New Brunswick.
