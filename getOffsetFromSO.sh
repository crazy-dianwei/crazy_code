#!/bin/bash

name=`echo $1 | cut -d. -f1`

objdump -D $1 > ${name}.info

key=$2@plt\>\:

line=`cat -n ${name}.info | grep "$key" | awk '{print $1}'`
let line=line+1

num=`cat -n ${name}.info | sed -n "${line}p" | cut -d# -f 2 | awk '{print $1}'`

echo $num > ${name}_$2.file

chmod +r ${name}_$2.file