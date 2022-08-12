let x, y, r, g, b;

function setup() {
    createCanvas(windowWidth, windowHeight);
    background(0);
}

function draw() {
    r = random(255);
    g = random(255);
    b = random(255);

    x = random(width);
    y = random(height);
    noStroke();
    fill(r, g, b, 100);
    circle(x, y, 25);
}