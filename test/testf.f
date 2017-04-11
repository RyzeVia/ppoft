      program init
      implicit none
      include 'mpif.h'
      integer ierr
      integer i, rank, id
      dimension id(2)

      call mpi_init(ierr)

      call fmicp_init(ierr)

      call mpi_comm_rank(MPI_COMM_WORLD, rank, ierr)

      call fmicp_enable("test_cp", 7, 1)
      call fmicp_registration_data_scaler(i, id(1), id(2))
      call fmicp_ready()
      print '("RANK[",i2,"]:join")', rank

      do i=1, 100
      print '("RANK[",i2,"]:",i3)', rank, i
      call sleep(1)
      call mpi_barrier(MPI_COMM_WORLD, ierr)

      call fmicp_checkpoint_candidate(ierr)
      end do

      call fmicp_disable()

      call fmicp_finalize("flag2",5)
      call mpi_finalize(ierr)

      stop
      end program init
