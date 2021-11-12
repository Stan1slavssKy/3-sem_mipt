#==========================================================================================

CXX       = gcc
WARNINGS  = -Wall -Wextra 

DEBUG_MODE   = -g3 -O0 
RELEASE_MODE = -g0 -O3
VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all

SOURCE = matrix_mul.c
OBJECT = $(SOURCE:.c=.o)
OUTPUT = matrix_mul_output

default: launch

launch: $(OUTPUT)
	./$(OUTPUT)

valgrind: $(OUTPUT)
	valgrind ./$(OUTPUT)
	
$(OUTPUT): $(OBJECT)
	$(CXX) $(WARNINGS) $(DEBUG_MODE) $^ -o $(OUTPUT)
 
matrix_mul.c.o: matrix_mul.c
	$(CXX) -c $^

clean:
	rm -f *.o *.a $(OBJECT) $(OUTPUT) 

#==========================================================================================