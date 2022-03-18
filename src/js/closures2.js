function wrapElements(a) {
	var result = [], i, n;
	for(i = 0, n = a.length; i < n; ++i) {
		result[i] = function() { return a[i]; };
	}
	return result;
}

var wrapped = wrapElements([10, 20, 30, 40, 50]);
var f = wrapped[0];
console.log(f());


// Immediately invoked function expression (IIFE)
function wrapElementsV2(a) {
	var result = [];
	for(var i = 0, n = a.length; i < n; ++i) {
		(function() {
			var j = i;
			result[i] = function() { return a[j]; };
		})();
	}
	return result;
}

var wrapped = wrapElementsV2([10, 20, 30, 40, 50]);
var f = wrapped[0];
console.log(f());
console.log(wrapped[2]());

function wrapElementsV3(a) {
	var result = [];
	for(var i = 0, n = a.length; i < n; ++i) {
		(function(j) {
			result[i] = function() { return a[j]; };
		})(i);
	}
	return result;
}

var wrapped = wrapElementsV3([10, 20, 30, 40, 50]);
var f = wrapped[1];
console.log(f());
