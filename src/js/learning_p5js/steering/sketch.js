let vehicle;
let target;
let path;

function setup() {
    createCanvas(800, 800);
    vehicle = new Vehicle(100, 100);
    vehicle.vel.x = 2;
    path = new Path(0, 200, 800, 200);
}

function draw() {
    background(0);

    path.end.y = mouseY;
    let force = vehicle.follow(path);
    vehicle.applyForce(force);

    // vehicle.wander();

    vehicle.update();
    vehicle.show();
    vehicle.edges();

    path.show();
    // fill(255, 0, 0);
    // noStroke();
    // target = createVector(mouseX, mouseY);
    // // target = createVector(width * .8, height * .8);
    // circle(target.x, target.y, 32);
    // noFill();
    // stroke(0, 255, 0);
    // circle(target.x, target.y, 332);

    // // let steering = vehicle.seek(target);
    // let steering = vehicle.arrive(target);
    // vehicle.applyForce(steering);

    // vehicle.seek(target);
    // vehicle.update();
    // vehicle.show();

    // textSize(16);
    // fill(0, 255, 0);
    // noStroke();
    // let eta = "ETA: " + vehicle.getEta();
    // text(eta, width - (width * .20), 30);
}