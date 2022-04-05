#!bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

echo -ne "${NC}invalid map unclosed begin: "
./cub3D maps/invalid_map_unclose_begin.cub >> /dev/null && echo -e "${RED}KO" || echo -e "${GREEN}OK"

echo -ne "${NC}invalid map unclosed end: "
./cub3D maps/invalid_map_unclose_end.cub >> /dev/null && echo -e "${RED}KO" || echo -e "${GREEN}OK"

echo -ne "${NC}invalid map border bottom: "
./cub3D maps/invalid_map_border_bottom.cub >> /dev/null && echo -e "${RED}KO" || echo -e "${GREEN}OK"

echo -ne "${NC}invalid map border top: "
./cub3D maps/invalid_map_border_top.cub >> /dev/null && echo -e "${RED}KO" || echo -e "${GREEN}OK"

echo -ne "${NC}invalid map no player: "
./cub3D maps/invalid_map_no_player.cub >> /dev/null && echo -e "${RED}KO" || echo -e "${GREEN}OK"

echo -ne "${NC}invalid map char F: "
./cub3D maps/invalid_map_char_f.cub >> /dev/null && echo -e "${RED}KO" || echo -e "${GREEN}OK"

echo -ne "${NC}valid map: "
./cub3D maps/valid_map.cub >> /dev/null && echo -e "${GREEN}OK" || echo -e "${RED}KO"