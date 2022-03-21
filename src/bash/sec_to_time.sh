#/usr/bin/env bash

function get_time_from_sec()
{
	#SEC=$(bc <<< "(3600 * 5) + (4 * 60) + 35")
	input_sec=$1
	printf "input seconds = %d\n" $input_sec
	local seconds=$(bc <<< "$input_sec % 60") 
	local tmp_min=$(bc <<< "($input_sec - $seconds) / 60")
	local hours=0

	if [ $tmp_min -gt 60 ]; then
		minutes=$(bc <<< "$tmp_min % 60")
		hours=$(bc <<< "($tmp_min - $minutes) / 60")
	fi
	printf "%02d:%02d:%02d\n" $hours $minutes $seconds
}

result=`get_time_from_sec $(bc <<< "(3600 * 5) + (60 * 4) + 35")`
echo $result

result=`get_time_from_sec $(bc <<< "(3600 * 0) + (60 * 0) + 5")`
echo $result

result=`get_time_from_sec $(bc <<< "(3600 * 1) + (60 * 45) + 0")`
echo $result

result=`get_time_from_sec $(bc <<< "(3600 * 25) + (60 * 59) + 59")`
echo $result

result=`get_time_from_sec $(bc <<< "(3600 * 0) + (60 * 0) + 0")`
echo $result
