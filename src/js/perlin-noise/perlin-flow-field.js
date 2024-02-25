
let inc = 0.1;
let scl = 10;
let cols, rows;
let zoff = 0;

let particles = [];
let flowfield;

let fr;

function setup() {
    createCanvas(800, 800);
    cols = floor(width / scl);
    rows = floor(height / scl);
    fr = createP('');

    flowfield = new Array(cols * rows);

    for(let i = 0; i < 1500; ++i) {
        particles[i] = new Particle();
    }
    background(255)
}

function draw() {
    let yoff = 0;

    for(let y = 0; y < rows; ++y) {
        let xoff = 0;
        for(let x = 0; x < cols; ++x) {
            let index = x + y * cols;
            // let r = random(255);
            let angle = noise(xoff, yoff, zoff) * TWO_PI * 4;
            let v = p5.Vector.fromAngle(angle);
            v.setMag(0.5);
            flowfield[index] = v;

            // stroke(0, 50);
            // push();
            // translate(x*scl, y*scl);
            // rotate(v.heading());
            // strokeWeight(1);
            // line(0, 0, scl, 0);
            // pop();

            // fill(r);
            // rect(x*scl, y*scl, scl, scl);
            xoff += inc;
        }
        yoff += inc;
        zoff += 0.0005;
    }

    for(let i = 0; i < particles.length; ++i) {
        particles[i].follow(flowfield);
        particles[i].update();
        particles[i].edges();
        particles[i].show();
    }
    fr.html(floor(frameRate()));
    // noLoop();
}