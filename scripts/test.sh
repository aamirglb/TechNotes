#!/bin/bash

QT_VERSION=5.12.6
#QT_PATH=/opt/Qt
#QT_DESKTOP $QT_PATH/${QT_VERSION}/gcc

if [[ $# -ne 1 ]]
then
	echo "Usage: setup_qgc qt_offline_installer_path"
else
	if [ -f "$1" ]; then
		echo "$1 exists."
	else
		echo "Unable to locate '$1'; specify absolute path."
	fi
fi

#echo $#
#while [[ $# -gt 0 ]]
#do
#echo "$1"
#shift
#done
