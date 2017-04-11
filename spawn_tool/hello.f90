program main
  implicit REAL*8 (A-H,O-Z)
  include 'mpif.h'
  integer :: PETOT, my_rank, ierr, my_rank2(1), sum(1)
  call MPI_INIT      (ierr)
  call MPI_COMM_SIZE (MPI_COMM_WORLD, PETOT, ierr )
  call MPI_COMM_RANK (MPI_COMM_WORLD, my_rank, ierr )
  my_rank2(1) = my_rank
  call MPI_ALLREDUCE (my_rank2, sum, 1, MPI_INTEGER, MPI_SUM, MPI_COMM_WORLD, ierr )
  write (*,'(a,5i8)') 'Hello World FORTRAN', my_rank, PETOT, MPI_COMM_WORLD, MPI_COMM_SELF, sum(1)
  call MPI_FINALIZE (ierr)
  stop
end
