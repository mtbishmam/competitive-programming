#!/bin/bash
cf gen > in
cf bf < in > exp
cf code < in > out

for ((i = 1; ; ++i)) do
	echo $i
	./gen > in
	./bf < in > exp
	./code < in > out
	diff -w exp out || break
done
notify-send "bug found!!!"
