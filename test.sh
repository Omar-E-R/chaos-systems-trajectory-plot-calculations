Current_dir="$(pwd)"

export LD_LIBRARY_PATH=$Current_dir/lib

cd data

find -name "*.sysdyn" -fprint ~/projet/data/data_search

string=$(grep -c ".sysdyn" ~/projet/data/data_search)

if [ "$string" -eq 0 ]; then
	echo "No regeistered dynamic systems were found"

elif [ -n "$string" ]; then
	echo "$string system(s) were found"
	echo $(cat data_search | cut -d "/" -f 2 data_search | cut -d "." -f -1)>data_search
	cat data_search
	echo "Would you like to edit or view any of them?"
	read choice
	if [ "$choice" == "oui" ] || [ "$choice" == "Oui" ] || [ "$choice" == "O" ] || [ "$choice" == "o" ]; then
		echo "lequel?" && read cmd
		./start $cmd
	else
		make

	fi
fi

