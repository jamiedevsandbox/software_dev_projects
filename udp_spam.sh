#!/bin/bash

echo "Running nemesis UDP spammer. Press Ctrl-C to cease UDP spam"

for (( ;; ))
	do
		nemesis udp -v -S 13.37.13.37 -D 172.16.0.3 -I 1337 -T 128 -d eth0 -H 00:11:13:37:13:37
		sleep 1
	done
