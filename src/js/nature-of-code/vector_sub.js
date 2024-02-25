function setup() {
    createCanvas(600, 400);
}

function draw() {
    background(50);

    let mouse = createVector(mouseX, mouseY);
    let center = createVector(width/2, height/2);

    stroke(200);
    strokeWeight(4);
    line(0, 0, mouse.x, mouse.y);
    line(0, 0, center.x, center.y);

    mouse.sub(center);

    stroke(0);
    translate(width/2, height/2);
    line(0, 0, mouse.x, mouse.y);
}