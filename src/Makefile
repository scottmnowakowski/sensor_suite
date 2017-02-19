# Assumes stlink is installed system-wide

SRCS=main.c system_stm32f4xx.c stm32f4xx_it.c newlib_stubs.c my_printf.c I2C1.c lsm9ds0.c

# Library modules
SRCS += stm32f4xx_gpio.c stm32f4xx_rcc.c stm32f4xx_usart.c stm32f4xx_sdio.c stm32f4xx_syscfg.c stm32f4xx_exti.c misc.c stm32f4xx_i2c.c

SRCS += startup_stm32f4xx.s

LIBS = -lm -lc

# Binaries will be generated with this name (.elf, .bin, .hex, etc)
PROJ_NAME=sensorsuite

#######################################################################################

STM_COMMON=../STM32F4-Discovery_FW_V1.1.0

CC_PATH=/usr/local/arm/
CC=$(CC_PATH)/bin/arm-none-eabi-gcc
OBJCOPY=$(CC_PATH)/bin/arm-none-eabi-objcopy

CFLAGS  = -std=c99 -O3 -Wall -Tstm32_flash.ld -DHSE_VALUE=8000000 -g -pedantic
CFLAGS += -DUSE_STDPERIPH_DRIVER
CFLAGS += -mlittle-endian -mthumb-interwork
CFLAGS += -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16
CFLAGS += -I. -I../inc

# Include files from STM libraries
CFLAGS += -I$(STM_COMMON)/Libraries/CMSIS/ST/STM32F4xx/Include
CFLAGS += -I$(STM_COMMON)/Libraries/CMSIS/Include
CFLAGS += -I$(STM_COMMON)/Libraries/STM32F4xx_StdPeriph_Driver/inc

OBJS = $(SRCS:.c=.o)

vpath %.c $(STM_COMMON)/Libraries/STM32F4xx_StdPeriph_Driver/src

.PHONY: proj

all: proj

proj: $(PROJ_NAME).elf

$(PROJ_NAME).elf: $(SRCS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@ 
	$(OBJCOPY) -O ihex $(PROJ_NAME).elf $(PROJ_NAME).hex
	$(OBJCOPY) -O binary $(PROJ_NAME).elf $(PROJ_NAME).bin

clean:
	rm -f *.o
	rm -f $(PROJ_NAME).elf
	rm -f $(PROJ_NAME).hex
	rm -f $(PROJ_NAME).bin
	rm -f $(PROJ_NAME).dump
	rm -f $(STM_COMMON)/Libraries/STM32F4xx_StdPeriph_Driver/src/*.o

# Flash the STM32F4
burn: proj
	st-flash write $(PROJ_NAME).bin 0x8000000
	$(CC_PATH)/bin/arm-none-eabi-objdump -d -S $(PROJ_NAME).elf  > $(PROJ_NAME).dump
