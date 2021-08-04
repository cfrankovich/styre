#!/usr/bin/env sh

red="\e[0;91m"
blue="\e[0;94m"
green="\e[0;92m"
bold="\e[1m"
uline="\e[4m"
reset="\e[0m"

pos="[${green}${bold}+${reset}]"
neg="[${red}${bold}-${reset}]"
neu="[${blue}${bold}o${reset}]"

SRCDIR=$(pwd)

echo -e "\n${red}>${blue}>${green}> ${reset}Installing ${bold}Styre${reset} from ${bold}https://github.com/cfrankovich/styre${reset} ${green}<${blue}<${red}<${reset}\n"

# Make the .styre directory #
STYREDIR="/home/$USER/.styre"
echo -e "${neu} Creating the ${bold}.styre${reset} directory in ${bold}${STYREDIR}${reset}."
if [ ! -d $STYREDIR ]
then
	mkdir $STYREDIR
	echo -e "${pos} Created directory!"
else
	echo -e "${neg} Directory already found! Skipping process..."
fi
cd $STYREDIR

# Create config and other files #
echo -e "${neu} Creating config file."
if [ ! -e config ]
then
	touch config 
	echo -e "DIR \"${STYREDIR}\"CGOAL \"\"\nNUMLIST \"0\"\nDEFCOM \"G\"\n" > config 
	echo -e "${pos} Config file created!"
else
	echo -e "${neg} Config file already found! Skipping process..."
fi 

echo -e "${neu} Creating lists file."
if [ ! -e lists ]
then
	touch lists
	echo -e "${pos} Created lists file!"
else
	echo -e "${neg} Lists file already found! Skipping process..."
fi

echo -e "${neu} Creating lists directory."
if [ ! -d Lists ]
then
	mkdir Lists
	echo -e "${pos} Created lists directory!"
else
	echo -e "${neg} Directory already exists! Skipping process..."
fi

# Compile #

# Move to bin #

# Finish #
echo -e "${pos} Installation complete! Please run ${bold}styre -h${reset} for help.\n" 

