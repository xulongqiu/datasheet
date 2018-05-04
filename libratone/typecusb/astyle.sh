#########################################################################
# File Name: astyle.sh
# Author: eric.xu
# mail: eric.xu@libratone.com.cn
# Created Time: 2017年01月25日 星期三 16时29分19秒
#########################################################################
#!/bin/bash

if [ $# -ne 1 ];then
    echo "Usage $0 directory"
    exit 1
fi

if [ -d $1 ];then
    dir=$1
else
    echo "$1 isn't a file or directory"
    exit 1
fi

for file in `find ${dir} -name "*.[ch]" -o -name "*.cpp"`; do
    echo $file
    dos2unix $file
    astyle --style=linux --indent=spaces=4 --align-pointer=name -M80 -f -k1 -j -p -U -H -c -w -n -X -c $file
done
