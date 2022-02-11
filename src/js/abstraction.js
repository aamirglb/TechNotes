function repeat(n, action) {
	for(let i = 0; i < n; ++i) {
		action(i);
	}
}

repeat(3, console.log);

let labels = [];
repeat(5, i => {
	labels.push(`Unit-${i+1}`);
});
console.log(labels);
