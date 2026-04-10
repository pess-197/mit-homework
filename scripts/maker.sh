mkdir -p Build
arg1="$1"
arg2="$2"
if [[ "$2" == *.cpp ]]; then
	case "$arg1" in
		"build") g++ "$2" -o ./Build/exct ;;
		"run") g++ "$2" -o ./Build/exct; ./Build/exct ;;
		"clean") rm -rf ./Build ;;
	esac
fi


