#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

echo -en "${NC}0) Invalid map floor: "
(./cub3D maps/invalid_map_floor.cub >> /dev/null) && echo -e "${RED} KO" || echo -e "${GREEN}OK"

echo -en "${NC}1) Valid map: "
(./cub3D maps/valid_map.cub >> /dev/null) && echo -e "${GREEN} OK" || echo -e "${RED}KO"