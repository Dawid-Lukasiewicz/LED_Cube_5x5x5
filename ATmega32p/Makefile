MCU= atmega328p
CLK= 8000000UL

CFLAGS= -Wall -pedantic
TARGET_FLAGS= -mmcu=${MCU} -DF_CPU=${CLK} -O2
CC= avr-gcc
AVRDUDE= avrdude -c usbasp -p ${MCU}

__start__: Numbers.h Functions.h main.c
	${CC} ${TARGET_FLAGS} -o build.elf Numbers.h Functions.h main.c



# .objects.o: Numbers.h Functions.h main.c
# 	$(CC) $(TARGET_FLAGS) -c  

# __start__: Numbers.h Functions.h main.c
# 	$(CC) -mmcu=$(MCU) -o build.elf Numbers.h Functions.h main.c