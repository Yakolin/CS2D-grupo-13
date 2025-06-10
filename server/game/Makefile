RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
RESET = \033[0m

#Archivos
Ejecutable = juego
CPP = $(wildcard *.cpp) \
	  $(wildcard Map/*.cpp) \
	  $(wildcard Config/*.cpp) \
      $(wildcard Player/*.cpp) \
	  $(wildcard Weapons/*.cpp) \
	  $(wildcard Colliders/*.cpp) \
      $(wildcard ../protocol/*.cpp) \
      $(wildcard ../../common/*.cpp)

HEADERS = $(wildcard *.h) \
          $(wildcard ../protocol/*.h) \
          $(wildcard ../../common/*.h)

#Compilacion
FLAGS = g++ -Wpedantic -Wreorder -Werror=return-type

VALGRIND_FLAGS = --leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2 --show-leak-kinds=all --trace-children=yes

compile: $(CPP) $(HEADERS)
	@echo "${BLUE}Analizando código con cppcheck...${RESET}" 
	$(FLAGS) $(CPP) -o $(Ejecutable) -lyaml-cpp

test: compile
	@echo "${YELLOW}Ejecutando tests${RESET}" 
	./$(Ejecutable) 


test-valgrind: compile
	@echo "${YELLOW}Ejecutando tests con valgrind${RESET}" 
	valgrind $(VALGRIND_FLAGS) ./$(Ejecutable) 


all: clean test-valgrind 
gdb: 
	@echo "${YELLOW}Ejecutando tests con GDB${RESET}" 
	gdb ./$(Ejecutable) 
clean: 
	@echo  "${RED} Limpiando archivos... ${RESET}"
	@rm -f $(Ejecutable)