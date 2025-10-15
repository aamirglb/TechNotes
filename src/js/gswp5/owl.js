let canvas;

function setup() {
    canvas = createCanvas(480, 120);
    canvas.parent('p5-container');
}

function draw() {
    background(204);
    randomSeed(0);
    for(let i = 35; i < width + 40; i += 40) {
        let gray = int(random(0, 102));
        let scalar = random(0.25, 1.0);
        owl(i, 110, gray, scalar);
    }
    // owl(110, 110);
    // owl(180, 110);
}

function owl(x, y, g, s) {
    push();

    translate(x, y);
    scale(s);
    stroke(g);

    strokeWeight(70);

    line(0, -35, 0, -65);  // body
    noStroke();
    fill(255-g);
    ellipse(-17.5, -65, 35, 35);  // left eye dome
    ellipse(17.5, -65, 35, 35);   // right eye dome
    arc(0, -65, 70, 70, 0, PI);   // chin

    fill(g);
    ellipse(-14, -65, 8, 8); // left eye
    ellipse(14, -65, 8, 8);  // right eye
    quad(0, -58, 4, -51, 0, -44, -4, -51);
    pop();
}