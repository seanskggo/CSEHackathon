#!/usr/bin/bash

for i in {1000..5000}; do
    postcode=$[RANDOM % 2000+1000 ]" "
    name=`head /dev/urandom | tr -dc A-Za-z0-9 | head -c 13 ; echo ''`
    bname='Business name'
    echo "$postcode $bname $name" >> random.txt
done
