let r = 100;
let angle = 0;
let delta = -10;
let px = [];
let py = [];
let col;

function setup() {
    createCanvas(400, 400);
    angleMode(DEGREES);
    background(20);
    col = 255;
}

function draw() {
    
    // r = map(mouseX, 0, width, 50, 100);
    translate(width/2, height/2);
    stroke(255, 0, 0);
    fill(255, 0, 0);
    ellipse(0, 0, 4, 4);

    let x = r * cos(angle);
    let y = r * sin(angle);
    px.push(x);
    py.push(y);

    stroke(col);
    noFill();

    beginShape();
    for(let i = 0; i < px.length; ++i) {
        vertex(px[i], py[i]);
    }
    endShape();

    // point(x, y);
    angle += 5;
    if(angle >= 365) {
        angle = 0;
        console.log(px.length);
        noLoop();
        
        r += delta;
    }
}