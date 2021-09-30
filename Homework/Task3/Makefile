CXX       = gcc
WARNINGS  = -Wall -Wextra 

DEBUG_MODE   = -g3 -O0 
RELEASE_MODE = -g0 -O3

VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all

EXEC_DIR = ./executer
LIBS_DIR = ./libs
TEXT_DIR = ./text

SOURCE = $(EXEC_DIR)/executer.c $(EXEC_DIR)/main.c $(LIBS_DIR)/split_func.c $(TEXT_DIR)/text.c
OBJECT = $(SOURCE:.c=.o)
OUTPUT = executer_output

default: launch

launch: $(OUTPUT)
	./$(OUTPUT) "input_commands"

debug: $(OUTPUT)
	valgrind $(VALGRIND_FLAGS) ./$(OUTPUT) "input_commands"

$(OUTPUT): $(OBJECT)
	$(CXX) $(WARNINGS) $(DEBUG_MODE) $^ -o $(OUTPUT)

main.o: $(EXEC_DIR)/main.c
	$(CXX) -c $^

executer.o: $(EXEC_DIR)/executer.c
	$(CXX) -c $^

split_func.o: $(LIBS_DIR)/split_func.c
	$(CXX) -c $^

text.o: $(TEXT_DIR)/text.c
	$(CXX) -c $^
	
clean:
	rm -f *.o *.a $(OBJECT) $(OUTPUT)