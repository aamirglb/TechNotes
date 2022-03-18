// V1
function makeSandwichV1() {
	var magicIngredient = "peanut butter";
	function make(filling) {
		return magicIngredient + " and " + filling;
	}
	return make("jelly0");
}

console.log(makeSandwichV1());

// V2
function makeSandwichV2() {
	var magicIngredient = "peanut butter";
	function make(filling) {
		return magicIngredient + " and " + filling;
	}
	return make;
}

var f = makeSandwichV2();
console.log(f("jelly"));
console.log(f("bananas"));
console.log(f("marshmallows"));

// V3
// A closure can remember the parameters as well as variables of outer function
function sandwichMakerV3(magicIngredient) {
	function make(filling) {
		return magicIngredient + " and " + filling;
	}
	return make;
}

var chickenAnd = sandwichMakerV3("chicken");
console.log(chickenAnd("cheese")); 
console.log(chickenAnd("mustard")); 

var turkeyAnd = sandwichMakerV3("turkey");
console.log(turkeyAnd("swiss")); 
console.log(turkeyAnd("provolone")); 

// V4
// Function expression
function sandwichMaker(magicIngredient) {
	return function(filling) { // anonymous function expression
		return magicIngredient + " and " + filling;
	}
};

function box() {
	var val = undefined;
	return {
		set: function(newVal) { val = newVal; },
		get: function() { return val; },
		type: function() { return typeof val; }
	};
}

var b = box();
console.log(b.type());
b.set(12.3);
console.log(b.get());
console.log(b.type());
