#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

echo -en "${NC}0) not enouth args: "
(./cub3D >> /dev/null) && echo -e "${RED} KO" || echo -e "${GREEN}OK"

echo -en "${NC}1) too much args: "
(./cub3D arg1 arg2 >> /dev/null) && echo -e "${RED} KO" || echo -e "${GREEN}OK"

echo -en "${NC}2) without extention: "
(./cub3D parsingfile >> /dev/null) && echo -e "${RED} KO" || echo -e "${GREEN}OK"

echo -en "${NC}3) without only extention: "
(./cub3D .cub >> /dev/null) && echo -e "${RED} KO" || echo -e "${GREEN}OK"

echo -en "${NC}4) wrong extention: "
(./cub3D toparse.txt >> /dev/null) && echo -e "${RED} KO" || echo -e "${GREEN}OK"

echo -en "${NC}5) file do not exist: "
(./cub3D toparse.cub >> /dev/null) && echo -e "${RED} KO" || echo -e "${GREEN}OK"

mkfile 0 toparse.cub

chmod 000 toparse.cub
echo -en "${NC}5) wrong access right do not exist: "
(./cub3D toparse.cub >> /dev/null) && echo -e "${RED} KO" || echo -e "${GREEN}OK"

chmod +r toparse.cub

echo -en "${NC}6) good information: "
(./cub3D toparse.cub >> /dev/null) && echo -e "${GREEN} OK" || echo -e "${RED}KO"

chmod +w toparse.cub
rm toparse.cub