let xoff1 = 0;
let xoff2 = 10000;
// let points = [];
let xs = [];
let ys = [];

function setup() {
    createCanvas(400, 400);
}

function draw() {
    background(51);

    let x = map(noise(xoff1), 0, 1, 0, width);
    let y = map(noise(xoff2), 0, 1, 0, height);
    // points.push((x, y));
    xs.push(x);
    ys.push(y);
    
    noStroke();
    fill('yellow');
    xoff1 += 0.01;
    xoff2 += 0.01;
    ellipse(x, y, 24, 24);

    stroke('red');
    // fill('white');
    for(let i = 0; i < xs.length; ++i) {
        point(xs[i], ys[i]);
    }
}
