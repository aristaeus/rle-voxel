CC=g++
OUT=vox
FILE=wrap rle main
LIB=-lsfml-window -lsfml-system -lGL -lGLEW
CXXFLAGS=-g -Wall
BUILDIR=build/
SRCDIR=src/
INCDIR=include/

OBJ=$(addprefix $(BUILDIR),$(addsuffix .o, $(FILE)))

all: $(OBJ)
	$(CC) $(OBJ) $(LIB) -o $(BUILDIR)$(OUT)
	cp resources/* $(BUILDIR)

build/%.o: src/%.cpp
	$(CC) $(CXXFLAGS) -c -o  $@ $< -I$(INCDIR)

clean:
	rm -f $(BUILDIR)*
