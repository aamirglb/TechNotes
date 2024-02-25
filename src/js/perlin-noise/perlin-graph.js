let start = 0;
let inc = 0.01;
function setup() {
    createCanvas(400, 400);
}

function draw() {
    background(51);

    stroke(255);
    noFill();
    beginShape();

    let xoff = start;
    for(let x = 0; x < width; ++x) {
        stroke(255);
        // let y = random(height);
        // let y = noise(xoff) * height;
        let n = map(noise(xoff), 0, 1, -50, 50);
        let s = map(sin(xoff), -1, 1, 0, height);
        let y = s + n;
        vertex(x, y);
        xoff += inc;
    }
    endShape();
    start += inc;
    // noLoop();
}