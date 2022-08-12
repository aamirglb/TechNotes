let xoff = 0;
let xoff2 = 10000;
let slider;
let start = 0;
let inc = 0.01;

function setup() {
    createCanvas(400, 400);
    // slider = createSlider(1, 100, 10);
}

function draw() {
    loadPixels();
    var xoff = 0;
    // background(51);

    // stroke(255);
    // noFill();
    // beginShape();

    var yoff = 0;
    for(var y = 0; y < height; ++y) {
        var xoff = 0;
        for(var x = 0; x < width; ++x) {
            var index = (x + y * width) * 4;
            var r = noise(xoff, yoff) * 255;
            pixels[index + 0] = r;
            pixels[index + 1] = r;
            pixels[index + 2] = r;
            pixels[index + 3] = 255;
            xoff += inc;
        }
        yoff += inc;
    }
    updatePixels();


    // var xoff = start;
    // inc = slider.value() * 0.01;

    // for(var x = 0; x < width; ++x) {
    //     stroke(255);
    //     // var y = random(height);
    //     // var y = map(noise(xoff), 0, 1, 1, height);
    //     var y = noise(xoff) * height;
    //     vertex(x, y);
    //     xoff += inc;
    // }
    // endShape();
    // start += inc;


    // noLoop();
    // let x = map(noise(xoff), 0, 1, 0, width);
    // var y = map(noise(xoff2), 0, 1, 0, height);

    // xoff += 0.01;
    // xoff2 += 0.02;

    // ellipse(x, y, 24, 24);
}

