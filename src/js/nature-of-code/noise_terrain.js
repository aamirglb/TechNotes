let land;
let theta = 0.0;

function setup() {
    createCanvas(640, 240, WEBGL);
    land = new Terrain(20, 800, 400);
}

function draw() {
    land.calculate();

    background(255);
    push();
    translate(0, 20, -200);
    rotateX(PI / 3);
    rotateZ(theta);
    land.render();
    pop();

    theta += 0.0025;
}