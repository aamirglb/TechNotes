var aIdx = "a".charCodeAt(0);

var alphabet = "";
for(var i = 0; i < 26; ++i) {
	alphabet += String.fromCharCode(aIdx + i);
}
console.log(alphabet);

var digits = "";
for(i = 0; i < 10; ++i) {
	digits += i;
}
console.log(digits);

var random = "";
for(i = 0; i < 8; ++i) {
	random += String.fromCharCode(Math.floor(Math.random() * 26) + aIdx);
}
console.log(random);

function buildString(n, callback) {
	var result = "";
	for(var i=0; i<n; ++i) {
		result += callback(i);
	}
	return result;
}

var a = buildString(26, function(i) {
	return String.fromCharCode(aIdx + i);
});

var d = buildString(10, function(i) { return i; });

var r = buildString(8, function() {
	return String.fromCharCode(Math.floor(Math.random() * 26) + aIdx);
});
console.log(a);
console.log(d);
console.log(r);

