var cols, rows;
var w = 20;
var grid = [];
var current;
var stack = [];

function setup() {
    createCanvas(800, 800);
    cols = floor(width/w);
    rows = floor(height/w);
    // frameRate(5);
    for(let j = 0; j < rows; ++j) {
        for(let i = 0; i < cols; ++i) {
            var cell = new Cell(i, j);
            grid.push(cell);
        }
    }
    current = grid[0];
}

function draw() {
    background(51);
    for(let i = 0; i < grid.length; ++i) {
        grid[i].show();
    }
    current.visited = true;
    current.highlight();

    // Step 1
    var next = current.checkNeighbors();
    if(next) {
        next.visited = true;

        // step 2
        stack.push(current);

        // Step 3
        removeWalls(current, next);
        // Step 4
        current = next;
    } else {
        if(stack.length > 0) {
            var cell = stack.pop();
            console.log("backtracking to cell (", cell.i, ", ",cell.j, ")");
            current = cell;
        }
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
