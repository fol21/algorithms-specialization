# C/C++ compiler
CC = gcc  
CXX = g++

# Linker
LD = ld

# Libraries to link with (include '-l')
LIBS = -pthread -lpthread -lrt -fopenmp 

# Compiler and linker flags (warning levels, optimisation level, 
LINKS = -lm

# include debugging symbols, add include search path, add library search path)
CFLAGS = -Wall -Iinclude -std=c++11 -fdiagnostics-color=always
OFLAGS = -g -O -c

# Folders
BIN = ./bin
OBJ = ./src/obj

#Objects
_FOBJ = specialization_algorithms.o utils.o
FOBJ := $(_FOBJ:%.o=./src/obj/%.o)

###### Dependencies #######



src/%: ./src/%.cpp ./include/%.h
	mkdir -p ./src/obj
	$(CXX) $(LIBS) ${CFLAGS} $(OFLAGS) $< -o ./src/obj/$(@F).o

# specialization_algorithms: ./src/specialization_algorithms.cpp ./include/specialization_algorithms.h
# 	$(CXX) $(LIBS) ${CFLAGS} $(OFLAGS) $< -o ./src/obj/$@.o

# utils: ./src/utils.cpp ./include/utils.h
# 	$(CXX) $(LIBS) ${CFLAGS} $(OFLAGS) $< -o ./src/obj/$@.o

dependencies:
	make src/specialization_algorithms
	make src/utils

###### Test ######

%.test : test/%.test.cpp $(FOBJ)
	make dependencies
	$(CXX) $(LIBS) $(CFLAGS) -o $(BIN)/test/$@ $^ $(LINKS)
	clear
	$(BIN)/test/$@ $(PARAMS)


###### Applications #####

# problem2 : problem2.cpp $(FOBJ)
# 	make dependencies
# 	$(CXX) $(LIBS) $(CFLAGS) -g -o $(BIN)/$@ $^ $(LINKS)

# problem3 : problem3.cpp $(FOBJ)
# 	make dependencies
# 	$(CXX) $(LIBS) $(CFLAGS) -g -o $(BIN)/$@ $^ $(LINKS)

_COURSE = ${SPEC_COURSE}
problem% : $(_COURSE)/problem%.cpp
	make dependencies
	mkdir -p ./bin
	$(CXX) $(LIBS) $(CFLAGS) -g -o $(BIN)/$@ $^ $(FOBJ) $(LINKS)

problem%.o : $(_COURSE)/problem%.cpp
	make dependencies
	mkdir -p ./obj
	$(CXX) $(LIBS) $(CFLAGS) ${OFLAGS} -o ./obj/$@ $^ $(FOBJ) $(LINKS)