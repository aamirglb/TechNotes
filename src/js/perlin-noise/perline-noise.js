let points = [];

let noiseMap = [];
let cols; let rows; let size = 50;
let xoff = 0; let yoff = 0; let inc = 0.1;

function setup() {
    createCanvas(400, 400);

    cols = width / size;
    rows = height / size;
    for(let i = 0; i < cols; ++i) {
        noiseMap[i] = [];
        yoff = 0;
        for(let j = 0; j < rows; ++j) {
            noiseMap[i][j] = noise(xoff, yoff);
            yoff += inc;
        }
        xoff += inc;
    }
    // let xoff = 0;
    // for(let i = 0; i < width; ++i) {
    //     points[i] = map(noise(xoff), 0, 1, 0, height);
    //     xoff += 0.07;
    // }
}

function draw() {
    background(220);

    for(let i = 0; i < cols; ++i) {
        for(let j = 0; j < rows; ++j) {
            rect(i*size, j*size, size, size);
            textAlign(CENTER);
            text(round(noiseMap[i][j], 3), size/2+i*size, size/2+j*size);
        }
    }
    // for(let i = 0; i < width - 1; ++i) {
    //     line(i, points[i], i+1, points[i+1]);
    // }
}