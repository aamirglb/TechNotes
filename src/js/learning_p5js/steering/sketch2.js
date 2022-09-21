let font;
let vehicles = [];

function preload() {
    font = loadFont('AvenirNextLTProDemi.otf');
}

function setup() {
    createCanvas(700, 300);
    background(51);
    textFont(font);
    textSize(192);
    fill(255);
    noStroke();
    // text('train', 100, 200);

    let points = font.textToPoints('aamir', 100, 200)
    for(let p of points) {
        let vehicle = new Vehicle(p.x, p.y);
        vehicles.push(vehicle);
        // stroke(255);
        // strokeWeight(8);
        // point (p.x, p.y);
    }
}

function draw() {
    background(51);
    for(let v of vehicles) {
        v.behaviours();
        v.update();
        v.show();
    }
}