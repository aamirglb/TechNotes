class Blob {
    constructor(x, y) {
        this.pos = createVector(x, y);
        this.vel = createVector();
        let angle = random(0, 2 * PI);
        this.vel.x = random(2, 5) * Math.cos(angle);
        this.vel.y = random(2, 5) * Math.sin(angle);

        // this.vel.mult(random(6, 10));
        this.r = random(200, 240);
    }

    show() {
        noFill();
        stroke(0);
        strokeWeight(4);
        ellipse(this.pos.x, this.pos.y, this.r * 2, this.r * 2);
    }

    update() {
        this.pos.add(this.vel);

        if(this.pos.x > width || this.pos.x < 0) {
            this.vel.x *= -1;
        }

        if(this.pos.y > height || this.pos.y < 0) {
            this.vel.y *= -1;
        }
    }
}

let blobs = [];
let totalBlobs = 10;

function setup() {
    createCanvas(640, 360);
    colorMode(HSB)
    for(let i = 0; i < totalBlobs; ++i) {
        blobs.push(new Blob(random(0, width), random(0, height)));
    }
}

function draw() {
    background(51);
    loadPixels();

    for(let x = 0; x < width; ++x) {
        for(let y = 0; y < height; ++y) {
            let sum = 0;
            for(let blob of blobs) {
                // let d = dist(x, y, blob.pos.x, blob.pos.y);
                let xdiff = x - blob.pos.x;
                let ydiff = y - blob.pos.y;
                let d = sqrt(xdiff * xdiff + ydiff * ydiff);
                sum += 10 * blob.r / d;
            }
            set(x, y, color(sum, 255, 255));

            // let d = dist(x, y, width/2, height/2);
            // let d = dist(x, y, blobs[0].pos.x, blobs[0].pos.y);
            // let pix = (x + y * width) * 4;
            // // let col = 1000 * blobs[0].r / d;
            // pixels[pix + 0] = sum;
            // pixels[pix + 1] = 255;
            // pixels[pix + 2] = 255;
            // pixels[pix + 3] = 255;
            // pixels[index] = color(255, 0, 255);
        }
    }
    updatePixels();
    for(let blob of blobs) {
        blob.update();
        // blob.show();
    }

}