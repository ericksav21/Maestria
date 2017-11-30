#!/bin/sh

prefix="data/"
FILES=data/*.pgm
for f in $FILES
do
	ff=${f#$prefix}
	if [ $1 = '1' ]
	then
		./main --file $ff -S 2841 --algo UMDA --psize 100 --ngenerations 200 --srate 0.4 -V
	else
		./main --file $ff -S 2841 --algo Genetic --psize 100 --ngenerations 200 --urate 0.5 --mrate 0.015 -V
	fi
done
