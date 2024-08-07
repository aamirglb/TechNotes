let center;
let angle = 0;
let letters = [];
let cols;
let rows;
let size = 20;

function setup() {
    createCanvas(640, 480);
    center = createVector(width/2, height/2);
    cols = width / size;
    rows = height / size;

    for(let i = 0; i < cols; ++i) {
        letters[i] = [];
        for(let j = 0; j < rows; ++j) {
            let x = i * size + size/2;
            let y = j * size + size/2;
            letters[i][j] = new Letter(x, y, 0.3);
        }
    }
    // pos = createVector(150, 150);
    l = new Letter(300, 300);
}

function draw() {
    background(0);

    center.x = mouseX;
    center.y = mouseY;

    fill(255);
    ellipse(center.x, center.y, 10, 10);
    
    for(let i = 0; i < cols; ++i) {
        for(let j = 0; j < rows; ++j) {
            if(mouseIsPressed) {
                letters[i][j].scl = 1;
            } else {
                letters[i][j].scl = 0.3;
            }
            letters[i][j].display();
            // noFill();
            // rect(i*size, j*size, size, size);
        }
    }
    // calculateVelocity(center, pos);
    // console.log(calculateAngle(center, pos));

    angle += 0.005;
}

