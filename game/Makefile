RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
RESET = \033[0m

#Archivos
Ejecutable = juego
CPP = $(wildcard *.cpp)
HEADERS = $(wildcard *.h)

#Compilacion
FLAGS = g++ -Wall -Wextra -Wpedantic -Wreorder -Wunused -Werror=return-type

VALGRIND_FLAGS = --leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2 --show-leak-kinds=all --trace-children=yes

compile: $(CPP) $(HEADERS)
	@echo "${BLUE}Analizando código con cppcheck...${RESET}" 
	cppcheck --inline-suppr --enable=all --suppress=missingIncludeSystem --suppress=missingInclude --suppress=unusedFunction --suppress=unusedStructMember --suppress=unmatchedSuppression --language=c++ --std=c++20 --error-exitcode=1 .
	@echo "${GREEN}Compilando el ejecutable $(Ejecutable) ${RESET}"
	$(FLAGS) $(CPP) -o $(Ejecutable)

test: compile
	@echo "${YELLOW}Ejecutando tests${RESET}" 
	./$(Ejecutable) 


test-valgrind: compile
	@echo "${YELLOW}Ejecutando tests con valgrind${RESET}" 
	valgrind $(VALGRIND_FLAGS) ./$(Ejecutable) 


all: clean test-valgrind 

clean: 
	@echo  "${RED} Limpiando archivos... ${RESET}"
	@rm -f $(Ejecutable)