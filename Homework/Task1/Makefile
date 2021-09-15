CXX       = gcc
WARNINGS  = -Wall -Wextra 

DEBUG_MODE   = -g3 -O0 
RELEASE_MODE = -g0 -O3

VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all

SOURCE = main.c split_func.c
OBJECT = $(SOURCE:.c=.o)
OUTPUT = split_out

default: launch

launch: $(OUTPUT)
	./$(OUTPUT)

debug: $(OUTPUT)
	valgrind $(VALGRIND_FLAGS) ./$(OUTPUT)

$(OUTPUT): $(OBJECT)
	$(CXX) $(WARNINGS) $(DEBUG_MODE) $^ -o $(OUTPUT)

main.o: main.c
	$(CXX) -c $^

split_func.o: split_func.c
	$(CXX) -c $^

clean:
	rm -f *.o *.a $(OBJECT) $(OUTPUT)