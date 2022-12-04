let n = 0;
let c = 4;

function setup() {
    createCanvas(400, 400);
    angleMode(DEGREES);
    colorMode(HSB)
    background(0);
}

function draw() {
    // let angle = n * 137.5;
    let angle = n * 137.3;
    let r = c * sqrt(n);

    let x = r * cos(angle) + width/2;
    let y = r * sin(angle) + height/2;

    fill(angle % 256, 255, 255);
    noStroke();
    ellipse(x, y, 4, 4);
    ++n;
}