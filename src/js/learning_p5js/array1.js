let languages = ["C", "C++", "C#", "Java", "Python", "Javascript"];
let index = 0;

function setup() {
    createCanvas(600, 400);
}

function draw() {
    background(0);

    fill(255);
    textSize(32);
    text(languages[index], 12, 200);
}

function mousePressed() {
    ++index;
    if(index == languages.length) index = 0;
}