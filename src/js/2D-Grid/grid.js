let grid = [];
let cellWidth = 32;
let cellHeight = 32;
let cellSize;
let count = 0;
let prevCount = 0;
let canvas;
let i;
let rows;
let columns;
let useRectectangle;
let randomCell;

// variable for draw() method
let row = 0;
let col = -1;

function setup() {
    canvas = createCanvas(704, 704);
    canvas.parent('p5-container');
    i = 0;
    background(0);
    stroke(0, 255);

    rows = height / cellHeight;
    columns = width / cellWidth;
    useRectectangle = false;
    randomCell = true;

    cellSize = cellWidth - 2;
    for(let r = 0; r < rows; ++r) {
        for(let c = 0; c < columns; ++c) {
            rect((c * cellWidth) + 1, (r * cellHeight) + 1, cellSize, cellSize);
        }
        // console.log((r * cellHeight) + 1);
    }

    for(let r = 0; r < rows; ++r) {
        grid[r] = [];
        for(let c = 0; c < columns; ++c) {
            grid[r][c] = 0;
        }
    }

    console.log("Rows = ", rows, " Columns = ", columns);
    console.log("Using Rectangle: ", useRectectangle);
    console.log("Fill Random Cell = ", randomCell);
}

function columnWiseFill() {
    col += 1;
    if(col > columns) {
        console.log("Column is ", col, " moving to next row ", row);
        col = 0;
        row += 1;
    }

    if(row == rows) {
        return false;
    } else {
        return true;
    }
}

function rowWiseFill() {
    row += 1;
    // console.log(row);
    if(row >= rows) {
        console.log("Row is ", row, " moving to next column ", col);
        row = 0;
        col += 1;
    }

    if(col == columns) {
        return false;
    } else {
        return true;
    }
}

function draw() {
    const fr = document.getElementById('frame-rate');
    frameRate(30);
    let frate = Math.floor(frameRate());
    fr.innerHTML = `Frame Rate: ${frate}`

    count += 1;
    // let row = 0;
    // let col = 0;

    if(randomCell) {
        row = floor(random(height/cellHeight));
        col = floor(random(width/cellWidth));
    }
    else {
        if(!columnWiseFill()) {
            noLoop();
            return;
        }
        // if(!rowWiseFill()) {
        //     noLoop();
        //     return;
        // }
    }

    if( grid[row][col] == 0) {
        i += 1;
        stroke(0, 255);
        grid[row][col] = 1;
        let alpha = map(count, 0, 1000, 50, 255);
        if(count > 1000) {
            alpha = 255;
        }
        fill(255, 0, 255, alpha);
        if(useRectectangle) {
            rect(col*cellWidth + 1, row*cellHeight + 1, cellSize, cellSize);
        } else {
            ellipseMode(CORNER);
            circle(col*cellWidth+1, row*cellHeight+1, cellSize);
        }
        textAlign(CENTER, CENTER);
        // stroke(0, 0, 0, 225);
        noStroke();
        fill(0, 255);
        text(count.toFixed(0), col*cellWidth + (cellWidth/2), row*cellHeight + (cellHeight/2));

        if(col == columns-1) {
            const t = document.getElementById('text-container');
            const p = document.createElement('p');
            p.innerHTML = `${i} => (${row}, ${col}): ${count}  difference: ${count - prevCount}`;
            t.appendChild(p);
        }
        prevCount = count;
    }
}