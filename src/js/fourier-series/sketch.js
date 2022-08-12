let time = 0;
let wave = [];
let slider;
let colors = [ [255, 0, 0], [0, 255, 0], [0, 0, 255]];

function setup() {
    createCanvas(800, 400);
    slider = createSlider(1, 100, 1);
}

function draw() {
    background(0);
    translate(200, 200);

    let x = 0;
    let y = 0;
    // let x = radius * cos(time);
    // let y = radius * sin(time);

    for(let i = 0; i < slider.value(); ++i) {
        let prevx = x;
        let prevy = y;

        let n = i * 2 + 1;
        let radius = 75 * (4 / (n * PI));
        x += radius *  cos(n * time);
        y += radius * sin(n * time);

        stroke(255, 100);
        noFill();
        ellipse(prevx, prevy, radius*2);

        fill(255);
        stroke(255)
        // stroke(...colors[i % 3], 100);
        line(prevx, prevy, x, y);
        // ellipse(x, y, 8);
    }
    wave.unshift(y);
    translate(200, 0);
    line(x-200, y, 0, wave[0]);

    beginShape();
    noFill();
    for(let i = 0; i < wave.length; ++i) {
        vertex(i, wave[i]);
    }
    endShape();

    time += 0.05;

    if(wave.length > 250) {
        wave.pop();
    }

}

function getIndex(i, j) {
    if( i < 0 || j < 0 || i > cols - 1 || j > rows - 1) {
        return -1;
    }
    return i + (j * cols);
}

const removeWalls = (c, n) => {
    var x = c.i - n.i;
    if(x === 1) {
        c.walls.left = false;
        n.walls.right = false;
    } else if( x === -1) {
        c.walls.right = false;
        n.walls.left = false;
    }

    var y = c.j - n.j;
    if(y === 1) {
        c.walls.top = false;
        n.walls.bottom = false;
    } else if( y === -1) {
        c.walls.bottom = false;
        n.walls.top = false;
    }
}
