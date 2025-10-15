let cities;
function preload() {
    cities = loadTable("uszips.csv", "header");
}

function setup() {
    let canvas = createCanvas(480, 240);
    fill(255, 150);
    noStroke();
}

function draw() {
    background(0);
    let xoffset = map(mouseX, 0, width, -width*3, -width);
    // console.log(xoffset);
    translate(xoffset, -600);
    scale(10);
    for(let i = 0; i < cities.getRowCount(); ++i) {
        let latitude = cities.getNum(i, "lat");
        let longitude = cities.getNum(i, "lng");
        setXY(latitude, longitude);
    }
}

function setXY(lat, lng) {
    let x = map(lng, -180, 180, 0, width);
    let y = map(lat, 90, -90, 0, height);
    ellipse(x, y, 0.25, 0.25);
}