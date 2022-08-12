let squareSize = 150;
let lineWidth = 4;

function setup() {
    createCanvas(1000, 800)
    background(100);
}

function draw() {
    // background(100);
    lineWidth = random(4, 30);
    squareSize = random(50, 250);

    rectMode(CENTER);
    strokeWeight(lineWidth);
    stroke(0, 0, 255, 10);
    fill(0, 255, 0, 10);
    square(200, 150, squareSize);
    // noStroke();
    // fill(255, 50);
    // circle(mouseX, mouseY, 20);
}

function mousePressed() {
    background(0);
}

