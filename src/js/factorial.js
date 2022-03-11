// Compute factorial using recursion

let call_count = 0;

var factorial = function factorial(i, a) {
	a = a || 1;
	if(i < 2) {
		return a;
	}
	console.log(`Recursive call ${++call_count}: factorial(${i-1}, ${a*i})`);
	return factorial(i-1, a*i);
};

console.log(factorial(10));
