# Compilador
CXX = g++

# Archivos fuente .cpp
SRC = $(wildcard *.cpp)

# Archivo header que usa Q_OBJECT
HDR = lobbyView.h

# Archivo moc generado
MOC_CPP = moc_lobbyView.cpp

# Objetos de los .cpp
OBJ = $(SRC:.cpp=.o)

# Objeto del moc
MOC_OBJ = moc_lobbyView.o

# Ejecutable final
TARGET = sdl

# Flags compilación
CXXFLAGS = \
    -fPIC \
    -I/usr/include/x86_64-linux-gnu/qt5 \
    -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets \
    -I/usr/include/x86_64-linux-gnu/qt5/QtGui \
    -I/usr/include/x86_64-linux-gnu/qt5/QtCore \
    $(shell sdl2-config --cflags)

# Flags linkeo
LDFLAGS = \
    -lQt5Widgets -lQt5Gui -lQt5Core \
    $(shell sdl2-config --libs) -lSDL2_image

# Regla principal
all: $(TARGET)

# Linkeo
$(TARGET): $(OBJ) $(MOC_OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

# Regla compilación individual
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Generar moc
$(MOC_CPP): $(HDR)
	moc $(HDR) -o $(MOC_CPP)

# Compilar moc
$(MOC_OBJ): $(MOC_CPP)
	$(CXX) $(CXXFLAGS) -c $(MOC_CPP) -o $(MOC_OBJ)

# Limpiar
clean:
	rm -f $(TARGET) $(OBJ) $(MOC_OBJ) $(MOC_CPP)
