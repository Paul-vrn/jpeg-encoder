#!/bin/bash
# script qui va générer les .jpeg de tous les .ppm avec notre programme et celui des profs puis comparer les résultats avec compare et enfin supprimer les fichiers générés
if ! test -f "../ppm2jpeg"; then 
    echo "generate ppm2jpeg"
    make -C ../
fi
if test -f "./result.txt"; then
    rm result.txt
fi
for file in `find ../images -name "*.ppm"`;
do
    filename="${file%.*}"
    if ! test -f "$filename-out.jpg"; then
        ../ppm2jpeg $file > /dev/null --outfile=$filename-out.jpg $1
    fi
    if ! test -f "$filename-out2.jpg"; then
        ../bin_prof/ppm2blabla $file --outfile=$filename-out2.jpg $1
    fi
    result=$(compare -metric NCC $filename-out.jpg $filename-out2.jpg /dev/null 2>&1);
    echo "$result percentage of similarity for $filename.jpg" >> result.txt
done
make -C ../ clean
exit 0;
