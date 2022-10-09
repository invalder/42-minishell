#!/bin/bash

cat ./easter_egg/anya4 | sed -e "s/@/$(tput setaf 232)\@$(tput sgr0)/g" -e "s/ /$(tput setaf 230)\0$(tput sgr0)/g" -e "s/&/$(tput setaf 117)\&$(tput sgr0)/g" -e "s/?/$(tput setaf 255)\?$(tput sgr0)/g"
