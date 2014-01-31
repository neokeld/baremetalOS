SOURCES=baremetal_os.c uart.c console.c gpio.c memory.c led.c command.c
CC=arm-linux-gnueabihf-gcc
ARMLD=arm-linux-gnueabihf-ld
OBJCPY=arm-linux-gnueabihf-objcopy
CFLAGS=-g  -O0 -ffunction-sections -fdata-sections -fno-common -ffixed-r8 -msoft-float -D__KERNEL__ -DCONFIG_SYS_TEXT_BASE=0x4a000000 -I./include/asm/ -fno-builtin -ffreestanding -nostdinc -pipe -DCONFIG_ARM -D__ARM__ -marm -mno-thumb-interwork -mabi=aapcs-linux -march=armv7-a -Wall -Wstrict-prototypes -fno-stack-protector -Wno-format-nonliteral -Wno-format-security -fstack-usage -fno-toplevel-reorder 
LDFLAGS=-g -Ttext 0x50000000 -L -lgcc
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=baremetal_os
EXEBIN=$(EXECUTABLE).bin

all: clean $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(ARMLD) $(LDFLAGS) -o $(EXECUTABLE) -e $(EXECUTABLE) $(OBJECTS) 
	$(OBJCPY) -O binary $(EXECUTABLE) $(EXEBIN)

clean: 
	rm -f $(OBJECTS) *.su

mrproper: clean
	rm $(EXECUTABLE) $(EXEBIN)

send:
	scripts/send_image $(EXEBIN) 0x50000000

.c.o:
	$(CC) $(CFLAGS) $< -o $@ -c
