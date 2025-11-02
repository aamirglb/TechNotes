let grid;
let offset = 4;
let startX = 10;
let startY = 10;
let cellSize = 20;
let stack = [];
let startCell;

class Cell {
  constructor(row, col) {
    this.y = row;
    this.x = col;
    this.size = 20;
    this.visited = false;
    this.backtracked = false;
    this.neighbours = [];
  }

  drawAsStart() {
    stroke(255, 255, 255);
    fill(255, 0, 0);
    let offset = 6 + 2;
    rect(this.x * this.size + offset, this.y * this.size + offset, this.size - 4, this.size - 4);
  }

  drawAsCurrent() {
    stroke(255, 255, 255);
    fill(255, 0, 255);
    let offset = 6 + 2;
    rect(this.x * this.size + offset, this.y * this.size + offset, this.size - 4, this.size - 4);
  }

  draw() {
    stroke(255, 255, 255);
    let offset = 6 + 2;
    noFill();
    rect(this.x * this.size + offset, this.y * this.size + offset, this.size - 4, this.size - 4);

    if(this.visited) {
      fill(255, 255, 0);
      // noStroke();
      rect(this.x * this.size + offset, this.y * this.size + offset, this.size - 4, this.size - 4);
    }
    if(this.backtracked) {
      fill(0, 255, 255);
      // noStroke();
      rect(this.x * this.size + offset, this.y * this.size + offset, this.size - 4, this.size - 4);
    }
  }

  unvisit() {
    this.visited = false;
  }

  visit() {
    this.visited = true;
  }

  backtrack() {
    this.backtracked = true;
  }
}

class Grid {
  constructor(rows, cols, cellSize) {
    this.grid = [];
    this.rows = rows;
    this.cols = cols;
    this.cellSize = cellSize;
    for (let r = 0; r < this.rows; ++r) {
      this.grid[r] = [];
      for (let c = 0; c < this.cols; ++c) {
        this.grid[r][c] = new Cell(r, c);
      }
    }
  }

  backtrack(cell) {
    cell.backtrack()
  }

  getCell(row, col) {
    return this.grid[row][col];
  }

  drawCurrent(cell) {
    cell.drawAsCurrent();
  }

  drawStart(cell) {
    cell.drawAsStart();
  }

  getVisitedCount() {
    let count = 0;
    for (let r = 0; r < this.rows; ++r) {
      for (let c = 0; c < this.cols; ++c) {
        if(this.grid[r][c].visited == true) {
          count += 1;
        }
      }
    }
    return count;
  }

  getNeighbours(cell) {
    if(cell.neighbours.length === 0) {
      let c = cell.x;
      let r = cell.y;
      if (r > 0) cell.neighbours.push(this.grid[r - 1][c]);
      if (r < this.rows - 1) cell.neighbours.push(this.grid[r + 1][c]);
      if (c > 0) cell.neighbours.push(this.grid[r][c - 1]);
      if (c < this.cols - 1) cell.neighbours.push(this.grid[r][c + 1]);
    }
    return cell.neighbours;
  }

  draw() {
    for (let r = 0; r < this.rows; ++r) {
      for (let c = 0; c < this.cols; ++c) {
        this.grid[r][c].draw();
      }
    }
  }

  unvisitAll() {
    for (let r = 0; r < this.rows; ++r) {
      for (let c = 0; c < this.cols; ++c) {
        this.grid[r][c].unvisit();
      }
    }
  }

  walk() {
    let r = Math.floor(Math.random() * 4);
    // move right
    if(r === 0) {
      if (startX < this.cols - 1) startX += 1;
      // else startX -= 1;
    } else if(r===1) {
      if (startX > 0) startX -= 1;
      // else startX += 1;
    } else if(r===2) {
      if (startY < this.rows - 1) startY += 1;
      // else startY -= 1;
    } else if(r===3) {
      if (startY < 0) startY -= 1;
      // else startY += 1;
    }
    // console.log(startY, startX);

    this.grid[startY][startX].visit();
  }

  debug() {
    let count = 0;
    for (let r = 0; r < this.rows; ++r) {
      for (let c = 0; c < this.cols; ++c) {
        if (this.grid[r][c].visited == true) {
          count += 1;
        }
      }
    }
    console.log(`Visited cell count: ${count}`)
  }
}

function testNeighbours() {
  if(mouseX > 8 && mouseX < (width - 16) && mouseY > 8 && mouseY < (height - 16)) {
    let row = Math.floor( (mouseY - 6) / cellSize);
    let col = Math.floor( (mouseX - 6) / cellSize);
    console.log(row, col);
    let cell = grid.getCell(row, col);
    let neighbours = grid.getNeighbours(cell);
    for(let n of neighbours) {
      n.visit();
    }
  }
}

function drawBoundary() {
  stroke("white");
  noFill();
  rect(4, 4, width - 8, height - 8);
}

function getRandomInt(max) {
  return Math.floor(Math.random() * max);
}

function setup() {
  canvas = createCanvas(812, 812);
  canvas.parent('p5-container');
  grid = new Grid(40, 40, 20);
  let r = getRandomInt(40);
  let c = getRandomInt(40);
  startCell = grid.getCell(r, c);
  stack.push(startCell);
}

function draw() {
  // frameRate(30);
  background("black");
  drawBoundary();

  // grid.walk();
  // grid.unvisitAll();
  // testNeighbours();

  if(stack.length === 0) {
    console.log("Done!!");
    grid.draw();
    grid.drawCurrent(startCell);
    noLoop();
    return;
  }

  let current = stack[stack.length - 1];
  // get neighbours
  let neighbours = grid.getNeighbours(current);

  let allVisited = true;
  // check if all neighbours are visited
  for(let n of neighbours) {
    if(n.visited === false) {
      allVisited = false;
      break;
    }
  }
  if(allVisited) {
    // backtrack
    let c = stack.pop();
    grid.backtrack(c);
  } else {
    let r = getRandomInt(neighbours.length);
    if(neighbours[r].visited === false) {
      neighbours[r].visit();
      stack.push(neighbours[r]);
    }
  }
  grid.draw();
  grid.drawCurrent(current);
  grid.drawStart(startCell);

  const visited = document.getElementById('visited');
  const unvisited = document.getElementById('unvisited');
  visited.innerHTML = `visited: ${grid.getVisitedCount()}`;
  unvisited.innerHTML = `unvisited: ${1600 - grid.getVisitedCount()}`;
}
