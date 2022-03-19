var obj = {
	hello: function() {
		return "hello, " + this.username;
	},
	username: "Aamir",
};

console.log(obj.hello());

var obj2 = {
	hello: obj.hello,
	username: "Mohammad",
};

console.log(obj2.hello());

function hello() {
	return "hello, " + this.username;
}

var obj3 = {
	hello: hello,
	username: "Umar",
};

var obj4 = {
	hello: hello,
	username: "Ali",
};
console.log(obj3.hello());
console.log(obj4.hello());

username = "global"
console.log(hello());

function User(name, passwordHash) {
	this.name = name;
	this.passwordHash = passwordHash;
}

var u1 = new User("aamir", "11234555");
console.log(u1.name, u1.passwordHash);

function compareNumbers(x, y) {
	if(x < y) return -1;
	if(x > y) return 1;
	return 0;
}

console.log([2, 4, 1, 0, 6, 3, 9, 6].sort(compareNumbers));

var names = ["mohammad", "aamir", "ali"];
var upper = names.map(n => n.toUpperCase());
console.log(upper);
