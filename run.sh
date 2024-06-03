!#/bin/bash

# don't work with -std=c99 because strsep is not a c standard
gcc -std=gnu99 -g -Wall -Wextra -pedantic-errors -fstrict-aliasing -fstack-protector-all -fPIE -Werror -Wfatal-errors parse_csv.c -o parse_csv
valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all -s ./parse_csv 
