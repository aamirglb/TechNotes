var colors = ["Red", "Green", "Blue", "Yellow", "Orange"];
console.log("colors (", colors.length, "): ", colors)

// get last element
console.log("pop(): ", colors.pop());
console.log("colors (", colors.length, "): ", colors)

console.log("pop(): ", colors.pop());
console.log("colors (", colors.length, "): ", colors)

colors.push("Pink");
console.log("colors (", colors.length, "): ", colors)

colors.push("Cyan");
console.log("colors (", colors.length, "): ", colors)

console.log("shift(): ", colors.shift());
console.log("colors (", colors.length, "): ", colors)

colors.unshift("Purple");
console.log("colors (", colors.length, "): ", colors)

console.log("\n\n");

var scores = [43, 22, 76, 10, 99, 55, 43];
console.log(scores);
scores.sort();
console.log(scores);

var fn = function() {
	console.log("Hello Function!!");
}

fn();

let a = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10];
console.log(a.filter(i => i % 2 == 0));
console.log(a.filter(i => i % 2 != 0));
console.log(a.map(i => i * 0.5));

console.log(a.reduce((a,b) => a + b));

console.log("Average: ", a.reduce((a,b) => a + b) / a.length);

console.log("some: ", a.map(i => some(i => i % 3 == 0)));

