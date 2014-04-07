
#include <boost/mpi/environment.hpp>
#include <boost/mpi/communicator.hpp>
#include <iostream>
#include <stdio.h>

namespace mpi = boost::mpi;

/* Return 1 if 'i'th bit of 'n' is 1; 0 otherwise */
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

int main()
{
    mpi::environment env;
    mpi::communicator world;
    for (int i = 0; i < world.size(); i++)
    {
        check_circuit(0, world.rank());
    }
}
