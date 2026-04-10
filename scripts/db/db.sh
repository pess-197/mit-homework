case "$1" in
	"get") cat ./db/"$2";;
	"set") touch ./db/"$2"; echo "$3" > ./db/"$2";;
esac
