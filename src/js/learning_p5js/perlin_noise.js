let xoffset = 0;
let xoffset2 = 10000;

function setup() {
    createCanvas(400, 400);
}

let inc = 0.01;
let start = 0;
function draw() {
    background(51);
    // let x = random(width);
    // let x = map(noise(xoffset), 0, 1, 0, width);
    // let y = map(noise(xoffset2), 0, 1, 0, height);

    // xoffset += 0.02
    // xoffset2 += 0.02
    // ellipse(x, y, 24, 24);

    stroke(255);
    noFill();
    beginShape();
    let xoff = start;
    for(let x = 0; x < width; ++x) {
        stroke(255);
        var n = map(noise(xoff), 0, 1, -50, 50);
        var s = map(sin(xoff), -1, 1, 0, height);
        var y = s + n;
        // point(x, random(height));
        // let y = map(noise(xoff), 0, 1, 0, height);
        vertex(x, y);
        xoff += inc;

    }
    endShape();
    start += inc;
    // noLoop();
}