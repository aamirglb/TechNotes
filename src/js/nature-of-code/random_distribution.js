let randomCounts = [];
let total = 20;
let offset = 4;

function setup() {
    createCanvas(640, 240 * 2 + 20);

    for(let i = 0; i < total; ++i) {
        randomCounts[i] = 0;
    }
}

function draw() {
    background(255);

    line(0, 0, 0, height / 2);
    line(0, height / 2, width, height / 2);

    line(0, height / 2  + 20, 0, height);
    line(0, height, width, height);
    // pick a random num betn 0-total and increase the count
    let index = floor(random(randomCounts.length));
    randomCounts[index] += 1;

    // draw the bar graph
    noFill();
    stroke(0);
    strokeWeight(1);
    let w = width / randomCounts.length;

    beginShape();
    for(let i = 0; i < randomCounts.length; ++i) {
        vertex(i*w + (w/2), ( height / 2 ) - randomCounts[i]);
    }
    endShape();

    // stroke('red');
    // strokeWeight(4);
    // beginShape();
    // for(let i = 0; i < randomCounts.length; ++i) {
    //     vertex(i*w + (w/2), height - randomCounts[i]);
    // }
    // endShape();

    stroke(0);
    strokeWeight(1);
    fill(127);
    for(let i = 0; i < randomCounts.length; ++i) {
        rect(i*w, height - randomCounts[i], w - 1 - offset, randomCounts[i]);
    }
}