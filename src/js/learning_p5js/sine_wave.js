class Wave {
    constructor(amp, period, phase) {
        this.amplitude = amp;
        this.period = period;
        this.phase = phase;
    }
    calculate(x) {
        return sin(this.phase + TWO_PI * x / this.period) * this.amplitude;
    }

    update() {
        this.phase += 0.02;
    }
}

let waves = [];
let angles = [];
let angleV = [];
let r = 4;

function setup() {
    createCanvas(600, 400);
    // let total = floor(width/(r*2));
    // for(let i = 0; i < total+1; ++i) {
    //     angles[i] = map(i, 0, total, 0, 2*TWO_PI);
    //     // angleV[i] = random(-0.1, 0.1);
    //     angleV[i] = 0.01 + i / 100;
    // }
    for(let i = 0; i < 5; ++i) {
        waves[i] = new Wave(random(20, 80), random(100, 600), random(TWO_PI));
    }
}

function draw() {
    background(0);

    for(let x = 0; x < width; x+=10) {
        let y = 0;
        for(let wave of waves) {
            y += wave.calculate(x);
        }
        noStroke();
        ellipse(x, y + height/2, 16);
    }

    for(let wave of waves) {
        wave.update();
    }
    // background(0);
    // translate(300, 200);
    // // fill(252, 238, 33);
    // noFill();
    // stroke(252, 238, 33);

    // beginShape();
    // for(let i = 0; i < angles.length; ++i) {
    //     let y = map(sin(angles[i]), -1, 1, -200, 200);
    //     strokeWeight(4);
    //     let x = map(i, 0, angles.length, -300, 300);
    //     // line(x, 0, x, y);
    //     circle(x, y, r*2);
    //     // angles[i] += angleV[i];
    //     // vertex(x, y);
    //     angles[i] += 0.02;
    // }
    // endShape();

    // angle += angleV;
}