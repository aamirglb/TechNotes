let walker;

function setup() {
    createCanvas(640, 240);
    walker = new Walker();
    background(0);
}

function draw() {
    walker.step();
    walker.show();
}