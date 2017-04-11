TARGET = ICP_datamanage.o
HEADS  = cpio.h

ifndef PFIXENV
export ICP_HOME	  = ../../
export XPTI_ARCH  = ftb
export FTB_HOME   = $(HOME)/opt/ftb
export CFR_HOME   = $(ICP_HOME)/../config_reader
export CPIO_ARCH	  = syscall
export CFLAG_EXT  =  -I$(CFR_HOME)  -I$(ICP_HOME)/xpt -I$(ICP_HOME)/xpt/xpti/$(XPTI_ARCH) -I$(ICP_HOME)/cpio/$(CPIO_ARCH)
export PFIXENV    = 1
export MPICC      = mpicc
endif

# CFLAG_EXT  = -I$(ICP_HOME)/xpt -I$(ICP_HOME)/xpt/xpti/$(XPTI_ARCH) -I$(CFR_HOME) -I$(FTB_HOME)/include

CFLAGS  = -c -Wall -g -I../../ -I. $(CFLAG_EXT)

all: $(TARGET)
	cp $(TARGET) ../../

.c.o:
	$(MPICC) $(CFLAGS) $*.c
	cp $(TARGET) ../../

clean:
	rm $(TARGET)