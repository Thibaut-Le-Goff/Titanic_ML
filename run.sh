!#/bin/bash

gcc parse_csv.c -o parse_csv
valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all -s ./parse_csv 
