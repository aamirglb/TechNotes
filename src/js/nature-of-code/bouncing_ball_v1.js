let x = 100;
let y = 100;
let xspeed = 2.5;
let yspeed = 2;
let d = 24;
let r = d / 2;

let choice;
let color;

function setup() {
    createCanvas(640, 340);
    background(255);
}

function draw() {
    background(255);

    line(0, 0, width, 0);
    line(0, 0, 0, height);
    line(0, height, width, height);
    line(width, 0, width, height);

    x = x + xspeed;
    y = y + yspeed;

    if( (x + r) > width || (x - r ) < 0) {
        console.log(x, r);
        xspeed = xspeed * -1;
        // choice = random(3);
        if(d+2 < width) {
        color = random(255);
        d += 2;
        r = d / 2;
        x += xspeed;
        }
        // console.log(d);
    }

    if((y + r) > height || (y - r) < 0) {
        yspeed = yspeed * -1;
        if(d+2 < height) {
        color = random(255);
        d += 2;
        r = d / 2;
        y += yspeed;
        }
        // d += 2;
        // console.log(d, r);
    }

    stroke(0);
    fill(color, color + 10, color - 10);
    circle(x, y, d);
}