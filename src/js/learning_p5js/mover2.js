class Mover {
    constructor(x, y, m) {
        this.mass = m;
        this.pos = createVector(x, y);
        // this.vel = createVector(0, 0);
        this.vel = p5.Vector.random2D();
        this.acc = createVector(0, 0);
        this.radius = sqrt(this.mass) * 15;
    }

    applyForce(force) {
        let f = p5.Vector.div(force, this.mass);
        this.acc.add(f);
    }

    update() {
        this.vel.add(this.acc);
        this.pos.add(this.vel);
        this.acc.set(0, 0);
    }

    show() {
        stroke(255);
        strokeWeight(2);
        fill(255, 100);
        ellipse(this.pos.x, this.pos.y, this.radius*2);
    }
}

class Attractor {
    constructor(x, y, m) {
        this.pos = createVector(x, y);
        this.mass = m;
        this.r = sqrt(this.mass) * 15;
    }

    show() {
        noStroke();
        // stroke(255);
        fill(255, 0, 0);
        ellipse(this.pos.x, this.pos.y, this.r * 2);
    }

    attract(mover) {
        let force = p5.Vector.sub(this.pos, mover.pos);
        let distanceSq = constrain(force.magSq(), 100, 2500);
        let G = 90;
        let strength = G * (this.mass * mover.mass) / distanceSq;
        force.setMag(strength);
        mover.applyForce(force);
    }
}

let movers = [];
let attractor;

function setup() {
    createCanvas(800, 800);
    for(let i = 0; i < 8; ++i) {
        let x = random(width);
        let y = random(height);
        let m = random(1, 2);
        movers[i] = new Mover(x, y, m);
    }

    attractor = new Attractor(width/2, height/2, 2);
    background(0);
}

function draw() {
    background(0);

    for(let i = 0; i < 8; ++i) {
        movers[i].update();
        movers[i].show();
        attractor.attract(movers[i]);
    }


    attractor.show();
}