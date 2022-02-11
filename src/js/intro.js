//import {stdin, stdout} from 'process';
// Cannot use import statement outside a module

var numArray = [1, 2, 3, 4, 5];
for(var i = 0; i < numArray.length+2; ++i) {
	console.log(numArray[i]);
	//process.stdout.write(numArray[i]);
	//process.stdout.write(", ");
}

// define an object
var myObj = {firstName: "Aamir", lastName: "Ali"};
console.log(myObj);
for(x in myObj) {
	console.log("key: ", x);
	console.log("value: ", myObj[x]);
}

// define a function
var f = function() {
	console.log("Hello from function!!");
	console.log("Hello again from function!!");
}

f();

var sum = function(x, y) {
	return x+y;
}

console.log(sum(10, 20));

var x = 16 + "Blue";
console.log(x);

var x = "16"+"Blue";
console.log(x);

var x = 16 + 4 + "Blue";
console.log(x);

var x="Blue"+16+4;
console.log(x);

try {
	throw "myException";
} catch(e) {
	console.log(e);
} finally {
	console.log("Finally Block!!");
}

console.log();

var s1 = "Welcome";
s1 += "to";
s1 += "Javascript";
console.log(s1);

var s2 = "".concat("Welcome ", "to ", "Javascript");
console.log(s2);
