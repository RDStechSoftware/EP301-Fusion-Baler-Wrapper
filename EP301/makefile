NAME = EP301 McHale Fusion 124

# path to /h8/iar/exe needed + include directory path needed as enviromental variable
AS = ah8300
CC = icch83
LD = hlink

AFLAGS = -v3 -l
CFLAGS = -v3 -mL -e -r -q -L -gOA -xDFT -P -1id -s9
#LFLAGS = -f lnk -o pro.hex -Fintel-extended -Y1
LFLAGS = -f lnk -o pro.hex -Fintel-extended -Y1 -xms -l map

# Source files that need to be Assembled
A_SRC =

# c source files to build
C_SRC = \
BYTEDEF.C \
EPL_INT.C \
EPL_HDW.C \
EPL_232.C \
EPL_CAN.C \
EPL_000.C \
EPL_001.C \
EPL_002.C \
EPL_003.C \
EPL_004.C \
EPL_005.C \
EPL_010.C \
EPL_011.C \
EPL_LAN0.C \
EPL_LAN1.C \
EPL_LAN2.C \
BM_BALER.C \
BM_F1ALL.C \
BM_F1EUR.C \
BM_F1CYR.C \
BM_FNT2.C \
BM_FNT3.C \
BM_SYM.C \
BM_KEY.C \

# Define all object files.
A_OBJ = $(A_SRC:.s20=.r20)
C_OBJ = $(C_SRC:.C=.r20)

all: test
    
clean:
	-rm -f *.r20 *.lst pro.hex pro.typ protyp.hex hexsort.hex pro_up.bat *.obj *.~* *.tds

test: pro.hex
	@ echo "...Copying"
	softtype bytedef.h
	
pro.hex: $(A_OBJ) $(S_OBJ) $(C_OBJ)
	@ echo "..linking"
	$(LD) $(LFLAGS)
	prosort pro.hex 512
	
$(A_OBJ): %.r20: %.s20 makefile
	@ echo ".assembling"
	$(AS) $(AFLAGS) $*.lst $<

$(C_OBJ): %.r20: %.C makefile bytedef.h
	@ echo ".Compiling"
	$(CC) $< $(CFLAGS)
	
    