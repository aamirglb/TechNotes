let i = 0;
let j = 0;

function setup() {
    createCanvas(600, 400);
}

function draw() {
    background(0);
    strokeWeight(4);
    stroke(255);

    for(let x = 0; x <= mouseX; x+=50) {
        for(let y = 0; y <= height; y+=50) {
            fill(random(255), random(255), random(255));
            ellipse(x, y, 25, 25);
        }
    }
}