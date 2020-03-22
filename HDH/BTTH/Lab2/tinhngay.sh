#!/bin/sh
#declaration
year=$1
month=$2
desfilename=$3
isLeafYear=0
isCare=0 #month == 2 then isCare = 1
#

#check the legalization (>1900) of year
if [ $year -le 1900 ]
then echo > "$desfilename" "Nam khong hop le"
exit 0
fi
# 

#check for leaf year
if [ `expr $year % 4` -eq 0 ] #
then isLeafYear=1
fi 
if [ `expr $year % 100` -eq 0 ] #
then isLeafYear=0
fi
if [ `expr $year % 400` -eq 0 ] #
then isLeafYear=1
fi
#

#check the legalization of month
if [ $month -gt 12 ]
then echo > "$desfilename" "Thang khong hop le"
exit 1
fi

if [ $month -lt 1 ]
then echo > "$desfilename" "Thang khong hop le"
exit 1
fi
#

#debug out

#

#main

if [ $isLeafYear -eq 1 ]
then if [ $month -eq 2 ]
then echo > "$desfilename" 29;
exit 2
fi
fi 

case $month in
"1" | "3" | "5" | "7" | "8" | "10" | "12" ) echo > "$desfilename" 31;;
esac

case $month in
"4" | "6" | "9" | "11" ) echo > "$desfilename" 30;;
esac

exit 3

#
