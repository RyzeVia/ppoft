# mpiexec ./spawn_test

mpiexec -x LD_PRELOAD=$PWD/mpi_hook.so ./spawn_test
