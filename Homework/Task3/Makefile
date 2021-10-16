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

debug: $(OUTPUT)
	valgrind $(VALGRIND_FLAGS) ./$(OUTPUT) "input_commands"

launch: $(OUTPUT)
	./$(OUTPUT) "input_commands"

$(OUTPUT): $(OBJECT)
	$(CXX) $(DEBUG_MODE) $(OBJECT) -o $@

.c.o: $(CXX) -c $(WARNINGS) $< -o $@

clean:
	rm -f *.o *.a $(OBJECT) $(OUTPUT)

#==========================================================================================