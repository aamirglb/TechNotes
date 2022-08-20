class Particle {
    constructor(x, y) {
        this.pos = createVector(x, y);
        this.vel = p5.Vector.random2D();
        this.vel.mult(random(0.5, 2))
        this.acc = createVector(0, 0.00);
        this.r = 4;
        this.mass = 1;
        this.lifespan = 255;
    }

    applyForce(force) {
        // let f = force.copy();
        // f.div(this.mass);
        this.acc.add(force);
    }

    update() {
        // this.velocity.mult(0.99);
        this.vel.add(this.acc);
        this.pos.add(this.vel);
        this.acc.set(0, 0);
        this.lifespan -= 2.5;
        // this.acceleration.mult(0);

    }

    show() {
        stroke(255, this.lifespan);
        strokeWeight(2);
        fill(255, this.lifespan);
        ellipse(this.pos.x, this.pos.y, this.r * 2);
    }

    isDead() {
        return this.lifespan <= 0;
    }

    left() {
        return this.pos.x - this.r;
    }

    right() {
        return this.pos.x + this.r;
    }

    top() {
        return this.pos.y - this.r;
    }

    bottom() {
        return this.pos.y + this.r;
    }

    edges() {
        if(this.bottom() >= height) {
            this.pos.y = height - this.r;
            this.vel.y *= -1;
        } else if(this.top() <= 0) {
            this.pos.y = this.r;
            this.vel.y *= -1;
        }

        if(this.right() >= width) {
            this.pos.x = width - this.r;
            this.vel.x *= -1;
        } else if(this.left() <= 0) {
            this.pos.x = this.r;
            this.vel.x *= -1;
        }
    }
}

let particles = [];

function setup() {
    createCanvas(400, 400);
    // particles.push(new Particle(200, 200))
    // for(let i = 0; i < 100; ++i) {
    //     particles[i] = new Particle(width/2, 20);
    // }
}

function draw() {
    background(0);
    for(let i = 0; i < 5; ++i) {
        particles.push(new Particle(200, 20));
    }
    for(let p of particles) {
        let gravity = createVector(0, 0.2);
        p.applyForce(gravity);
        p.update();
        // p.edges();s
        p.show();
    }

    // particles.push(new Particle(width/2, 20));
    for(let i = particles.length - 1; i >= 0; --i) {
        if(particles[i].isDead()) {
            particles.splice(i, 1);
        }
    }
    // for(let p of particles) {
    //     p.update();
    //     p.show();
    //     if(p.isDead()) {
    //     }
    // }
    // if(particles.length > 100) {
    //     particles.shift();
    // }
}