rg1="$1"
echo "$rg1" | sed 's/$/+1/' | bc
