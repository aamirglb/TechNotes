#!/usr/bin/awk -f
#
function max(arr, big)
{
	big = 0;
	for(i in user)
	{
		if(user[i] > big) { big=user[i]; }
	}
	return big
}

NF > 7 {
	user[$3]++
}

END {
	maxm = max(user);
	for(i in user) {
		scaled = 60 * user[i] / maxm;
		printf "%-10.10s [%8d]:", i, user[i]
		for(i = 0; i<scaled; i++) {
			printf "#";
		}
		printf "\n"
	}
}

