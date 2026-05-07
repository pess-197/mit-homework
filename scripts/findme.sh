IFS=':' read -ra patharray <<< "$PATH"

arg="$1"

for i in "${patharray[@]}"; do
	find "$i" -maxdepth 1 -iname "$1" 2>/dev/null
done

