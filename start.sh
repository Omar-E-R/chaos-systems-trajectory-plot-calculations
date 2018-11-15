clear

LD_LIBRARY_PATH=$LD_LIBRARY_PATH:../lib

export LD_LIBRARY_PATH

cd ./bin

find -name "projetOmar" -fprint ../search/search

cd ../sysdyn

find -name "*.sysdyn" -fprint ../search/searchsys

cd ../

sysFound=$(grep -c ".sysdyn" ./search/searchsys)

projectisCompiled=$(grep -c "projet" ./search/search)

result = "echo $(cut -d "/" -f 3 ./data/searchsys | cut -d "." -f 1)"

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
		
		echo "Enter any key to continue or enter q to quit the program"
		
		read choice
		
		if [ "$choice" == "q" ]; then
			clear
			exit
		else 
			./projetOmar
			exit
		fi
	fi #if there was systems already registered AND PROJET IS COMPILED
elif [ -n $sysFound ] && [ -n $projectisCompiled ]; then
	

	echo "$sysFound system(s) is(were) found:"
	echo
	echo $(result)
	echo
	echo "Would you like to edit or view any of them? y/n"

	read choice

	if [ "$choice" == "y" ] || [ "$choice" == "Y" ] || [ "$choice" == "yes" ] || [ "$choice" == "Yes" ]; then
		while : ; do
			clear
			echo "which one?"
			echo
			echo $(result)

			read cmd

			sysFound=$(grep -c "$cmd" ./search/searchsys)

			if [ -n $sysFound ]; then
				break
			fi
		done
		./projetOmar $cmd
	else
		echo "Do you want to delete any of them? y/n"

		read choice

		if [ "$choice" == "y" ] || [ "$choice" == "Y" ] || [ "$choice" == "yes" ] || [ "$choice" == "Yes" ]; then
			while : ; do 
				
				clear
				echo "which one?"
				echo
				echo $(result)


				read cmd

				sysFound=$(grep -c "$cmd" ./search/searchsys)

				if [ -n $sysFound ]; then
					break
				fi
			done

			echo ".....Deleting \"$cmd\" system..."
			echo "Do you want to proceed? y/n"


			read choice

			if [ "$choice" == "y" ] || [ "$choice" == "Y" ] || [ "$choice" == "yes" ] || [ "$choice" == "Yes" ]; then
				
				find -name "$cmd.*" -fprint ./search/searchsys

				mv $(echo $(cut -d "" -f 2 ./search/searchsys)) ./tmp
				clear
				echo "\"$cmd\" system no longer exists"
			else

				echo "To start the program  enter any key or q to quit"

				read choice

				if [ "$choice" == "q" ]; then

					exit
				else 
					./projetOmar
				fi
			fi
		fi
	fi
else
	make
	exit

fi