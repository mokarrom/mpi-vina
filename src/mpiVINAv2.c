/* File      : mpiVinav2.c
*  Author    : Md Mokarrom Hossain
*  Username  : x2013idf
*  Course    : CSCI 522
*  Purpose   : MPI based parallel version of Autodock Vina.
*/

#include <stdio.h>

#include "mpi.h"
#include "CLinkedList.h"

#define MASTER                  0

#define COMPUTE_TAG             11
#define TERMINATE_TAG           22
#define WORK_REQ_TAG            33

#define MAX_LIGAND_NAME_LENGTH  25
#define LIGAND_FILE_NAME        "ligandlist"

void mpiVinaManager (int numProcs);
void mpiVinaWorker (int workerId);

MPI_Datatype MPI_LIGAND;
LigandList lgndsList;

int main(int argc, char *argv[])
{
    int numProcs, rank, totalLigands;
    FILE *ligandListFile;
    double startTime = 0.0, endTime = 0.0;

    MPI_Init (&argc, &argv );
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &numProcs);

    MPI_Type_contiguous(MAX_LIGAND_NAME_LENGTH, MPI_CHAR, &MPI_LIGAND);
    MPI_Type_commit(&MPI_LIGAND);

    // Only master processor will read the ligandlist file and will make the work pool.
    if(rank == MASTER)
    {
        printf("Master processor : Reading ligandlist file and creating work pool.\n");
        startTime = MPI_Wtime(); // start timer.
        char ligandName[MAX_LIGAND_NAME_LENGTH];
        ligandListFile = fopen(LIGAND_FILE_NAME , "r");
        if (NULL == ligandListFile)
        {
            printf("Couldn't open file %s for reading.\n", LIGAND_FILE_NAME);
            MPI_Abort(MPI_COMM_WORLD, 911); //Terminates MPI execution environment with error code 911.
            return 0;
        }
        //Initialize ligand list.
        InitLigandList(&lgndsList);

        while (fgets(ligandName, sizeof(ligandName), ligandListFile))
        {
            char *nlptr = strchr(ligandName, '\n');
            if (nlptr)  // Remove ending new line from ligandName.
                *nlptr = '\0';
            //Add to the list.
            InsertBack(&lgndsList, ligandName);
        }
        //Get total number of ligands.
        totalLigands = length(&lgndsList);
    }

    if(rank == MASTER)
    {
        mpiVinaManager(numProcs);   // Master processor will play the role of mpiVINA manager.
    }
    else
    {
        mpiVinaWorker(rank);    // All other processors will play the role of mpiVINA worker.
    }

    if (rank == MASTER)
    {
        endTime = MPI_Wtime(); // end timer.
        printf("\n\n..........................................\n"); 
        printf("   Number of workers       = %d \n", numProcs - 1); 
        printf("   Number of Lignds        = %u \n", totalLigands); 
        printf("   Total time required     = %.2lf seconds.\n", endTime - startTime); 
        printf("..........................................\n\n");
		fflush(stdout);

        ClearLigandList(&lgndsList); //Clear memory occupied by ligandlist.
    }

    MPI_Type_free (&MPI_LIGAND);
    MPI_Finalize ( );
    return 0;
}

void mpiVinaManager(int numProcs)
{
    int i;
    MPI_Status mStatus;
    Ligand *currLigand = NULL;

    currLigand = lgndsList.head;    //Begin with first ligand.

    while (currLigand != NULL)
    {
        //Wait for receiving work item request from any worker.
        MPI_Recv(NULL, 0, MPI_INT, MPI_ANY_SOURCE, WORK_REQ_TAG, MPI_COMM_WORLD, &mStatus);
        //Assign an work item to the requested worker.
        MPI_Send(currLigand->ligandName, 1, MPI_LIGAND, mStatus.MPI_SOURCE, COMPUTE_TAG, MPI_COMM_WORLD);

        currLigand = currLigand->next;    //Go ahead of the list.
    }

    //Computation has done. Send termination tag to all the slaves.
    for (i = 1; i < numProcs; i++)
    {
        MPI_Recv(NULL, 0, MPI_INT, MPI_ANY_SOURCE, WORK_REQ_TAG, MPI_COMM_WORLD, &mStatus);
        MPI_Send(NULL, 0, MPI_INT, mStatus.MPI_SOURCE, TERMINATE_TAG, MPI_COMM_WORLD);
    }
    return;
}

void mpiVinaWorker(int workerId)
{
    MPI_Status wStatus;
    char lignadName[MAX_LIGAND_NAME_LENGTH];

    printf("Worker %d has started.\n", workerId);
	fflush(stdout);
    //Initial request to manager for assigning work item.
    MPI_Send(NULL, 0, MPI_INT, 0, WORK_REQ_TAG, MPI_COMM_WORLD);
    MPI_Recv(lignadName, 1, MPI_LIGAND, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &wStatus);

    while (wStatus.MPI_TAG == COMPUTE_TAG)
    {
        printf("Worker = %d : ligand '%s' is processing...\n", workerId, lignadName);
		fflush(stdout);

        char vinaCmd[500]="Vina/vina --config Vina/conf.txt --ligand ./Ligand/";
        strcat(vinaCmd, lignadName);
        strcat(vinaCmd, " --out Output/");
        strcat(vinaCmd, lignadName);
        strcat(vinaCmd, ".pdbqt --log Output/");
        strcat(vinaCmd, lignadName);
        strcat(vinaCmd, ".txt>/dev/null");
        //Ask Autodock Vina to perform molecular docking.
        system(vinaCmd);

        vinaCmd[0] = '\0';
        strcat(vinaCmd, "mv  Ligand/");
        strcat(vinaCmd, lignadName);
        strcat(vinaCmd, " ProcessedLigand/");
        //Move processed ligands to ProcessedLigand directory.
        system(vinaCmd);

        //Request for another work item.
        MPI_Send(NULL, 0, MPI_INT, 0, WORK_REQ_TAG, MPI_COMM_WORLD);
        MPI_Recv(lignadName, 1, MPI_LIGAND, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &wStatus);
    }

    if (wStatus.MPI_TAG == TERMINATE_TAG)
    {
        printf("Worker %d has terminated.\n", workerId);
		fflush(stdout);
    }
    else
    {
        printf("Worker %d has received invalid Tag\n", workerId);
		fflush(stdout);
    }
    return;
}
