
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:../lib

export LD_LIBRARY_PATH
clear

while : ; do
	cd ./bin

	find -name "projetOmar" -fprint ../search/search

	cd ../sysdyn

	find -name "*.sysdyn" -fprint ../search/searchsys

	cd ..

	sysFound=$(grep -c ".sysdyn" ./search/searchsys)

	projectisCompiled=$(grep -c "projetOmar" ./search/search)


	#if no systems are registered
	clear
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
			./bin/projetOmar
		else
			./bin/projetOmar

		fi #if there was systems already registered AND PROJET IS COMPILED
	elif [ -n $sysFound ] && [ -n $projectisCompiled ]; then
		
		clear

		echo "$sysFound system(s) is(were) found:"
		echo "---------------"
		echo $(cut -d "/" -f 2 ./search/searchsys | cut -d "." -f 1)
		echo "---------------"
		echo "Do you want to edit or view any of it? y/n"

		read choice

		if [ "$choice" == "y" ] || [ "$choice" == "Y" ] || [ "$choice" == "yes" ] || [ "$choice" == "Yes" ]; then
			while : ; do
					clear
					echo "which one?"
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
			./bin/projetOmar $cmd
		else
			echo "Do you want to delete any of them? y/n"

			read choice

			if [ "$choice" == "y" ] || [ "$choice" == "Y" ] || [ "$choice" == "yes" ] || [ "$choice" == "Yes" ]; then
				while : ; do 
					
					clear
					echo "which one?"
					echo "---------------"
					echo $(cut -d "/" -f 2 ./search/searchsys | cut -d "." -f 1)
					echo "---------------"
					echo


					read cmd
					echo
					echo
					sysFound=$(grep -c "$cmd" ./search/searchsys)

					if [ -n $sysFound ]; then
						break
					fi
				done
				echo
				echo "deleting \"$cmd\" system!"
				echo "Do you wish to proceed? y/n"


				read choice
				echo

				if [ "$choice" == "y" ] || [ "$choice" == "Y" ] || [ "$choice" == "yes" ] || [ "$choice" == "Yes" ]; then
					
					find -name "$cmd.*" -fprint ./search/searchsys
					mv $(echo $(cut -d "" -f 2 ./search/searchsys)) ./tmp

					find -name "$cmd" -fprint ./search/searchsys
					mv $(echo $(cut -d "" -f 2 ./search/searchsys)) ./tmp

					clear
					echo "\"$cmd\" system no longer exists"
				fi

			fi
			echo "To start the program  enter any key or q to quit"

			read choice

			if [ "$choice" == "q" ]; then

				exit
			else 
				./bin/projetOmar
			fi
		fi
	else
		make
		exit

	fi
done