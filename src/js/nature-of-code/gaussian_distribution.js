function setup() {
    createCanvas(640, 240 * 2 + 20);
    background(255);
}

function draw() {
    let x = randomGaussian(width / 2, 60);

    noStroke();
    fill(10, 10);
    circle(x, 120, 16);
}