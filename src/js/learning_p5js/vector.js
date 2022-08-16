function setup() {
    createCanvas(400, 400);
    // background(0);
}

function draw() {
    background(0);
    let pos = createVector(200, 200);
    let mouse = createVector(mouseX, mouseY);
    let v = p5.Vector.sub(mouse, pos);

    // normalize a vector - change it to unit vector but maintain its direction
    // let m = v.mag();
    // v.div(m);
    // v.mult(50);

    // // same as above
    // v.normalize();
    // v.mult(50);

    // same as above
    v.setMag(50);

    translate(width/2, height/2);
    strokeWeight(4);
    stroke(255);
    line(0, 0, v.x, v.y);

    // strokeWeight(1);
    // stroke(200, 200);
    // line(0, 0, width/2, 0);
    // line(0, 0, -width/2, 0);
    // line(0, 0, 0, height/2);
    // line(0, 0, 0, -height/2);

    // // pick a vector with random direction and fixed magnitude
    // // unit vector - length 1 and a direction
    // // let v = createVector(100, 0);
    // // let v = createVector(random(-100, 100), random(-100, 100));
    // let v = p5.Vector.random2D();
    // v.mult(random(50, 100));

    // strokeWeight(4);
    // stroke(255, 50);
    // line(0, 0, v.x, v.y);
}