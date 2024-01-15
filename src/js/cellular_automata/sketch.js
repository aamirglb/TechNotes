// Visualizing Cellular Automata
let cells = [];
let ruleValue = 3;
let ruleSet;
let cellWidth = 4;
let y = 0;

function setup() {
  createCanvas(810, 1010);
  background(220);
  ruleSet = ruleValue.toString(2).padStart(8, "0");

  let total = width / cellWidth;
  for(let i = 0; i < total; ++i) {
    // cells[i] = floor(random(2));
    cells[i] = 0;
  }
  cells[floor(total/2)] = 1;
}

function draw() {

    for(let i = 0; i < cells.length; ++i) {
      let x = i * cellWidth;
      // stroke(0);
      noStroke();
      fill(255 - cells[i] * 255);
      square(x, y, cellWidth);
    }

    y += cellWidth;

    let nextCells = [];
    let len = cells.length;

    for(let i = 0; i < cells.length; ++i) {
      let left = cells[(i - 1 + len) % len];
      let right = cells[(i + 1 + len) % len];
      let state = cells[i];
      let newState = calculateState(left, state, right);
      nextCells[i] = newState;
    }
    cells = nextCells;
}

function calculateState(a, b, c) {
  let ruleset = [1, 0, 1, 1, 0, 1, 1, 0];
  let neighborhood = '' + a + b + c;
  let value = 7 - parseInt(neighborhood,2);
  return parseInt(ruleSet[value]);
  // return ruleset[value];

  if( a == 1 && b == 1 && c == 1) return 1;
  if( a == 1 && b == 1 && c == 0) return 0;
  if( a == 1 && b == 0 && c == 1) return 1;
  if( a == 1 && b == 0 && c == 0) return 1;
  if( a == 0 && b == 1 && c == 1) return 0;
  if( a == 0 && b == 1 && c == 0) return 1;
  if( a == 0 && b == 0 && c == 1) return 1;
  if( a == 0 && b == 0 && c == 0) return 0;
}