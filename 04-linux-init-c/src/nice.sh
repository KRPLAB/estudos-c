#!/bin/sh

gcc -Wall 07_loop_escalonamento.c -o loop

nice -0  ./loop &
nice -0  ./loop &
nice -10 ./loop &
nice -10 ./loop &
nice -20 ./loop &
nice -20 ./loop &

sleep 90
killall loop
