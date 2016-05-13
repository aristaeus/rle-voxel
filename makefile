CC=g++
OUT=vox
OBJ=wrap.o rle.o main.o
LIB=-lsfml-window -lsfml-system

all: $(OBJ)
	$(CC) $(OBJ) $(LIB) -o $(OUT)
	rm *.o
