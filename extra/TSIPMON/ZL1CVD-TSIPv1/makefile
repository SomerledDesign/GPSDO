# WinAVR Sample makefile written by Eric B. Weddington, et al.
# Released to the Public Domain
# Please read the make user manual!
#
# On command line:
# make all = Make software.
# make clean = Clean out built project files.
# make coff = Convert ELF to COFF using objtool.
#
# To rebuild project do "make clean" then "make all".

# MCU name
MCU = atmega8515

#Fuse settings for atmega8515
ifeq ($(MCU), atmega8515)
# externer Quarz 12MHz
	FUSE_BITS = -u -U lfuse:w:0xef:m -U hfuse:w:0xc9:m
endif

# Output format. (can be srec, ihex)
#FORMAT = srec

# using ihex for MiniPro USB programmer C.D. 23/10/2014
FORMAT = ihex

# Target file name (without extension).
TARGET = main

# Optimization level (can be 0, 1, 2, 3, s) 
# (Note: 3 is not always the best optimization level. See avr-libc FAQ)
OPT = s

# List C source files here. (C dependencies are automatically generated.)
SRC = $(TARGET).c \
lcd.c
#foo.c bar.c

# List Assembler source files here.
# Make them always end in a capital .S.  Files ending in a lowercase .s
# will not be considered source files but generated files (assembler
# output from the compiler), and will be deleted upon "make clean"!
# Even though the DOS/Win* filesystem matches both .s and .S the same,
# it will preserve the spelling of the filenames, and gcc itself does
# care about how the name is spelled on its command-line.
ASRC = 
# conv.S


# Optional compiler flags.
CFLAGS = -g -O$(OPT) -funsigned-char -funsigned-bitfields -fpack-struct \
-fshort-enums -Wall -Wstrict-prototypes -Wa,-ahlms=$(<:.c=.lst)

# Optional assembler flags.
ASFLAGS = -Wa,-ahlms=$(<:.S=.lst),-gstabs 

# Optional linker flags.
LDFLAGS = -Wl,-Map=$(TARGET).map,--cref

# Additional libraries
#
# Minimalistic printf version
#LDFLAGS += -Wl,-u,vfprintf -lprintf_min
#
# Floating point printf version (requires -lm below)
#LDFLAGS +=  -Wl,-u,vfprintf -lprintf_flt
#
# -lm = math library
LDFLAGS += -lm


# Programming support using avrdude. Settings and variables.

# Programming hardware: alf avr910 avrisp bascom bsd 
# dt006 pavr picoweb pony-stk200 sp12 stk200 stk500
#
# Type: avrdude -c ?
# to get a full listing.
#

#AVRDUDE_PROGRAMMER = AVR910
#AVRDUDE_PROGRAMMER = stk200
#AVRDUDE_PROGRAMMER = USBasp

AVRDUDE_PROGRAMMER = USBasp
#AVRDUDE_PROGRAMMER = bsd
#  vcc   = 2, 3, 4, 5;
#  reset = 7;
#  sck   = 8;
#  mosi  = 9;
#  miso  = 10;

AVRDUDE_PORT = usb        # programmer connected to USB port
#AVRDUDE_PORT = com1	   # programmer connected to serial device
#AVRDUDE_PORT = lpt1	       # programmer connected to parallel port

AVRDUDE_WRITE_FLASH = -U flash:w:$(TARGET).hex $(FUSE_BITS)
#AVRDUDE_WRITE_EEPROM = -U eeprom:w:$(TARGET).eep

AVRDUDE_FLAGS = -p $(MCU) -P $(AVRDUDE_PORT) -c $(AVRDUDE_PROGRAMMER)

# ---------------------------------------------------------------------------

# Define directories, if needed.
DIRAVR = C:/WinAVR-20100110 
DIRAVRBIN = $(DIRAVR)/bin
DIRAVRUTILS = $(DIRAVR)/utils/bin
DIRINC = .
DIRLIB = $(DIRAVR)/avr/lib


# Define programs and commands.
SHELL = sh

CC = avr-gcc

OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump


# Programming support using avrdude.
AVRDUDE = avrdude


REMOVE = rm -f
COPY = cp

ELFCOFF = objtool

HEXSIZE = avr-size --target=$(FORMAT) $(TARGET).hex
ELFSIZE = avr-size -A $(TARGET).elf

FINISH = echo Errors: none
BEGIN = echo -------- begin --------
END = echo --------  end  --------

# Define all object files.
OBJ = $(SRC:.c=.o) $(ASRC:.S=.o) 

# Define all listing files.
LST = $(ASRC:.S=.lst) $(SRC:.c=.lst)

# Combine all necessary flags and optional flags. Add target processor to flags.
ALL_CFLAGS = -mmcu=$(MCU) -I. $(CFLAGS)
ALL_ASFLAGS = -mmcu=$(MCU) -I. -x assembler-with-cpp $(ASFLAGS)


# Default target.
all: begin gccversion sizebefore $(TARGET).elf $(TARGET).hex $(TARGET).eep \
$(TARGET).lss sizeafter finished end


# Eye candy.
begin:
	@$(BEGIN)

finished:
	@$(FINISH)

end:
	@$(END)


# Display size of file.
sizebefore:
	@if [ -f $(TARGET).elf ]; then echo Size before:; $(ELFSIZE);fi

sizeafter:
	@if [ -f $(TARGET).elf ]; then echo Size after:; $(ELFSIZE);fi



# Display compiler version information.
gccversion : 
	$(CC) --version



# Target: Convert ELF to COFF for use in debugging / simulating in AVR Studio.
coff: $(TARGET).cof end

%.cof: %.elf
	$(ELFCOFF) loadelf $< mapfile $*.map writecof $@



# Program the device.  
program: $(TARGET).hex $(TARGET).eep
	$(AVRDUDE) $(AVRDUDE_FLAGS) $(AVRDUDE_WRITE_FLASH) $(AVRDUDE_WRITE_EEPROM)



# Create final output files (.hex, .eep) from ELF output file.
%.hex: %.elf
	$(OBJCOPY) -O $(FORMAT) -R .eeprom $< $@

%.eep: %.elf
	-$(OBJCOPY) -j .eeprom --set-section-flags=.eeprom="alloc,load" --change-section-lma .eeprom=0 -O $(FORMAT) $< $@

# Create extended listing file from ELF output file.
%.lss: %.elf
	$(OBJDUMP) -h -S $< > $@



# Link: create ELF output file from object files.
.SECONDARY : $(TARGET).elf
.PRECIOUS : $(OBJ)
%.elf: $(OBJ)
	$(CC) $(ALL_CFLAGS) $(OBJ) --output $@ $(LDFLAGS)


# Compile: create object files from C source files.
%.o : %.c
	$(CC) -c $(ALL_CFLAGS) $< -o $@


# Compile: create assembler files from C source files.
%.s : %.c
	$(CC) -S $(ALL_CFLAGS) $< -o $@


# Assemble: create object files from assembler source files.
%.o : %.S
	$(CC) -c $(ALL_ASFLAGS) $< -o $@


# Target: clean project.
clean: begin clean_list finished end

clean_list :
	$(REMOVE) $(TARGET).hex
	$(REMOVE) $(TARGET).eep
	$(REMOVE) $(TARGET).obj
	$(REMOVE) $(TARGET).cof
	$(REMOVE) $(TARGET).elf
	$(REMOVE) $(TARGET).map
	$(REMOVE) $(TARGET).obj
	$(REMOVE) $(TARGET).a90
	$(REMOVE) $(TARGET).sym
	$(REMOVE) $(TARGET).lnk
	$(REMOVE) $(TARGET).lss
	$(REMOVE) $(OBJ)
	$(REMOVE) $(LST)
	$(REMOVE) $(SRC:.c=.s)
	$(REMOVE) $(SRC:.c=.d)


# Automatically generate C source code dependencies. 
# (Code originally taken from the GNU make user manual and modified (See README.txt Credits).)
# Note that this will work with sh (bash) and sed that is shipped with WinAVR (see the SHELL variable defined above).
# This may not work with other shells or other seds.
%.d: %.c
	set -e; $(CC) -MM $(ALL_CFLAGS) $< \
	| sed 's,\(.*\)\.o[ :]*,\1.o \1.d : ,g' > $@; \
	[ -s $@ ] || rm -f $@


# Remove the '-' if you want to see the dependency files generated.
-include $(SRC:.c=.d)



# Listing of phony targets.
.PHONY : all begin finish end sizebefore sizeafter gccversion coff clean clean_list


