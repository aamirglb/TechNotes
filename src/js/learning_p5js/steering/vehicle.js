function findProjection(pos, a, b) {
    let v1 = p5.Vector.sub(a, pos);
    let v2 = p5.Vector.sub(b, pos);
    v2.normalize();
    let scalarProject = v1.dot(v2);
    v2.mult(scalarProject);
    v2.add(pos);
    return v2;
}


class Vehicle {
    constructor(x, y) {
        this.pos = createVector(x, y);
        this.vel = createVector(1, 0);
        this.acc = createVector(0, 0);
        this.maxSpeed = 2;
        this.maxForce = 0.1;
        this.eta = Infinity;
        this.r = 16;
        this.wanderTheta = PI/2;
        this.path = [];

        //debug symbols
        this.ds = 0;
        this.dt = 0;
    }

    follow(path) {
        // path following algorithm
        let future = this.vel.copy();
        future.mult(50);
        future.add(this.pos);
        fill(255, 0, 0);
        noStroke();
        circle(future.x, future.y, 16);

        // check if future position is on the path
        let target = findProjection(path.start, future, path.end);
        fill(0, 255, 0);
        noStroke();
        circle(target.x, target.y, 16);

        let d = p5.Vector.dist(future, target);
        if(d > path.radius) {
            return this.seek(target);
        } else {
            return createVector(0, 0);
        }
    }


    wander() {
        // let force = p5.Vector.random2D();
        // this.applyForce(force);
        let wanderPoint = this.vel.copy();
        wanderPoint.setMag(100);
        wanderPoint.add(this.pos);
        // fill(255, 0, 0);
        // noStroke();
        // circle(wanderPoint.x, wanderPoint.y, 8);

        let wanderRadius = 50;
        // noFill();
        // stroke(255);
        // circle(wanderPoint.x, wanderPoint.y, wanderRadius*2);

        // line(this.pos.x, this.pos.y, wanderPoint.x, wanderPoint.y);

        let theta = this.wanderTheta + this.vel.heading();
        let x = wanderRadius * cos(theta);
        let y = wanderRadius * sin(theta);
        wanderPoint.add(x, y);
        // fill(0, 255, 0);
        // noStroke();
        // circle(wanderPoint.x, wanderPoint.y, 16);

        // stroke(255);
        // line(this.pos.x, this.pos.y, wanderPoint.x, wanderPoint.y);

        let steer = wanderPoint.sub(this.pos);
        steer.setMag(this.maxForce);
        this.applyForce(steer);

        let displaceRange = 0.3;
        this.wanderTheta += random(-displaceRange, displaceRange);
    }
    flee(target) {
        return this.seek(target).mult(-1);
    }

    getEta() {
        return this.eta;
    }

    seek(target, arrival = false) {
        // let desired = p5.Vector.sub(target, this.pos);
        let force = p5.Vector.sub(target, this.pos);
        let desireSpeed = this.maxSpeed;


        if(arrival) {
            let slowRadius = 300;
            let distance = force.mag();
            this.dt = distance;

            if(distance < slowRadius) {
                desireSpeed = map(distance, 0, slowRadius, 0, this.maxSpeed);
            }
            this.eta = Math.floor(distance / this.maxSpeed);
        }

        force.setMag(desireSpeed);
        force.sub(this.vel);
        force.limit(this.maxForce);
        return force;
        // this.applyForce(force);
    }

    evade(vehicle) {
        let pursuit = this.pursue(vehicle);
        pursuit.mult(-1);
        return pursuit;
    }

    pursue(vehicle) {
        let target = vehicle.pos.copy();
        let prediction = vehicle.vel.copy();
        prediction.mult(10);
        target.add(prediction);
        fill(0, 255, 0);
        circle(target.x, target.y, 16);
        return this.seek(target);
    }

    arrive(target) {
       return this.seek(target, true);
    }
    applyForce(force) {
        this.acc.add(force);
    }

    update() {
        this.vel.add(this.acc);
        this.vel.limit(this.maxSpeed);
        this.pos.add(this.vel);
        this.acc.set(0, 0);

        this.path.push(this.pos.copy());
    }

    show() {
        stroke(255);
        strokeWeight(2);
        fill(255);
        push();
        translate(this.pos.x, this.pos.y);
        rotate(this.vel.heading());
        triangle(-this.r, -this.r/2, -this.r, this.r/2, this.r, 0);
        pop();

        // beginShape();
        // noFill();
        // stroke(255);
        // for(let v of this.path) {
        //     vertex(v.x, v.y);
        // }
        // endShape();
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


/*
kernel32.lib
user32.lib
gdi32.lib
winspool.lib
comdlg32.lib
advapi32.lib
shell32.lib
ole32.lib
oleaut32.lib
uuid.lib
odbc32.lib
odbccp32.lib
*/