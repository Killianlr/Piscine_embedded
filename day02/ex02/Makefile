NAME = main
BIN = $(NAME).bin
HEX = $(NAME).hex
CC = avr-gcc
OBJCPY = avr-objcopy
SOURCES = main.c
USB_DEV ?= /dev/ttyUSB0

F_CPU ?= 16000000UL
UART_BAUD ?= 115200

CFLAGS = -Wall -Wextra -Werror -Os -DF_CPU=$(F_CPU) -DUART_BAUD=$(UART_BAUD) -mmcu=atmega328p

all: hex flash

hex: $(SOURCES)
	$(CC) $(CFLAGS) $^ -o $(BIN)
	$(OBJCPY) $(BIN) $(HEX)

flash:
	avrdude -c arduino -b $(UART_BAUD) -p m328p -P $(USB_DEV) -U flash:w:./$(HEX)

screen:
	screen $(USB_DEV) $(UART_BAUD)

clean:
	rm -f $(BIN) $(HEX)

.PHONY: all clean flash screen hex