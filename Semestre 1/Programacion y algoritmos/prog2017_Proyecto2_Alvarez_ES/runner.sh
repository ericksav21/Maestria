#!/bin/sh

prefix="data/"
FILES=data/*.pgm
for f in $FILES
do
	ff=${f#$prefix}
	if [ $1 = '1' ]
	then
		./main --file $ff -S 1550 --algo UMDA --psize 30 --ngenerations 50 --srate 0.6 -V
	else
		./main --file $ff -S 1710 --algo Genetic --psize 50 --ngenerations 100 --urate 0.5 --mrate 0.015 -V
	fi
done
