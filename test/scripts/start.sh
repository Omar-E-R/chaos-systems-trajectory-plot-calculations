#!/bin/bash
LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:../lib
export LD_LIBRARY_PATH

#clear


while : ; do
	cd ./bin

	find -name "ElRifai" -fprint ../search/search

	cd ../sysdyn

	find -name "*.sysdyn" -fprint ../search/searchsys

	cd ..

	sysFound=$(grep -c ".sysdyn" ./search/searchsys)

	projectisCompiled=$(grep -c "ElRifai" ./search/search)

	#alias systems = "cut -d \"/\" -f 2 ./search/searchsys | cut -d \".\" -f 1"
	#alias found = "grep -c ".sysdyn" ./search/searchsys"

	#clear
	#if no systems are registered
	if [ $sysFound -eq 0 ]; then

		echo "No registered dynamic systems were found"
		echo
		echo "Enter any key to start the program or enter q to quit"

		read choice

		if [ "$choice" == "q" ]; then
			clear
			exit
		
		elif [ $projectisCompiled -eq 0 ]; then
			
			make
			./bin/ElRifai
		else
			./bin/ElRifai

		fi #if there was systems already registered AND PROJET IS COMPILED
	elif [ -n $sysFound ] && [ -n $projectisCompiled ]; then
		
		#clear

		echo "$sysFound system(s) is(were) found:"
		echo "---------------"
		echo $(cut -d "/" -f 2 ./search/searchsys | cut -d "." -f 1)
		echo "---------------"
		echo "Enter:"
		echo "<1> To edit or view any of the systems data"
		echo "<2> To delete any of the systems file data"
		echo "<3> To plot any of the systems"
		echo "<q> To exit program"

		read choice

		if [ "$choice" == "1" ]; then
			while : ; do
				clear
				echo "which one of the systems below?:"
				echo "---------------"
				echo $(cut -d "/" -f 2 ./search/searchsys | cut -d "." -f 1)
				echo "---------------"
				echo

				read cmd

				sysFound=$(grep -c "$cmd" ./search/searchsys)

				if [ -n $sysFound ]; then
					break
				fi
			done
			./bin/ElRifai $cmd
		fi
		if [ "$choice" == "2" ]; then
			echo "Enter the full exact name of the system you want to delete from below:"
			echo "---------------"
			echo $(cut -d "/" -f 2 ./search/searchsys | cut -d "." -f 1)
			echo "---------------"
			
			echo ; echo ;
			while : ; do 

				read cmd
				echo
				echo
				sysFound=$(grep -c "$cmd" ./search/searchsys)

				if [ -n $sysFound ]; then
					break
				fi
			done
			echo "Are you sure you want to proceed deleting '$cmd'? y/n:"
			read choice
			if [ "$choice" == "y" ] || [ "$choice" == "Y" ] || [ "$choice" == "yes" ] || [ "$choice" == "Yes" ]; then
					
				find -name "$cmd.*" -fprint ./search/searchsys
				rm -f $(echo $(cut -d "" -f 2 ./search/searchsys))

				find -name "$cmd" -fprint ./search/searchsys
				rm -f $(echo $(cut -d "" -f 2 ./search/searchsys))

				clear
				echo "\"$cmd\" system no longer exists"

			fi
		fi
		if [ "$choice" == "3" ]; then
			./gnuplotc.sh "$cmd"
		fi
		if [ "$choice" == "q" ]; then
			exit
		fi
	fi

done