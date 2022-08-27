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
        this.lifespan -= 5.5;
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

// let particles = [];

