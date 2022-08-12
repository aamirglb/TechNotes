let x, y;

function setup() {
    createCanvas(400, 400);
    x = 200;
    y = 200;
    background(51);
}


function draw() {

    stroke(255);
    strokeWeight(8);
    point(x, y);

    let r = floor(random(4));
    switch(r) {
        case 0:
            x += 1;
            break;
        case 1:
            x -= 1;
            break;
        case 2:
            y += 1;
            break;
        case 3:
            y -= 1;
            break;
    }


}