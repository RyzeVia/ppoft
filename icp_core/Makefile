TARGET  = libicp.a

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

export CC         = gcc
export MPICC      = mpicc
export CFLAGS	  = -Wall -g -I$(TMP_INC) -I. $(CFLAG_EXT)
export LD         = gcc
export MPILD      = mpicc
export LDFLAG     = -g -lpthread -lm -lrt -L$(TMP_LIB) -L.  $(LDFLAG_EXT) -o
export AR		  = ar
export RANLIB	  = ranlib
export ARCFLAGS	  = crsv
export ARXFLAGS	  = xv
endif

OBJS	= ICP_base.o ICP_debug.o ICP_failurerate_db.o \
          ICP_handler.o ICP_optimize.o ICP_pftp.o \
          ICP_scheduler_client.o ICP_server.o \
          ICP_datamanage.o 
#          ICP_fortran.o 
          
HEADS   = libicp.h libicp_gval.h

#Define Inference Rules

.c.o:
	$(CC) -c $(CFLAGS) -I$(FTB_HOME)/include $*.c

all: $(TMP_INC) $(TMP_LIB) $(TARGET)
	cp $(HEADS) $(TMP_INC)
	cp $(TARGET) $(TMP_LIB)

ICP_datamanage.o: cpio/$(CPIO_ARCH)/ICP_datamanage.c
	cd cpio/$(CPIO_ARCH); $(MAKE)

$(TMP_INC):
	mkdir $(TMP_INC)
	
$(TMP_LIB):
	mkdir $(TMP_LIB)


$(TARGET): xpt/libxpt.a $(CFR_HOME)/libcfr.a $(OBJS)
	mkdir depos
	cd depos; $(AR) $(ARXFLAGS) ../xpt/libxpt.a
	cd depos; $(AR) $(ARXFLAGS) $(CFR_HOME)/libcfr.a
	$(AR) $(ARCFLAGS) $@ $(OBJS) depos/*.o
	rm -rf depos
	
xpt/libxpt.a: 
	cd xpt; $(MAKE)
	
$(CFR_HOME)/libcfr.a:
	cd $(CFR_HOME); $(MAKE)
	
clean:
	rm -f $(TARGET) $(OBJS) *.o *~
	rm -rf depos
	for hd in $(HEADS); do rm -f $(TMP_INC)/$$hd; done
	for hd in $(TARGET); do rm -f $(TMP_LIB)/$$hd; done

allclean:
	rm -f $(TARGET) $(OBJS) *.o *~
	rm -f test
	rm -rf depos
	for hd in $(HEADS); do rm -f $(TMP_INC)/$$hd; done
	for hd in $(TARGET); do rm -f $(TMP_LIB)/$$hd; done
	cd xpt; make allclean;
	cd cpio/$(CPIO_ARCH); make clean

test: test.o
	$(LD) test.o libicp.a $(LDFLAGS) test -lftb
	
testclean:
	rm -f test 
	
	