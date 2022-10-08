#!/bin/bash

cat ./images/cat_headache | sed -e "s/%%/$(tput setaf 216)\%%$(tput sgr0)/g" -e "s/\#/$(tput setaf 216)\\#$(tput sgr0)/g" -e "s/\&/$(tput setaf 1)\\&$(tput sgr0)/g" -e "s/((/$(tput setaf 1)\(($(tput sgr0)/g"
