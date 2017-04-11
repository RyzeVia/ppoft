.SUFFIX = .c .f
TARGET  = test
INSLIB  = $(HOME)/opt/cifts/lib
INSINC  = $(HOME)/opt/cifts/include

LIBMICP = ../libmicp.a

#ALLINC	= ../include
ALLINC 	= /home/jitumoto/work/src/cocoft/iterative/include

CC      = mpicc
CFLAGS  = -c -Wall -g

FC 		= mpif90
FFLAGS  = -c -Wall -g

AR		= ar
RANLIB	= ranlib
ARCFLAGS	= crsv
ARXFLAGS	= xv

LD      = mpicc
FLD		= mpif90
LDFLAGS = -g -lpthread -lm -lrt -lftb -o 
#LDFLAGS2 = -L$(INSLIB) -I$(INSINC) -Ixpt -Ixpt/xpti/$(XPTI) -I$(CFRLIB) -L. -I. 
LDFLAGS2 = -L$(INSLIB) -I$(INSINC) -I$(ALLINC) -L. -I. 

OBJS	= test.o
          
#Define Inference Rules

.c.o:
	$(CC) $(CFLAGS) $(LDFLAGS2) $*.c

.f.o:
	$(FC) $(FFLAGS) $(LDFLAGS2) $*.f

all: $(TARGET)

fortran: testf.o
	$(FC) $(LDFLAGS) testf $(LDFLAGS2) testf.o $(LIBMICP)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $@ $(LDFLAGS2) $(OBJS) $(LIBMICP)

clean:
	rm -f $(TARGET) $(OBJS) *.o *~

	
