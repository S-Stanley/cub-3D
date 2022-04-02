#!bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

echo -ne "${NC}Test config file with texture path file do not exist: "
./cub3D maps/invalid_example_subject.cub >> /dev/null && echo -e "${RED}KO" || echo -e "${GREEN}OK"


echo -ne "${NC}Test config file with missing texture: "
./cub3D maps/invalid_map_texture.cub >> /dev/null && echo -e "${RED}KO" || echo -e "${GREEN}OK"

echo -ne "${NC}Test config file with correct textures and path: "
./cub3D maps/valid_map.cub >> /dev/null && echo -e "${GREEN}OK" || echo -e "${RED}KO"