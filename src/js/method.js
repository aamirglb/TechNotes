var myObject = {
	value: 0,
	increment: function (inc) {
		this.value += typeof inc === 'number' ? inc : 1;
	},
	double: function() {
		var that = this;
		var helper = function() {
			that.value *= 2;
		};
		helper();
	}
};

myObject.increment();
console.log(myObject.value);

myObject.increment(3);
console.log(myObject.value);

myObject.double();
console.log(myObject.value);

// Construction invocation pattern

var Quo = function(string) {
	this.status = string;
};

// Give all instances of Quo a public method called get_status
Quo.prototype.get_status = function() {
	return this.status;
};

var myQuo = new Quo("really confused");
console.log(myQuo.get_status());

//var q2 = Quo("try this");
//console.log(q2.get_status());
