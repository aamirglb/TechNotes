let xoffset = 0;
let xoffset2 = 10000;

function setup() {
    createCanvas(200, 200);
}

let inc = 0.01;

function draw() {
    let yoff = 0;
    loadPixels();

    background(51);
    stroke(255);
    noFill();
    beginShape();

    for(let y = 0; y < height; ++y) {
        let xoff = 0;
        for(let x = 0; x < width; ++x) {
            var index = (x+y * width) * 4;
            let r = noise(xoff, yoff) * 255;
            pixels[index]     = r; // red
            pixels[index + 1] = r; // green
            pixels[index + 2] = r; // blue
            pixels[index + 3] = 255; // alpha
            xoff += inc;
        }
        yoff += inc;
    }
    endShape();
    updatePixels();
    // noLoop();
}