#!/bin/bash

NAME="CS2D"
EXEC_DIR="/usr/bin"
DATA_DIR="/var/$NAME"
CONFIG_DIR="/etc/$NAME"


# Define color codes
GREEN='\033[0;32m'
BLUE='\033[94m'
RED='\033[0;31m'
NC='\033[0m'  

set -e # Finalizar ante error
trap 'echo -e "${RED}Error: La instalación ha fallado en la línea $LINENO.${NC}"; exit 1' ERR



# Descargar e instalar dependencias
echo -e "${GREEN}Instalando dependencias...${NC}"
sudo apt update
sudo apt install -y git cmake libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev qtbase5-dev qt5-qmake qtmultimedia5-dev libyaml-cpp-dev

printf '%*s\n' "$(tput cols)" | tr ' ' '-'

# Compilar el proyecto

sudo cp build/CS2D_client "$EXEC_DIR"
sudo cp build/CS2D_server "$EXEC_DIR"


# Copiar assets y archivos de configuracion

echo -e "${GREEN}Instalando binarios en $EXEC_DIR, assets en $DATA_DIR y configuraciones en $CONFIG_DIR...${NC}"
sudo mkdir -p "$DATA_DIR" "$CONFIG_DIR" "$CONFIG_DIR/server_config" "$CONFIG_DIR/server_config/maps"

if [ ! -f build/CS2D_client ] || [ ! -f build/CS2D_server ]; then
    echo -e "${RED}Error: No se encontraron los binarios. ¿Te olvidaste de compilar?${NC}"
    exit 1
fi

# Assets

sudo cp -r assets/* "$DATA_DIR"

#Config del server
sudo cp -r server/game/Map/Maps/* "$CONFIG_DIR/server_config/maps"
sudo cp -r server/game/Config/GameConfig.yaml "$CONFIG_DIR/server_config"
sudo cp -r server/protocol/server_config.yaml "$CONFIG_DIR/server_config"

printf '%*s\n' "$(tput cols)" | tr ' ' '-'

echo -e "${GREEN}Instalación completa.${NC}"
