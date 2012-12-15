PRG            = mollusk
OBJ            = mollusk.o
PROGRAMMER     = avrisp2
PORT           = usb
MCU_TARGET     = attiny44
AVRDUDE_TARGET = t44
OPTIMIZE       = -Os -fpack-struct -fshort-enums -funsigned-char -funsigned-bitfields -ffunction-sections -fdata-sections
DEFS           =
LIBS           =

#BAUDRATE       = 57600
HZ             = 8000000L

# You should not have to change anything below here.
CC             = avr-gcc
CXX            = avr-gcc

# Override is only needed by avr-lib build system.


override CFLAGS        = -std=c99 -g -DF_CPU=$(HZ) -Wall $(OPTIMIZE) -mmcu=$(MCU_TARGET) $(DEFS)
override LDFLAGS       = -Wl,-Map,$(PRG).map -s -Wl,--gc-sections
override CPPFLAGS      = -std=c99 -g -DF_CPU=$(HZ) -Wall $(OPTIMIZE) -fvtable-gc -mmcu=$(MCU_TARGET) $(DEFS)

OBJCOPY        = avr-objcopy
OBJDUMP        = avr-objdump

all: $(PRG).elf lst text #eeprom

$(PRG).elf: $(OBJ)
	$(CC) -std=c99 $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS) 

clean:
	rm -rf *.o $(PRG).elf *.eps *.png *.pdf *.bak *.hex *.bin *.srec
	rm -rf *.lst *.map $(EXTRA_CLEAN_FILES)

lst:  $(PRG).lst

%.lst: %.elf
	$(OBJDUMP) -h -S $< > $@

# Rules for building the .text rom images

text: hex bin srec

hex:  $(PRG).hex
bin:  $(PRG).bin
srec: $(PRG).srec

%.hex: %.elf
	$(OBJCOPY) -j .text -j .data -O ihex $< $@

%.srec: %.elf
	$(OBJCOPY) -j .text -j .data -O srec $< $@

%.bin: %.elf
	$(OBJCOPY) -j .text -j .data -O binary $< $@

# Rules for building the .eeprom rom images

flash:  $(PRG).hex
	avrdude -p $(AVRDUDE_TARGET) -c $(PROGRAMMER) -P $(PORT) -v  \
         -U flash:w:$(PRG).hex #-U eeprom:w:$(PRG).eep

fuse:
	avrdude -p $(AVRDUDE_TARGET) -c $(PROGRAMMER) -P $(PORT) -v \
	-U lfuse:w:lfuse.hex:h -U hfuse:w:hfuse.hex:h 	

ddd: gdbinit
	ddd --debugger "avr-gdb -x $(GDBINITFILE)"

gdbserver: gdbinit
	simulavr --device $(MCU_TARGET) --gdbserver

gdbinit: $(GDBINITFILE)

$(GDBINITFILE): $(PRG).hex
	@echo "file $(PRG).elf" > $(GDBINITFILE)

	@echo "target remote localhost:1212" >> $(GDBINITFILE)
	@echo "load"                         >> $(GDBINITFILE)
	@echo "break main"                   >> $(GDBINITFILE)
	@echo
	@echo "Use 'avr-gdb -x $(GDBINITFILE)'"