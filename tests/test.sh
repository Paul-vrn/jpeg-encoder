#!/bin/bash

if ! test -f "../ppm2jpeg"; then 
    echo "generate ppm2jpeg"
    make -C ../
fi

for file in `find ../images -name "*.ppm"`;
do
    filename="${file%.*}"
    echo $filename
    if ! test -f "$filename-out.jpg"; then
        ../ppm2jpeg $file > /dev/null --outfile=$filename-out.jpg
    fi
    if ! test -f "$filename-out2.jpg"; then
        ../bin_prof/ppm2blabla $file --outfile=$filename-out2.jpg
    fi
    result=$(compare -metric NCC $filename-out.jpg $filename-out2.jpg /dev/null 2>&1);
    echo "$result percentage of similarity for $filename.jpg"
done
make -C ../ clean
exit 0;
