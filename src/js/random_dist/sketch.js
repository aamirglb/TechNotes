let randomCounts = [];
let total = 40;
let colors = ['red', 'green', 'blue', 'orange', 'yellow']
function setup() {
  createCanvas(640, 240);
  for(let i = 0; i < total; ++i) {
    randomCounts[i] = 0;
  }
}

function draw() {
  background(255);

  let index = floor(random(randomCounts.length));
  randomCounts[index]++;

  stroke(0);
  let w = width / randomCounts.length;

  for(let x = 0; x < randomCounts.length; ++x) {
    fill(colors[x % colors.length]);
    rect(x * w, height - randomCounts[x], w - 1, randomCounts[x]);
  }
}
