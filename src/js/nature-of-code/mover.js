class Mover {
    constructor() {
        this.position = createVector(random(width), random(height));
        this.velocity = createVector(random(-2, 2), random(-2, 2));
        this.acceleration = createVector(-0.001, 0.001);
        this.topSpeed = 5;
    }

    update() {
        let mouse = createVector(mouseX, mouseY);
        let dir = p5.Vector.sub(mouse, this.position);
        dir.normalize();
        dir.mult(0.2);
        this.acceleration = dir;

        // this.acceleration = p5.Vector.random2D();
        // this.acceleration.mult(0.5);
        // this.acceleration.mult(random(2));
        this.velocity.add(this.acceleration);
        this.velocity.limit(this.topSpeed);
        this.position.add(this.velocity);
    }

    show() {
        stroke(0);
        strokeWeight(1);
        fill(175);
        circle(this.position.x, this.position.y, 24);
    }

    checkEdges() {
        if( this.position.x > width ) {
            this.position.x = 0;
        } else if(this.position.x < 0) {
            this.position.x = width;
        }

        if( this.position.y > height ) {
            this.position.y = 0;
        } else if(this.position.y < 0) {
            this.position.y = height;
        }
    }
}

let mover;

function setup() {
    createCanvas(600, 400);
    mover = new Mover();
}

function draw() {
    background(255);    
    
    strokeWeight(4);
    line(0, 0, width, 0);
    line(0, height, width, height);
    line(0, 0, 0, height);
    line(width, 0, width, height);

    mover.update();
    mover.checkEdges();
    mover.show();
}