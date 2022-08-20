let cols = 5;
let rows = 5;
let grid = new Array(cols);

let openSet = [];
let closedSet = [];
let start;
let end;
let w;
let h;

const heuristic = (a, b) => {
    return dist(a.x, a.y, b.x, b.y);

}
const removeFromArray = (arr, elt) => {
    for(let i = arr.lenght-1; i>=0; --i) {
        arr.splice(i, 1);
    }
}

class Spot {
    constructor(x, y, f, g, h) {
        this.x = x;
        this.y = y;
        this.f = f;
        this.g = g;
        this.h = h;
        this.neighbors = [];
        this.previous = undefined;
    }

    show(color) {
        fill(color);
        // stroke(0)
        noStroke();
        rect(this.x * w, this.y * h, w - 1, h - 1);
    }

    addNeighbors(grid) {
        let i = this.x;
        let j = this.y;

        if(i < cols - 1) {
            this.neighbors.push(grid[i+1][j]);
        }

        if(i > 0) {
            this.neighbors.push(grid[i-1][j]);
        }

        if(j < rows - 1) {
            this.neighbors.push(grid[i][j+1]);
        }

        if(j > 0) {
            this.neighbors.push(grid[i][j-1]);
        }
    }

}

function setup() {
    createCanvas(400, 400);
    w = width / cols;
    h = height / rows;

    for(let i = 0; i < cols; ++i) {
        grid[i] = new Array(rows);
    }

    for(let i = 0; i < cols; ++i) {
        for(let j = 0; j <rows; ++j) {
            grid[i][j] = new Spot(i, j, 0, 0, 0);
        }
    }

    for(let i = 0; i < cols; ++i) {
        for(let j = 0; j <rows; ++j) {
            grid[i][j].addNeighbors(grid);
        }
    }

    start = grid[0][0];
    end = grid[cols - 1][rows - 1];

    openSet.push(start);
}

function draw() {


    if(openSet.lenght > 0) {
        let winner = 0;
        for(let i = 0; i < openSet.length; ++i) {
            if(openSet[i].f < openSet[winner].f) {
                winner = i;
            }
        }

        let current = openSet[winner];

        if(current === end) {
            console.log("DONE!!");
        }

        removeFromArray(openSet, current);
        closedSet.push(current);

        let n = current.neighbors;
        for(let i = 0; i < n.lenght; ++i) {
            let neighbor = n[i];
            neighbor.g = current.g + 1;

            if(!closedSet.includes(neighbor)) {
                let tmpG = current.g + 1;

                if(openSet.includes(neighbor)) {
                    if(tmpG < neighbor.g) {
                        neighbor.g = tmpG
                    }
                } else {
                    neighbor.g = tmpG;
                    openSet.push(neighbor);
                }
                neighbor.h = heuristic(neighbor, end);
                neighbor.f = neighbor.g + neighbor.h;
            }
        }
    } else {
        // no solution
    }

    background(0);
    for(let i = 0; i < cols; ++i) {
        for(let j = 0; j < rows; ++j) {
            grid[i][j].show(color(255));
        }
    }

    for(let i = 0; i < closedSet.length; ++i) {
        closedSet[i].show(color(255, 0, 0));
    }

    for(let i = 0; i < openSet.length; ++i) {
        openSet[i].show(color(0, 255, 0));
    }
}