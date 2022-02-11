var apple={};

var apple = {
	name: "Apple",
	color: "Green",
	weight: 100,
	display: function() { console.log("I weight " + this.weight + "g " + this.color); }
};

apple.display();

apple.color = "Red";
apple.weight = 50;
apple.smell = "Fresh";

apple.display();

function person(first, last, age, color) {
	this.firstName = first;
	this.lastName = last;
	this.age = age;
	this.eyeColor = color;
	this.changeName = function(name) {
		this.lastName = name;
	}
}

var father = new person("John", "Doe", 50, "blue");
var mother = new person("Sally", "Rally", 48) 

console.log(father);
console.log(mother);

mother.changeName("John");
console.log(mother);
var msg = "Hello world!";
console.log(msg.toUpperCase());

var Fruit = function Fruit(name, color) {
    this.name = name;
    this.color = color;
    this.info = function() { return "I am a "+ this.color+ " "+this.name+"\n"};
};

var Cherry = new Fruit("Cherry", "red");
var Apple = new Fruit("Apple", "green");
var Mango = new Fruit("Mango", "yellow");

console.log(Cherry.info(), Apple.info(), Mango.info());

console.log(`half of 100 is ${100/2}`);
console.log('half of 100 is ${100/2}');
console.log("half of 100 is ${100/2}");
