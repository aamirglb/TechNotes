function setup() {
  createCanvas(640, 240); // creating canvas of size 640 x 240
  walker = new Walker(); // creating an instance/object of class Walker
  background(255);
}

function draw() {
  walker.step();
  walker.show();
}