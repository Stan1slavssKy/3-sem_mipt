#==========================================================================================

CXX       = gcc
WARNINGS  = -Wall -Wextra 

DEBUG_MODE   = -g3 -O0 
RELEASE_MODE = -g0 -O3
VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all

EXEC_DIR = ./run_processes
SOURCE = $(EXEC_DIR)/split.c $(EXEC_DIR)/run_processes.c
OBJECT = $(SOURCE:.c=.o)
OUTPUT = executer_output

default: launch

launch: $(OUTPUT)
	./$(OUTPUT) "input_commands"

$(OUTPUT): $(OBJECT)
	$(CXX) $(WARNINGS) $(DEBUG_MODE) $^ -o $(OUTPUT)

run_processes.o: $(EXEC_DIR)/run_processes.c
	$(CXX) -c $^

split.o: $(EXEC_DIR)/split.c
	$(CXX) -c $^

clean:
	rm -f *.o *.a $(OBJECT) $(OUTPUT) 

#==========================================================================================