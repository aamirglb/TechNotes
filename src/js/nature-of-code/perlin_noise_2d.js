let p;
let xoff;
let yoff;

function setup() {
    createCanvas(640, 640);
    loadPixels();
    xoff = 0.0;
    p = createP('');

    for(let x = 0; x < width; ++x) {
        yoff = 0.0;

        for(let y = 0; y < height; ++y) {
            let index = (x+y*width) * 4;

            const bright = map(noise(xoff, yoff), 0, 1, 0, 255);
            pixels[index] = bright;
            pixels[index + 1] = bright;
            pixels[index + 2] = 150;
            pixels[index + 3] = 255;

            // set(x, y, floor(bright));
            yoff += 0.01;
        }
        xoff += 0.01;
        updatePixels();
    }
}

function draw() {
}