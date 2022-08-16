// let x, y;
// let pos;

let prev;
class Walker {
    constructor(x, y) {
        this.pos = createVector(x, y);
        // this.vel = createVector(1, -1);
        this.vel = p5.Vector.random2D();
        this.vel.mult(random(3));
    }

    update() {

        let step = p5.Vector.random2D();
        let r = random(100);
        if(r < 1) {
            step.mult(random(25, 75));
        } else {
            step.setMag(2);
        }
        // this.pos.add(this.vel);
        this.pos.add(step);
        // this.pos.x += this.vel.x;
        // this.pos.y += this.vel.y;
    }

    show() {
        stroke(255);
        strokeWeight(2);
        fill(255, 100);
        line(this.pos.x, this.pos.y, prev.x, prev.y);
        prev.set(this.pos);
        // ellipse(this.pos.x, this.pos.y, 32);
        // point(this.pos.x, this.pos.y);
    }
}


let walker;
function setup() {
    createCanvas(400, 400);
    // x = 200;
    // y = 200;
    // pos = createVector(width/2, height/2);
    walker = new Walker(200, 200);
    prev = walker.pos.copy();

    background(0);
}


function draw() {

    walker.update();
    walker.show();

    // stroke(255);
    // strokeWeight(2);
    // // point(x, y);
    // point(pos.x, pos.y);
    // pos.x += random(-1, 1);
    // pos.y += random(-1, 1);

    // let r = floor(random(4));
    // switch(r) {
    //     case 0:
    //         x += 1;
    //         break;
    //     case 1:
    //         x -= 1;
    //         break;
    //     case 2:
    //         y += 1;
    //         break;
    //     case 3:
    //         y -= 1;
    //         break;
    // }
}