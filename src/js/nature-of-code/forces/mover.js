class Mover {
    constructor() {
        this.mass = 1;
        this.position = createVector(width/2, 30);
        this.velocity = createVector(0, 0);
        this.acceleration = createVector(0, 0);
        // this.topSpeed = 5;
    }

    applyForce(force) {
        let f = p5.Vector.div(force, this.mass);
        this.acceleration.add(f);
    }

    update() {
        this.velocity.add(this.acceleration);
        // this.velocity.limit(this.topSpeed);
        this.position.add(this.velocity);
        this.acceleration.mult(0);
    }

    show() {
        stroke(0);
        strokeWeight(2);
        fill(127, 127);
        ellipse(this.position.x, this.position.y, 24, 24);
    }

    checkEdges() {
        if( this.position.x > width ) {
            this.position.x = width;
            this.velocity.x *= -1;
        } else if(this.position.x < 0) {
            this.velocity.x *= -1;
            this.position.x = 0;
        }

        if( this.position.y > height ) {
            this.velocity.y *= -1;
            this.position.y = height;
        } 
        // else if(this.position.y < 0) {
        //     this.position.y = height;
        // }
    }
}

let mover;

function setup() {
    createCanvas(600, 400);
    mover = new Mover();
    createP("Click mouse to apply wind force");
}

function draw() {
    background(255);
    
    line(0, 0, width, 0);
    line(0, height, width, height);
    line(0, 0, 0, height);
    line(width, 0, width, height);

    let gravity = createVector(0, 0.1);
    mover.applyForce(gravity);

    if(mouseIsPressed) {
        if(mouseX > width/2) {
            let wind = createVector(0.1, 0);
            mover.applyForce(wind);
        } else {
            let wind = createVector(-0.1, 0);
            mover.applyForce(wind);
        }
    }
    mover.update();
    mover.checkEdges();
    mover.show();
}