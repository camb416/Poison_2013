#!/bin/bash

# sync from Cameron's machine to prototyper machine

# rsync -avh .

# echo "not working yet because mediavol1 is down"
# exit 0

# if [ $# -eq 0 ] ; then
#	echo 'you need to specify the IP of the prototyper machine'
#	exit 0
# fi

# D='/Volumes/mediavol1/2013_Poison/Production/Media\ Exhibits/POI_me_4.x_Magic_Book/data/'

# echo $D

rsync -avh --stats "media@172.16.40.23:/Volumes/mediavol1/2013_Poison/Production/Media\ Exhibits/POI_me_4.x_Magic_Book/data/" .

# /Users/sysadmin/Documents/of_v0.7.4_osx_release/apps/Poison_2013/RFIDBook/bin/data
