let xDir = Math.random() < 0.5 ? -1 : 1;
let yDir = Math.random() < 0.5 ? -1 : 1;

let stars = [];

function setup() {
    createCanvas(400, 400);
    for( let i = 0; i < 50; ++i) {
        let factor = 10;
        stars[i] = createVector(
            random(-width * factor, width * factor), 
            random(-height * factor, height * factor),
            random(10, width));
    }
    // startPos = createVector(width/2, height/2, 0);
    // slider = createSlider(1, 100, 10);
}

function draw() {
    background(0, 0, 0);
    fill(255);
    translate(width/2, height/2);

    for(let star of stars) {
        let x = star.x / star.z;
        let y = star.y / star.z;
        let d = map(star.z, 0, 400, 10, 1);
        fill(random(50, 255), random(40, 255), random(30, 255));
        circle( x, y, d);
        star.z -= 5;
        if( star.z < 10) {
            star.z = 400;
        }
    }
    
    // startPos.x += xDir;
    // startPos.y += yDir;

    // if( startPos.x >= width || startPos.x <= 0)
    // {
    //     xDir *= -1;
    //     // startPos.x *= -1;
    //     // startPos.x += -20;
    //     console.log("changing x direction");
    // }

    // if(startPos.y >= height || startPos.y <= 0)
    // {
    //     yDir *= -1;
    //     // startPos.y *= -1;
    //     // startPos.y += -20;
    //     console.log("changing y direction");
    // }
}

