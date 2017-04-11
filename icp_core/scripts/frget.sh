#!/bin/sh
if [ $# -eq 0 ]; then
	grep `hostname` /home/jitumoto/work/cuckoo-mpd/misc/finjector/frlist | awk '{print $2}'
else
	grep $1 /home/jitumoto/work/cuckoo-mpd/misc/finjector/frlist | awk '{print $2}'
fi
