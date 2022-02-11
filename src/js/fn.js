function hypotenuse(a, b) {
	function square(x) { return x*x; }
	return Math.sqrt(square(a) + square(b));
}

console.log(hypotenuse(4, 5));
