#!/bin/sh
#declaration
srcstring=$1
srcfilename=$2
desfilename=$3
#

#check the legalization of srcfilename
if [ ! -f "$srcfilename" ] #only check on this folder, I don't know how to do it further
then echo > "$desfilename" "Tap tin $srcfilename khong ton tai"
exit 0 #stop 
fi
#

#check the legalization of desfilename
#none
#

#main
if grep -q "$srcstring" "$srcfilename" #grep without annoucement
then echo > "$desfilename" "Trong tap tin $srcfilename co chuoi $srcstring"
else echo > "$desfilename" "Trong tap tin $srcfilename khong co chuoi $srcstring"
fi
exit 1
#
