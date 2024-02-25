let position;
let velocity;
let inc;
let r = 12;

function setup() {
    createCanvas(640, 340);
    position = createVector(100, 100);
    velocity = createVector(2.5, 2);
    inc = createVector(1, 1);
    inc = 1;
}

function draw() {
    background(255);
    
    strokeWeight(4);
    line(0, 0, width, 0);
    line(0, height, width, height);
    line(0, 0, 0, height);
    line(width, 0, width, height);
    
    position.add(velocity);

    if( (position.x + r) > width || (position.x - r) < 0) {
        velocity.x = velocity.x * -1;
        inc.x += 1;
    }
    if((position.y + r) > height || (position.y - r) < 0) {
        velocity.y *= -1;
    }

    stroke(0);
    strokeWeight(1);
    fill(127);
    circle(position.x, position.y, 24);
}