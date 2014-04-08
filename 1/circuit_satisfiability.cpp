#include <iostream>
#include <stdio.h>
#include <mpi.h>

void check_circuit (int id, int z) {
    int v[16];        /* Each element is a bit of z */
    int i;

    for (i = 0; i < 16; i++){ v[i] = ((z&(1<<i))?1:0); }

    if ((v[0] || v[1]) && (!v[1] || !v[3]) && (v[2] || v[3])
            && (!v[3] || !v[4]) && (v[4] || !v[5])
            && (v[5] || !v[6]) && (v[5] || v[6])
            && (v[6] || !v[15]) && (v[7] || !v[8])
            && (!v[7] || !v[13]) && (v[8] || v[9])
            && (v[8] || !v[9]) && (!v[9] || !v[10])
            && (v[9] || v[11]) && (v[10] || v[11])
            && (v[12] || v[13]) && (v[13] || !v[14])
            && (v[14] || v[15])) {
        printf ("%d) %d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d\n", id,
                v[0],v[1],v[2],v[3],v[4],v[5],v[6],v[7],v[8],v[9],
                v[10],v[11],v[12],v[13],v[14],v[15]);
        fflush (stdout);
    }
}

int main(int argc, char* argv[])
{
    int rank;
    int size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    unsigned int min = 0;
    unsigned int max = 65535;

    unsigned int lengthOfInterval = max / (size - 1);

    unsigned int start = rank * lengthOfInterval;
    unsigned int end = std::min(max, (rank + 1) * lengthOfInterval - 1);

    std::cout << start << " " << end << std::endl;

    for (int i = start; i < end; i++)
    {
        check_circuit(rank, i);
    }

    MPI_Finalize();
    return 0;
}
