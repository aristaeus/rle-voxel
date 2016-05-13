CC=g++
OUT=vox
OBJ=wrap.o rle.o main.o

all: $(OBJ)
	$(CC) $(OBJ) -o $(OUT)
	rm *.o
