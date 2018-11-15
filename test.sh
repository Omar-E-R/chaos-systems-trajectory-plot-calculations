LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./lib
export LD_LIBRARY_PATH

find -name "*.sysdyn" -fprint ./data/search
find -name "projet" -fprint ./data/search

resultSys=$(grep -c ".sysdyn" ./data/search)
resultCompiled=$(grep -c "projet" ./data/search)

if [ $resultSys -eq 0 ]; then
	echo "No regeistered dynamic systems were found"
	echo "Enter any key to start the program or enter q to quit"
	read choice
	if [ "$choice" == "q"]; then
		exit
	elif [ $resultCompiled -eq 0 ]; then
		make
		make
		exit
	else 
		./projet
	fi

elif [ -n "$resultSys" ]; then
	echo "$resultSys system(s) were found"
	cd data
	echo $(cat search | cut -d "/" -f 2 search | cut -d "." -f -1)>search
	cat search
	echo "Would you like to edit or view any of them? y/n"
	read choice
	if [ "$choice" == "y" ] || [ "$choice" == "Y" ] || [ "$choice" == "yes" ] || [ "$choice" == "Yes" ]; then
		while : ; do 
			echo "which one?"
			cat search
			read cmd
			resultSys=$(grep -c "$cmd" $Current_dir/data/search)
			[[ $resultSys -eq 0 ]] || break
		done
		cd ..
		./projet $cmd
	else
		cd ..
		echo "Enter any key to continue or enter q to quit"
		read choice
		if [ "$choice" == "q"]; then
			exit
		else
			./projet
		fi

	fi
fi

