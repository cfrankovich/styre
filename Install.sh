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
ver="1.0"

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
	echo -e "DIR \"${STYREDIR}\"\nCGOAL \"\"\nNUMLIST \"0\"\nDEFCOM \"-g\"\n" > config 
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
echo -e "${neu} Compiling source code."
cd $SRCDIR 
make >/dev/null 2>&1
if [ -e styre ]
then
	echo -e "${pos} Code compiled successfully!"
else
	echo -e "${neg} Code failed to compile!"
	exit 1
fi

# Move to bin #
echo -e "${neu} Moving binary"
sudo mv styre /usr/bin/styre
if [ -e /usr/bin/styre ]
then
	echo -e "${pos} Move complete!"
else
	echo -e "${neg} Could not move bianry"
fi

# Finish #
echo -e "${pos} Styre version ${ver} has been installed!\n" 

