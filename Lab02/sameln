#!/bin/bash

IFS=$'\n'
dir=$1
RESULT=`ls -a $dir | sort`
declare -a ARRAY
declare -a FIRSTARRAY
let count=0
let firstcount=0

for FILE in $RESULT
do
    if [ ! -L "$dir/$FILE" ] && [ ! -d "$dir/$FILE" ]
	then
	if [ ! -r "$dir/$FILE" ]
	    then
	    echo "You have no read permission for the file $dir/$FILE."
	elif [ -f "$dir/$FILE" ]
	    then
	    if [[ "$(basename "$FILE")" == .* ]]
		then
		FIRSTARRAY[$firstcount]="$dir/$FILE"
		let firstcount=$firstcount+1
	    else
		ARRAY[$count]="$dir/$FILE"
		let count=$count+1
	    fi
	fi
    fi
done

#Combine ARRAY and FIRSTARRAY
ARRAY=("${FIRSTARRAY[@]}" "${ARRAY[@]}")
let count=count+firstcount

for (( i=0;i<$count;i++ ))
do
    for (( j=$i+1;j<$count;j++ ))
    do
	file1="${ARRAY[i]}"
	file2="${ARRAY[j]}"
      	cmp -s -- "$file1"  "$file2"
	if [ $? -eq 0 ]
	    then
	    ln -f -- "$file1" "$file2"
	fi
    done
done






