#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

echo -en "${NC}0) Description in the middel: "
(./cub3D maps/invalid_map_description_middle.cub >> /dev/null) && echo -e "${RED} KO" || echo -e "${GREEN}OK"

echo -en "${NC}1) Unautorized char (diff of NSEW01): "
(./cub3D maps/invalid_map_char.cub >> /dev/null) && echo -e "${RED} KO" || echo -e "${GREEN}OK"

echo -en "${NC}2) More than 3 textures "
(./cub3D maps/invalid_map_multiple_occurence.cub >> /dev/null) && echo -e "${RED} KO" || echo -e "${GREEN}OK"

echo -en "${NC}3) Valid config file: "
(./cub3D maps/valid_map.cub >> /dev/null) && echo -e "${GREEN}OK" || echo -e "${RED}KO"