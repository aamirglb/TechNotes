function greaterThan(n) {
	return m => m > n;
}

let greaterThan10 = greaterThan(10);
console.log(greaterThan10(11));
console.log(greaterThan10(1));

function noisy(f) {
	return (...args) => {
		console.log("calling with", args);
		let result = f(...args);
		console.log("called with", args, " returned", result);
		return result;
	};
}

let r = noisy(Math.max)(3, 2, 1);
console.log(r);

["A", "B", "C", "D", "E"].forEach(v => console.log(v));
