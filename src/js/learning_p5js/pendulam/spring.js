class Spring {
    constructor(k, restLength, a, b) {
        this.k = k;
        this.restLength = restLength;
        this.a = a;
        this.b = b;
    }

    update() {
        let force = p5.Vector.sub(this.b.position, this.a.position);
        let x = force.mag() - this.restLength;
        force.normalize();
        force.mult(this.k * x);
        this.a.applyForce(force);
        force.mult(-1);
        this.b.applyForce(force)
    }

    show() {
        strokeWeight(4);
        stroke(255);
        line(this.a.position.x, this.a.position.y,
            this.b.position.x, this.b.position.y)
    }
}
// let bob;
// let anchor;
// let spring;

let particles = [];
let springs = [];
let spacing = 20;

// let restLength = 200;
let k = 0.1;
let gravity;

function setup() {
    createCanvas(800, 800);
    for(let i = 0; i < 20; ++i) {
        particles[i] = new Particle(width/2, i * spacing);
        if( i !== 0) {
            let a = particles[i];
            let b = particles[i - 1];
            let spring = new Spring(k, spacing, a, b);
            springs.push(spring);
        }
    }
    particles[0].locked = true;
    // bob = new Particle(350, 300);
    // anchor = new Particle(300, 0);
    gravity = createVector(0, 0.1);
    // spring = new Spring(0.01, 200, bob, anchor);
}

function draw() {
    background(112, 50, 126);
    // spring.show();

    for(let s of springs) {
        s.update();
        s.show();
    }
    for(let p of particles) {
        p.applyForce(gravity);
        p.update();
        // p.show();
    }


    let tail = particles[ particles.length - 1];
    // bob.show();
    // bob.update();
    // anchor.show();
    // anchor.update();
    // spring.update();

    if(mouseIsPressed) {
        tail.position.set(mouseX, mouseY);
        tail.velocity.set(0, 0);
    }
}