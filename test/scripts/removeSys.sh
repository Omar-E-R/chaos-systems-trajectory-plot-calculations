read cmdNew
read cmdOld
if [ "$cmdOld" != "$cmdNew" ]; then
	find -name "$cmdOld.*" -fprint ./search/searchsys
	rm $(echo $(cut -d "" -f 2 ./search/searchsys))
	find -name "$cmdOld" -fprint ./search/searchsys
	rm $(echo $(cut -d "" -f 2 ./search/searchsys))
fi
exit