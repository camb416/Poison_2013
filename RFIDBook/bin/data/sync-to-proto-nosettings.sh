#!/bin/bash

# sync from Cameron's machine to prototyper machine

# rsync -avh .

if [ $# -eq 0 ] ; then
	echo 'you need to specify the IP of the prototyper machine'
	exit 0
fi

rsync -avh --stats --progress --exclude 'settings' . sysadmin@$1:/Users/sysadmin/Documents/of_v0.7.4_osx_release/apps/Poison_2013/RFIDBook/bin/data/ 

# /Users/sysadmin/Documents/of_v0.7.4_osx_release/apps/Poison_2013/RFIDBook/bin/data
