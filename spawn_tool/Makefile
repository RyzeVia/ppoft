
ifndef PFIXENV
export XPTI_ARCH  = ftb
export CPIO_ARCH  = syscall
export ICP_HOME   = $(PWD)
export TMP_INC    = include
export TMP_LIB    = lib
export FTB_HOME   = $(HOME)/opt/ftb
export CFR_HOME   = $(ICP_HOME)/../config_reader
export CFLAG_EXT  = -I$(FTB_HOME)/include -I$(CFR_HOME) -I$(ICP_HOME)/xpt -I$(ICP_HOME)/xpt/xpti/$(XPTI_ARCH) -I$(ICP_HOME)/cpio/$(CPIO_ARCH)
export LDFLAG_EXT = -L$(FTB_HOME)/lib -L$(CFR_HOME) -L$(ICP_HOME)/xpt -L$(ICP_HOME)/xpt/xpti/$(XPTI_ARCH)  -L$(ICP_HOME)/cpio/$(CPIO_ARCH)
export PFIXENV    = 1
export MPIF90	  = mpif90
export CC         = gcc
export MPICC      = mpicc
export CFLAGS	  = -g
export LD         = gcc
export MPILD      = mpicc
export LDFLAG     = -g -lpthread -lm -lrt -L$(TMP_LIB) -L.  $(LDFLAG_EXT) -o
export AR		  = ar
export RANLIB	  = ranlib
export ARCFLAGS	  = crsv
export ARXFLAGS	  = xv
export SHARED_CFLAG = -shared -fPIC
endif

#ifdef DEBUG_WRAPPING
export FDEBUG = -DDEBUG_WRAPPING
#endif

#CC=mpifccpx
CC=$(MPICC)
#FC=mpifrtpx
FC=$(MPIF90)
#CFLAGS=-Kfast -Koptmsg=2 -Kunroll 
#CFLAGS=-DSPT_MPI_OVERWRAP # Overwrapping MPI_Init[_Thread]() MPI_Spawn[_multipule]()
CFLAGS=
#FFLAGS=-Kfast -Koptmsg=2 -Kunroll
FFLAGS=

TARGETS=  libnspawn.a #spawn_test_static
TARGETS2= mpi_hook.so #spawn_test
all: $(TARGETS)
	@echo "Making static library"
	@echo "If you want to use dll, change CFLAGS on Makefile"

shared: $(TARGETS2)
	@echo "Making dynamic library (Note: Only for openmpi)"
 
#mpi_logger.so: mpi_logger.c
#	$(CC) -shared -fPIC $< -o $@

mpi_hook.so: mpi_hook.c comm_split.c
	$(CC) $(SHARED_CFLAG) $+ -o $@

libnspawn.a: mpi_hook.o comm_split.o
	$(AR) $(ARCFLAGS) $@ $+

mpi_hook.c: gen.pl fbindings.pl
	perl ./gen.pl > $@
	perl ./fbindings.pl >>$@

spawn_test_static: spawn_test.o mpi_hook.o comm_split.o
	$(CC) $(CFLAGS) $+ -o $@

#hello: hello.f90
#	mpifrtpx $< -o $@
#
#f2ctest: f2ctest.c
#	mpifccpx $< -o $@

%: %.o
	$(CC) $(CFLAGS) $(FDEBUG) $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(FDEBUG) $< -c

%: %.f90
	$(FC) $(FFLAGS) $(FDEBUG) $< -o $@

clean:
	rm -f mpi_hook.c $(TARGETS) hello *.o
