arm-linux-gnueabihf-gcc  -g  -Os   -ffunction-sections -fdata-sections -fno-common -ffixed-r8 -msoft-float  -D__KERNEL__ -DCONFIG_SYS_TEXT_BASE=0x4a000000 -I./include/asm/ -fno-builtin -ffreestanding -nostdinc -isystem /usr/lib/gcc/arm-linux-gnueabi/4.8.1/include -pipe  -DCONFIG_ARM -D__ARM__ -marm -mno-thumb-interwork -mabi=aapcs-linux -march=armv7-a -Wall -Wstrict-prototypes -fno-stack-protector -Wno-format-nonliteral -Wno-format-security -fstack-usage -fno-toplevel-reorder     -o hello_world.o hello_world.c -c
arm-linux-gnueabihf-ld  -g -Ttext 0x50000000 \
                -o hello_world -e hello_world hello_world.o -L/usr/lib/gcc/arm-linux-gnueabi/4.8.1 -lgcc
arm-linux-gnueabihf-objcopy -O binary hello_world hello_world.bin
