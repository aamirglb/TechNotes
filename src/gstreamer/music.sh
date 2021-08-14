#!/bin/bash

freq=(115.0 215.0 315.0)
start=1
count=1000
for i in `seq 50 10 500`;
do 
	echo "$i"; 
	gst-launch-1.0  audiotestsrc freq="$i" volume=0.4 num-buffers=100 ! autoaudiosink
done

