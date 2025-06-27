#!/bin/bash

NAME="CS2D"
DESKTOP_DIR="$HOME/Desktop"
EXEC_DIR="/usr/bin"
DATA_DIR="/var/$NAME"
CONFIG_DIR="/etc/$NAME"
REPO="https://github.com/Yakolin/CS2D-grupo-13.git"
DIR="CS2D-grupo-13"

GREEN='\033[0;32m'
BLUE='\033[94m'
RED='\033[0;31m'
NC='\033[0m'

set -e
trap 'echo -e "${RED}Error: La instalación ha fallado en la línea $LINENO.${NC}"; exit 1' ERR

echo -e "${GREEN}Actualizando el sistema...${NC}"
sudo apt update
sudo apt upgrade -y

echo -e "${GREEN}Instalando herramientas básicas...${NC}"
sudo apt install -y git build-essential cmake make

echo -e "${GREEN}Clonando el repositorio del juego...${NC}"
git clone "$REPO"
cd "$DIR"

echo -e "${GREEN}Instalando dependencias del juego...${NC}"
sudo apt install -y \
  libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev \
  qtbase5-dev qt5-qmake qtmultimedia5-dev \
  libqt5charts5-dev \
  libsdl2-gfx-dev \
  libyaml-cpp-dev \
  libopusfile-dev libxmp-dev libfluidsynth-dev fluidsynth \
  libwavpack-dev libfreetype6-dev

# Instalación explícita por si hiciera falta
sudo apt-get install -y libsdl2-mixer-dev

# Dependencias multimedia adicionales para Qt y GStreamer
sudo apt install -y \
  gstreamer1.0-plugins-base \
  gstreamer1.0-plugins-good \
  gstreamer1.0-plugins-bad \
  gstreamer1.0-plugins-ugly \
  gstreamer1.0-libav \
  gstreamer1.0-plugins-base-apps \
  libqt5multimedia5-plugins

printf '%*s\n' "$(tput cols)" | tr ' ' '-'

echo -e "${GREEN}Compilando el proyecto...${NC}"
mkdir -p build
cd build
cmake ..
make -j$(nproc)
cd ..

printf '%*s\n' "$(tput cols)" | tr ' ' '-'

echo -e "${GREEN}Instalando ejecutables en $EXEC_DIR...${NC}"
sudo cp build/CS2D_client "$EXEC_DIR"
sudo cp build/CS2D_server "$EXEC_DIR"

echo -e "${GREEN}Instalando assets en $DATA_DIR y configuraciones en $CONFIG_DIR...${NC}"
sudo mkdir -p "$DATA_DIR" "$CONFIG_DIR/server_config/maps"

sudo cp -r assets/* "$DATA_DIR"
sudo cp -r server/game/Map/Maps/* "$CONFIG_DIR/server_config/maps"
sudo cp server/game/Config/GameConfig.yaml "$CONFIG_DIR/server_config"
sudo cp server/protocol/server_config.yaml "$CONFIG_DIR/server_config"

printf '%*s\n' "$(tput cols)" | tr ' ' '-'
echo -e "${BLUE}Creando ejecutables en $DESKTOP_DIR.${NC}"
sudo cp ./client.sh "$DESKTOP_DIR"
sudo cp ./server.sh "$DESKTOP_DIR"
echo -e "${GREEN}Instalación completa.${NC}"