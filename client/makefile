# Compilador
CXX = g++

# Buscar todos los .cpp (menos el ejecutable final)
SRC = $(wildcard *.cpp)

# Nombre del ejecutable
TARGET = sdl

# Archivos objeto (cada .cpp → .o)
OBJ = $(SRC:.cpp=.o)

# Flags de compilación
CXXFLAGS = \
    -fPIC \
    -I/usr/include/x86_64-linux-gnu/qt5 \
    -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets \
    -I/usr/include/x86_64-linux-gnu/qt5/QtGui \
    -I/usr/include/x86_64-linux-gnu/qt5/QtCore \
    $(shell sdl2-config --cflags)

# Flags de linkeo
LDFLAGS = \
    -lQt5Widgets -lQt5Gui -lQt5Core \
    $(shell sdl2-config --libs)

# Regla principal
all: $(TARGET)

# Enlazado final
$(TARGET): $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

# Regla de compilación individual
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpiar archivos generados
clean:
	rm -f $(TARGET) $(OBJ)
