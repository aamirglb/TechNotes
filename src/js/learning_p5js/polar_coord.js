let angle = 0;
function setup() {
    createCanvas(400, 400);
}

function draw() {
    // background(0);
    // stroke(255);
    // strokeWeight(4);
    // noFill();

    // translate(200, 200);
    // let r = 150;
    // circle(0, 0 , r*2);

    // strokeWeight(32);
    // stroke(252, 238, 33);

    // let x = r * cos(angle * -1);
    // let y = r * sin(angle * -1);
    // point(x, y);

    // angle += 0.01;

    background(0);
    translate(200, 200);
    fill(252, 238, 33);
    let r = map(sin(angle), -1, 1, 0, 200);
    circle(0, 0, r*2);
    angle += 0.02;
}