function make2DArray(cols, rows) {
  let arr = new Array(cols);
  for(let i = 0;  i < arr.length; ++i) {
    arr[i] = new Array(rows);
    for(let j = 0; j < arr[i].length; ++j) {
      arr[i][j] = 0;
    }
  }
  return arr;
}

let grid;
let w = 4;
let hueValue = 100;
let p;

function setup() {
  createCanvas(600, 800);
  colorMode(HSB, 360, 255, 255);
  cols = width / w;
  rows = height / w;
  grid = make2DArray(cols, rows);

  for(let i = 0; i < cols; ++i) {
    for(let j = 0; j < rows; ++j) {
      grid[i][j] = 0;
    }
  }
  p = createP('');
}

function draw() {

  if(random(1) < 0.2) {
    for(let i = -2; i < 2; ++i) {
      let x = floor(random(cols/2)) * w;
      let y = floor(random(10));
      // grid[x][y] = hueValue;

      let matrix = 5;
      let extent = floor(matrix/2);

      for(let i = -extent; i <= extent; ++i) {
        for(let j = -extent; j <= extent; ++j) {
          if(random(1) < 0.75) {
            let col = x + i;
            let row = y + j;
            if(col >= 0 && col <= cols - 1 && row >= 0 && row <= rows - 1) {
              grid[col][row] = hueValue;
            }
          }
        }
      }
    }
    hueValue += 1;
    if(hueValue > 360) {
      hueValue = 1;
    }
  }

  background(0);
  for(let i = 0; i < cols; ++i) {
    for(let j = 0; j < rows; ++j) {
      noStroke();
      if(grid[i][j] > 1) {
        fill(grid[i][j], 255, 255);
        let x = i * w;
        let y = j * w;
        square(x, y, w);
      }
    }
  }

  let nextGrid = make2DArray(cols, rows);
  for(let i = 0; i < cols; ++i) {
    for(let j = 0; j < rows; ++j) {
      let state = grid[i][j];
      if(state > 0) {
        let dir = random([-1, 1]);

        let below = grid[i][j+1];

        let left; // = grid[i-dir][j+1];
        let right; // = grid[i+dir][j+1];

        if( i + dir >= 0 && i + dir <= cols - 1) {
          right = grid[i+dir][j+1];
        }
        if(i - dir >= 0 && i - dir <= cols - 1) {
          left = grid[i-dir][j+1];
        }

        if(below === 0 ) {
          nextGrid[i][j+1] = grid[i][j];
        } else if(right == 0) {
          nextGrid[i+dir][j+1] = grid[i][j];
        } else if(left === 0) {
          nextGrid[i-dir][j+1] = grid[i][j];
        } else {
          nextGrid[i][j] = grid[i][j];
        }
      }
    }
  }
  grid = nextGrid;
  p.html(floor(frameRate()));
}

function mouseDragged() {
  let mouseCol = floor(mouseX / w);
  let mouseRow = floor(mouseY / w);

  let matrix = 5;
  let extent = floor(matrix/2);

  for(let i = -extent; i <= extent; ++i) {
    for(let j = -extent; j <= extent; ++j) {
      if(random(1) < 0.75) {
        let col = mouseCol + i;
        let row = mouseRow + j;
        if(col >= 0 && col <= cols - 1 && row >= 0 && row <= rows - 1) {
          grid[col][row] = hueValue;
        }
      }
    }
  }
  hueValue += 1;
  if(hueValue > 360) {
    hueValue = 1;
  }
}