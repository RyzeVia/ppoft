TARGET  = libmicp.a
TARGET2 = libmicp.so

ENV_X86 = 1
#ENV_FX10 = 1

ifndef PFIXENV
export XPTI_ARCH  = ftb
export CPIO_ARCH  = syscall
export TMP_INC    = $(PWD)/include
export TMP_LIB    = $(PWD)/lib
export ICP_HOME   = $(PWD)/icp_core
export FTB_HOME   = $(HOME)/opt/ftb
export CFR_HOME   = $(PWD)/config_reader
#export CFLAG_DBG  = -DDEBUG_ENABLE -DDEBUG_LEVEL=101 -DICP_PREPOST -DDEBUG_PS_ENABLE
export CFLAG_DBG  = -DMEASURE_WTIME -DDEBUG_ENABLE -DDEBUG_LEVEL=81 
export CFLAG_EXT  = $(CFLAG_DBG) -I$(FTB_HOME)/include -I$(CFR_HOME) -I$(ICP_HOME)/xpt -I$(ICP_HOME)/xpt/xpti/$(XPTI_ARCH) -I$(ICP_HOME)/cpio/$(CPIO_ARCH)
export LDFLAG_EXT = -L$(FTB_HOME)/lib -L$(CFR_HOME) -L$(ICP_HOME)/xpt -L$(ICP_HOME)/xpt/xpti/$(XPTI_ARCH)  -L$(ICP_HOME)/cpio/$(CPIO_ARCH)
export MPI_H	   = 
export PFIXENV    = 1

ifdef ENV_X86
export CC      = gcc
export MPICC      = mpicc
export CFLAGS	  = -Wall -g -I$(TMP_INC) -I. $(CFLAG_EXT)
export SHARED_CFLAG = -shared -fPIC
export LD      = gcc
export MPILD      = mpicc
export LDFLAG     = -g -lpthread -lm -lrt -L$(TMP_LIB) -L.  $(LDFLAG_EXT) -o
endif

ifdef ENV_FX10
export CC      = fccpx
export MPICC      = mpifccpx
export CFLAGS		= -g -I$(TMP_INC) -I. $(CFLAG_EXT)
export SHARED_CFLAG = -shared -Xg -fPIC
export LD      = fccpx
export MPILD      = mpifccpx
export LDFLAG     = -g -lpthread -lm -lrt -L$(TMP_LIB) -L.  $(LDFLAG_EXT) -o
endif

export AR		= ar
export RANLIB	= ranlib
export ARCFLAGS	= crsv
export ARXFLAGS	= xv
endif


OBJS	= MICP_base.o MICP_fortran.o
          
HEADS   = libmicp.h

#Define Inference Rules

.c.o:
	$(MPICC) -c $(CFLAGS) -I$(FTB_HOME)/include $*.c
	
all: $(TMP_INC) $(TMP_LIB) $(TARGET)
	cp $(HEADS) $(TMP_INC)
	cp $(TARGET) $(TMP_LIB)

$(TMP_INC):
	mkdir $(TMP_INC)
	
$(TMP_LIB):
	mkdir $(TMP_LIB)

$(TARGET): depos icp_core/libicp.a spawn_tool/libnspawn.a config_reader/libcfr.a $(OBJS)
	cd depos; $(AR) $(ARXFLAGS) ../icp_core/libicp.a
	cd depos; $(AR) $(ARXFLAGS) ../config_reader/libcfr.a
	cd depos; $(AR) $(ARXFLAGS) ../spawn_tool/libnspawn.a
	$(AR) $(ARCFLAGS) $@ $(OBJS) depos/*.o

#$(TARGET2): depos icp_core/libicp.a spawn_tool/libnspawn.a config_reader/libcfr.a $(OBJS)
#	cd depos; $(AR) $(ARXFLAGS) ../icp_core/libicp.a
#	cd depos; $(AR) $(ARXFLAGS) ../config_reader/libcfr.a
#	cd depos; $(AR) $(ARXFLAGS) ../spawn_tool/libnspawn.a
		

depos:
	mkdir depos
	
icp_core/libicp.a: 
	cd icp_core; $(MAKE)
	
spawn_tool/libnspawn.a:
	cd spawn_tool; $(MAKE)
	
config_reader/libcfr.a:
	cd config_reader; $(MAKE)
	
clean:
	rm -f $(TARGET) $(OBJS) *.o *~
	rm -rf depos
	for hd in $(HEADS); do rm -f $(TMP_INC)/$$hd; done
	for hd in $(TARGET); do rm -f $(TMP_LIB)/$$hd; done

allclean:
	rm -f $(TARGET) $(OBJS) *.o *~
	rm -rf depos
	for hd in $(HEADS); do rm -f $(TMP_INC)/$$hd; done
	for hd in $(TARGET); do rm -f $(TMP_LIB)/$$hd; done
	cd icp_core; make allclean
	cd config_reader; make clean
	cd spawn_tool; make clean
	
