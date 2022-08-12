class Bubble {
    constructor(x=200, y=150, r=10, c=255) {
        this.x = x;
        this.y = y;
        this.r = r;
        this.c = c;
        this.brightness = 0;
    }

    changeColor(bright) {
        this.brightness = bright;
    }

    contains(px, py) {
        let d = dist(px, py, this.x, this.y);
        return d < this.r;
        // if(d < this.r) {
        //     // this.brightness = 255;
        //     return true;
        // } else {
        //     return false;
        //     // this.brightness = 0;
        // }
    }

    move() {
        this.x += random(-5, 5);
        this.y += random(-5, 5);
    }

    show() {
        stroke(this.c);
        strokeWeight(4);
        fill(this.brightness, 100);
        // noFill();
        // noStroke();
        // fill(255, 10);
        ellipse(this.x, this.y, this.r*2);
    }
}

let bubbles = [];
let maxBubbles = 5;
let bubble;
let b2;

function setup() {
    createCanvas(600, 400);
    for(let i = 0; i < maxBubbles; ++i) {
        bubbles[i] = new Bubble(random(width), random(height), random(10, 30));
    }

    // bubble = new Bubble();
    // b2 = new Bubble(100, 50, 15, 100);

    // console.log(bubble.x, bubble.y);
    // print(bubble.x, bubble.y);

}

function draw() {
    background(0);

    for(let i = 0; i < bubbles.length; ++i) {
        if(bubbles[i].contains(mouseX, mouseY)) {
            bubbles[i].changeColor(255);
        } else {
            bubbles[i].changeColor(0);
        }

        bubbles[i].move();
        bubbles[i].show();
    }



    // bubble.move();
    // bubble.show();

    // b2.move();
    // b2.show();
}

function mousePressed() {
    for(let i = 0; i < bubbles.length; ++i) {
        if(bubbles[i].contains(mouseX, mouseY)) {
            bubbles.splice(i, 1);
        }
    }
}

// function mouseDragged() {
//     // let r = random(10, 50);
//     // let b = new Bubble(mouseX, mouseY, r);
//     // bubbles.push(b);
// }