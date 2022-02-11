(function() {
	console.log("no need to call me");
}());

var x = function() {
	console.log("function in x");
}();

// Error here
// x();

var i="red";
function countApples() {
	for(i=0;i<=10; ++i) {
		//console.log(i);
	}
}
countApples();

y=5;
var y;

function upperFn(x) {
	var z = 8;

	function innerFn(y) {
		console.log(x+y+z);
	}
	innerFn(3);
}

upperFn(2);

function wrapValue(n) {
	let local = n;
	return () => local;
}

let wrap1 = wrapValue(1);
let wrap2 = wrapValue(2);
console.log(wrap1());
console.log(wrap2());

function multiplier(factor) {
	return number => number * factor;
}

let twice = multiplier(2);
console.log(twice(25));

function max(...numbers) {
	let result = -Infinity;
	for(let n of numbers) {
		if(n > result) result = n;
	}
	return result;
}

console.log(max(4, 1, 9, -2, 4, 10));

let words = ["never", "fully"];
console.log(["will", ...words, "understand"]);

