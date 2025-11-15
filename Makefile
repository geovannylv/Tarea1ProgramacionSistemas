# 4. Makefile 

CC = gcc
CFLAGS = -Wall

SRC = Main.c Usuarios.c Productos.c
OBJ = Main.o Usuarios.o Productos.o

TARGET = sistema

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

asm:
	$(CC) -S Main.c
	$(CC) -S Usuarios.c
	$(CC) -S Productos.c

objdump:
	objdump -d Main.o > Main_dump.s
	objdump -d Usuarios.o > Usuarios_dump.s
	objdump -d Productos.o > Productos_dump.s

clean:
	rm -f *.o

cleanall:
	rm -f *.o *.s $(TARGET)
