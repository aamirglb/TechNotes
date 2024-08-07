class Letter {
    constructor(x, y, scl) {
        this.pos = createVector(x, y);
        this.scl = scl;
    }

    display() {
        this.calculateVelocity(center, this.pos);
        this.shift = map(this.distance, 0, 1000, 10, 0);
        this.osc = sin(TWO_PI * angle + this.shift);

        this.fontS = map(this.osc, -1, 1, 0.3, 1.5);

        push();
        translate(this.pos.x + (this.vel.x * this.osc), 
            this.pos.y + (this.vel.y * this.osc));
        fill(255);
        // ellipse(0, 0, 10, 10);
        scale(this.fontS);
        textAlign(CENTER, CENTER);
        text("A", 0, 0);
        pop();
    }

    calculateAngle() {
    let x = center.x - this.pos.x;
    let y = center.y - this.pos.y;

    let theta = atan(y/x);

    if(this.pos.x > center.x && this.pos.y > center.y) {
        return theta;
    } else if(this.pos.x <= center.x && this.pos.y >= center.y) {
        return PI - abs(theta);
    } else if(this.pos.x <= center.x && this.pos.y <= center.y) {
        return PI + theta;
    } else if(this.pos.x >= center.x && this.pos.y <= center.y) {
        return TWO_PI - abs(theta);
    }
    return theta;
}


calculateVelocity() {
    let angle = this.calculateAngle(center, this.pos);
    this.vel = p5.Vector.fromAngle(angle);
    this.distance = dist(center.x, center.y, this.pos.x, this.pos.y);
    this.vel.setMag(this.distance * this.scl);
    // line(center.x, center.y, center.x + this.vel.x, center.y + this.vel.y);
}
}