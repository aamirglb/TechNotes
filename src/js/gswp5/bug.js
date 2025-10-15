class JitterBug {
    constructor(x, y, diameter) {
        this.x = x;
        this.y = y;
        this.diameter = diameter
        this.speed = 0.5;
    }

    move() {
        this.x += random(-this.speed, this.speed);
        this.y += random(-this.speed, this.speed);
    }

    display() {
        ellipse(this.x, this.y, this.diameter, this.diameter);
    }
}

let bug;
let jit;

function setup() {
    let canvas = createCanvas(480, 120);
    background(204);
    bug = new JitterBug(width * 0.33, height/2, 50);
    jit = new JitterBug(width * 0.66, height/2, 10);
}

function draw() {
    bug.move();
    bug.display();

    jit.move();
    jit.display();
}