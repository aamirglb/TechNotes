var i;
var word;
var text =
	"This oracle of comfort has so pleased me, " +
	"That when I am in heaven I shall desire " +
	"To see what this child does, " +
	"and praise my Constructor.";

var words = text.toLowerCase( ).split(/[\s,.]+/);
var count = {};

for (i = 0; i < words.length; i += 1) {
	word = words[i];
	if (count[word]) {
		count[word] += 1;
	} else {
		count[word] = 1;
	}
}

for (k in count) {
	console.log(k, ": ", count[k]);
}

