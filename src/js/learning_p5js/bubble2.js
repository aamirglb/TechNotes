class Bubble {
    constructor(x=200, y=150, r=10, c=255) {
        this.x = x;
        this.y = y;
        this.r = r;
        this.c = c;
        this.brightness = 0;
        this.overlapping = false;
    }

    changeColor(bright) {
        this.brightness = bright;
    }

    intersects(other) {
        let d = dist(this.x, this.y, other.x, other.y);
        return (d < (this.r + other.r));
    }

    contains(px, py) {
        let d = dist(px, py, this.x, this.y);
        return d < this.r;
    }

    move() {
        this.x += random(-5, 5);
        this.y += random(-5, 5);
    }

    show() {
        stroke(this.c);
        strokeWeight(4);
        fill(this.brightness, 100);
        ellipse(this.x, this.y, this.r*2);
    }
}

let bubbles = [];
let b1;
let b2;

function setup() {
    createCanvas(800, 600);
    for(let i = 0; i < 20; ++i) {
        let x = random(width);
        let y = random(height);
        let r = random(20, 50);
        bubbles[i] = new Bubble(x, y, r);
    }

    // b1 = new Bubble(100, 200, 40);
    // b2 = new Bubble(200, 200, 40);
}

function draw() {
    background(0);

    for(let b of bubbles) {
        b.show();
        b.move();

        let overlapping = false;
        for(let other of bubbles) {
            if(b !== other && b.intersects(other)) {
                overlapping = true;
                // b.changeColor(255);
            } else {
                // b.changeColor(0);
            }
        }
        if(overlapping) b.changeColor(255);
        else b.changeColor(0);
    }
    // if(b1.intersects(b2)) {
    //     background(255, 0, 100);
    // } else {
    //     background(0);
    // }

    // b1.move();
    // b1.show();

    // b2.move();
    // b2.show();

    // b2.x = mouseX;
    // b2.y = mouseY;
}

