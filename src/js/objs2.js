let anObj = {left: 1, right: 2};
console.log(anObj.left);

delete anObj.left;

console.log(anObj.left);

console.log("left" in anObj);
console.log("right" in anObj);

let obj2 = {x:0, y:1, z:2};
console.log(Object.keys(obj2));
console.log(Object.values(obj2));

Object.assign(obj2, {x:10, y:20});
console.log(obj2);

let o1 = { value: 10};
let o2 = o1; 
let o3 = { value: 10};

console.log(o1 == o2);
console.log(o1 == o3);

o1.value = 15;
console.log(o2.value);
console.log(o3.value);

let journal = [];

function addEntry(events, squirrel) {
	journal.push({events, squirrel});
}

addEntry(["work", "touched tree", "pizza", "running", "television"], false);
addEntry(["work", "ice cream", "cauliflower", "lasagna", "touched tree", "brushed teeth"], false);
addEntry(["weekend", "cycling", "break", "peanuts", "beer"], true);

console.log(journal);

console.log("================ JSON ===================");
console.log(JSON.stringify(journal, null, 2));

for(let entry of journal) {
	console.log(`${entry.events.length} events.`);
}


let arr = ['el1', 'el2', 'el3'];

arr.addedProp = 'arrProp';

// elKey are the property keys
for (let elKey in arr) {
  console.log(elKey);
}

// elValue are the property values
for (let elValue of arr) {
  console.log(elValue)
}

const num = [5, 10, 15, 20, 25, 30, 35, 40];
for(let i in num) {
	console.log(i);
}

for(let i of num) {
	console.log(i);
}
