#!/bin/bash

NAME="CS2D"
EXEC_DIR="/usr/bin"
DATA_DIR="/var/$NAME"
CONFIG_DIR="/etc/$NAME"

# Colores
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

set -e
trap 'echo -e "${RED}Error: La desinstalación ha fallado en la línea $LINENO.${NC}"; exit 1' ERR

echo -e "${GREEN}Desinstalando $NAME...${NC}"

# Eliminar binarios
sudo rm -f "$EXEC_DIR/CS2D_client"
sudo rm -f "$EXEC_DIR/CS2D_server"

# Eliminar assets y configuración
sudo rm -rf "$DATA_DIR"
sudo rm -rf "$CONFIG_DIR"

echo -e "${GREEN}Desinstalación completa.${NC}"
