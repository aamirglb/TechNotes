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

let calculator = {
	op1: 3,
	op2: 5,
	add() {
		this.result = this.op1 + this.op2
	}
}

// calculator.add();
calculator["add"]()
console.log(calculator.result);

let o = {
	m: function() {
		let self = this
		console.log(this === o)
		f();

		function f() {
			console.log(this === o)
			console.log(self === o)
		}
	}
};
o.m();

// Before ES6 rest arguments

function max(x) {
	let mv = -Infinity;
	for(let i = 0; i < arguments.length; ++i) {
		if(arguments[i] > mv) mv = arguments[i];
	}
	return mv;
}

console.log(max(3, 4, 88, 1100, 567, 34, 234, 1234))

function new_max(first=-Infinity, ...rest) {
	let mv = first;
	for(let n of rest) {
		if(n > mv) mv = n;
	}
	return mv;
}

console.log(max(3333, 4, 88, 1100, 567, 34, 234, 1234));