let angle = 0.0;
let offset;
let scalar = 2;
let speed = 0.05;

function setup() {
    createCanvas(420, 420);
    fill(0);
    background(204);
    offset = (width / 2);
}

function draw() {
    let x = offset + cos(angle) * scalar;
    let y = offset + sin(angle) * scalar;
    circle(x, y, 2);
    angle += speed;
    scalar += speed;
}