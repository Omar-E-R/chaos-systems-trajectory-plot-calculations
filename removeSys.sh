read cmdNew
read cmdOld
if [ "$cmdOld" != "$cmdNew" ]; then
	rm -rf $cmdOld
	rm -rf $cmdOld.*
fi
exit