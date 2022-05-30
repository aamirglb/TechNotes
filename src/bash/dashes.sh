LEN=40
CHAR='-'

while (( $# > 0 ))
do
	case $1 in
		[0-9]*) LEN=$1
			;;
		-c) shift;
			CHAR=${1:--}
			STR_LEN=${#CHAR}
			let LEN=LEN/STR_LEN
			echo $CHAR $STR_LEN $LEN
			;;
		*) printf 'usage: %s [-c X] [#]\n' ${0##*/} >&2
			exit 2
			;;
	esac
	shift
done

for (( i=0; i<LEN; ++i ))
do
	#echo -n "$CHAR"
	printf "$CHAR"
done
echo ""

