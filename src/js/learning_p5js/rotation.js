let angle = 0;
let angleV = 0;
let angleA = 0.001;

function setup() {
    createCanvas(400, 400);
    // angleMode(DEGREES);
    angleMode(RADIANS);
}

function draw() {
    // background(0);
    // noStroke();
    // fill(240, 99, 164);
    // rectMode(CENTER);
    // rotate(angle);
    // rect(0, 0, 256, 16);
    // triangle(128, -32, 128, 32, 172, 0);
    // rect(-128, 0, 32, 48);
    // fill(252, 238, 33);
    // ellipse(0, 0, 8, 8);

    angleA = map(mouseX, 0, width, -0.01, 0.01);
    background(146, 83, 161);
    noStroke();
    fill(240, 99, 164);
    rectMode(CENTER);
    translate(200, 200);
    rotate(angle);
    rect(0, 0, 256, 32);

    angle += angleV;
    angleV += angleA;
}