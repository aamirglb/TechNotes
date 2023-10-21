let nums = [0x7E, 0x30, 0x6D, 0x79, 0x33, 0x5B, 0x5F, 0x70, 0x7F, 0x7B];
let index = 0;

function setup() {
    createCanvas(1000, 800)
    background(100);
    frameRate(3);
}

function draw() {
    background(0);
    sevenSegment(nums[index])
    index = (index + 1) % nums.length;
}

function getColor(val, shift) {
    let red =  255;
    let green = 0;
    let blue = 0;
    if( (val >> shift) & 1 ) {
        alpha = 255;
    } else {
        alpha = 10;//255 / 3;
    }
    // let alpha = 255 * (  );
    return color(red, green, blue, alpha);
}

function sevenSegment(val) {

    // stroke(255);
    // text('A', 80, 30);

    push();
    
    // fill(0);
    noFill()
    stroke(0)
    fill(getColor(val, 6));
    rect(60, 20, 80-2, 20-2, 6);  // A

    fill(getColor(val, 5));
    rect(140, 40, 20-2, 100-2, 6);  // B

    fill(getColor(val, 4));
    rect(140, 160, 20-2, 100-2, 6); // C

    fill(getColor(val, 3));
    rect(60, 260, 80-2, 20-2, 6);   // D

    fill(getColor(val, 2));
    rect(40, 160, 20-2, 100-2, 6);  // E

    fill(getColor(val, 1));
    rect(40, 40, 20-2, 100-2, 6);   // F

    fill(getColor(val, 0));
    rect(60, 140, 80-2, 20-2, 6);    // G
}

