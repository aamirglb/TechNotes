class Mover {
    constructor(x, y, m) {
        this.mass = m;
        this.pos = createVector(x, y);
        this.vel = createVector(0, 0);
        this.acc = createVector(0, 0);
        this.radius = sqrt(this.mass) * 15;

        // this.vel = p5.Vector.random2D();
        // this.vel.mult(random(3));
        // acceleration is change in velocity
    }

    left() {
        return this.pos.x - this.radius;
    }

    right() {
        return this.pos.x + this.radius;
    }

    top() {
        return this.pos.y - this.radius;
    }

    bottom() {
        return this.pos.y + this.radius;
    }
/*
    float x()      { return shape.getPosition().x; }
    float y()       { return shape.getPosition().y; }
    float left()    { return x() - shape.getRadius(); }
    float right()   { return x() + shape.getRadius(); }
    float top()     { return y() - shape.getRadius(); }
    float bottom()  { return y() + shape.getRadius(); }
*/
    applyForce(force) {
        let f = p5.Vector.div(force, this.mass);
        // force.div(this.mass);
        // using unit mass Force = Mass * Acceleration
        this.acc.add(f);
    }

    drag() {
        let drag = this.vel.copy();
        drag.normalize();
        drag.mult(-1);

        let c = 0.3;
        let speedSq = this.vel.magSq();
        drag.setMag(c * speedSq);
        this.applyForce(drag);
    }

    friction() {
        let diff = height - (this.pos.y + this.radius);
        // console.log("diff ", diff);
        if(diff < 1) {
            // console.log('friction');
            let force = this.vel.copy();
            force.normalize();
            force.mult(-1);

            // Magnitude of friction
            // let mu = 0.5;
            let normal = this.mass;
            force.setMag(mu * normal);
            this.applyForce(force);
        }
    }
    intersect(other) {
        let d = dist(this.pos.x, this.pos.y, other.pos.x, other.pos.y);
        return (d < (this.radius + other.radius));
    }

    edges() {
        if(this.bottom() >= height) {
            this.pos.y = height - this.radius; // - this.radius;
            this.vel.y *= -1;
        } else if(this.top() <= 0) {
            this.pos.y = this.radius;
            this.vel.y *= -1;
        }

        if(this.right() >= width) {
            this.pos.x = width - this.radius;
            this.vel.x *= -1;
        } else if(this.left() <= 0) {
            this.pos.x = this.radius;
            this.vel.x *= -1;
        }
    }
    update() {
        // let mouse = createVector(mouseX, mouseY);
        // this.acc = p5.Vector.sub(mouse, this.pos);
        // this.acc.setMag(0.1);

        // this.acc = p5.Vector.random2D();
        // this.acc.setMag(0.01);

        this.vel.add(this.acc);
        // this.vel.limit(5);
        this.pos.add(this.vel);
        this.acc.set(0, 0);

        // let mouse = createVector(mouseX, mouseY);
        // this.acceleration = p5.Vector.sub()
        // this.acceleration.setMag(0.2);
    }

    show() {
        stroke(255);
        strokeWeight(2);
        fill(255, 100);
        ellipse(this.pos.x, this.pos.y, this.radius*2);
    }
}

let moverA;
let moverB;
let movers = [];
let mu = 0.1;

function setup() {
    createCanvas(800, 600);
    // moverA = new Mover(width/2, height/2, 1);
    // moverB = new Mover(300, height/2, 2);

    for(let i = 0; i < 10; ++i) {
        movers[i] = new Mover(random(width), 50, random(1, 8));
    }
}

function draw() {
    background(0);

    fill(255, 125);
    noStroke();
    rect(0, height/2, width, height/2);
    // if(mouseIsPressed) {
    //     let wind = createVector(0.0, 0.0);
    //     if(mouseX <= 100) {
    //         wind = createVector(0.2, 0.0);
    //     } else if (mouseX > (width-100)) {
    //         wind = createVector(-0.2, 0.0);
    //     }

    //     if(mouseY <= 100) {
    //         wind = createVector(0.0, 0.2);
    //     } else if(mouseY > (height-100)) {
    //         wind = createVector(0.0, -0.2);
    //     }
    //     // let wind = createVector(-0.1, 0.0);
    //     moverA.applyForce(wind);
    //     moverB.applyForce(wind);
    // }

    // if(moverA.intersect(moverB)) {
    //     console.log("ball intersecting");
    //     moverA.vel.x *= -1;
    //     moverA.vel.y *= -1;

    //     moverB.vel.x *= -1;
    //     moverB.vel.y *= -1;
    // }

    stroke(255, 100);
    strokeWeight(2);
    fill(255);
    point(width/2, height/2);
    line(0, 100, width, 100);
    line(0, height-100, width, height-100);
    line(100, 0, 100, height);
    line(width-100, 0, width-100, height);

    // let gravity = createVector(0, 0.2);
    // let weightA = p5.Vector.mult(gravity, moverA.mass);
    // let weightB = p5.Vector.mult(gravity, moverB.mass);

    for(let mover of movers) {
        if(mouseIsPressed) {
            let wind = createVector(0.1, 0);
            mover.applyForce(wind);
        }
        let gravity = createVector(0, 0.2);
        let weight = p5.Vector.mult(gravity, mover.mass);
        mover.applyForce(weight);
        // mover.friction();
        if(mover.pos.y > height/2) {
            mover.drag();
        }
        mover.update();
        mover.edges();
        mover.show();
    }
    // moverA.applyForce(weightA);
    // // moverB.applyForce(weightB);

    // moverA.friction();
    // moverA.update();
    // moverA.edges();
    // moverA.show();

    // moverB.update();
    // moverB.edges();
    // moverB.show();
}