
for file in *; do
    while read -r line; do
	echo "${line#*.}"
    done < "$file"

done

# Path: 2.sh
