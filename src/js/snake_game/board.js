class Board {
  constructor(cols, rows, sz) {
    this.cols = cols;
    this.rows = rows;
    this.size = sz;
    this.board = [];
    this.dir = createVector(1, 0);

    for(let i = 0; i < this.cols; ++i) {
      this.board[i] = [];
      for(let j = 0; j < this.rows; ++j) {
        this.board[i][j] = 0;
      }
    }

    this.head = createVector(int(random(0, this.cols)), int(random(0, this.rows)));
    this.tail = this.head.copy();
    this.board[this.head.x][this.head.y] = 1;
    this.length = 1;
    this.food = createVector(0, 0);
    this.getFood();
  }

  getFood() {
    while(true) {
      this.food = createVector(int(random(0, this.cols)), int(random(0, this.rows)));
      if(this.board[this.food.x][this.food.y] == 0) {
        this.board[this.food.x][this.food.y] = -1;
        break;
      }
    }
  }

  update() {
    this.head.add(this.dir);

    if(this.head.x > this.cols - 1) {
      this.head.x = 0;
    }
    if(this.head.x < 0) {
      this.head.x = this.cols - 1;
    }
    if(this.head.y > this.rows - 1) {
      this.head.y = 0;
    }
    if(this.head.y < 0) {
      this.head.y = this.rows - 1;
    }

    if(this.board[this.head.x][this.head.y] > 1) {
      textAlign(CENTER, CENTER);
      fill(255);
      textSize(50);
      text("GAME OVER", width/2, height/2);
      this.dir.set(0, 0);
      noLoop();
    }

    let foodEaten = false;

    if(this.head.dist(this.food) == 0) {
      this.length += 1;
      this.board[this.head.x][this.head.y] = this.length + 1;
      foodEaten = true;
      this.getFood();
    }

    for(let i = 0; i < this.cols; ++i) {
      for(let j = 0; j < this.rows; ++j) {
        if(this.board[i][j] > 0) {
          if( foodEaten && (this.board[i][j] > 0) && (this.board[i][j] < this.length)) {
            this.board[i][j] += 1;
          }
          this.board[i][j] -= 1;
        }
      }
    }
  }

  setDirection(dir) {
    this.dir = dir.copy();
  }

  drawBoundary() {
    noFill();
    stroke(255, 255, 255, 100);
    let off = borderOffset;
    rect(off, off, width - (off*2), height - (off*2 + 150));
  }

  draw() {
    this.board[this.head.x][this.head.y] = this.length;
    this.drawBoundary();
    let offset = borderOffset;

    for(let i = 0; i < this.cols; ++i) {
      for(let j = 0; j < this.rows; ++j) {
        if(this.board[i][j] == 0 && showGrid) {
          noFill();
          stroke(255, 255, 255, 50);
          rect(i*this.size+offset, j*this.size+offset, this.size, this.size);
        } else if(this.board[i][j] > 0) {
          if(this.board[i][j] == this.length) {
            fill("cyan");
          } else {
            fill("red");
          }

          noStroke();
          rect(i*this.size+offset, j*this.size+offset, this.size, this.size);
        } else if(this.board[i][j] == -1) {
          fill("orange");
          noStroke();
          rect(i*this.size+offset, j*this.size+offset, this.size, this.size);
        }

        // textAlign(CENTER, CENTER);
        // fill(255);
        // textSize(10);
        // text(this.board[i][j], (i * this.size) + (this.size/2), (j * this.size) + (this.size/2));

      }
    }
    fill(255);
    textSize(14);
    text(`Score: ${this.length-1}`, 10, height - (130));
    text(`Level: ${gameLevel}`, 10, height - (100));

    if(this.length > 51) {
      gameLevel = 6;
      frameRate(18);
    } else if(this.length > 41) {
      gameLevel = 5;
      frameRate(15);
    } else if(this.length > 31) {
      gameLevel = 4;
      frameRate(12);
    } else if(this.length > 21) {
      gameLevel = 3;
      frameRate(10);
    } else if(this.length > 11) {
      gameLevel = 2;
      frameRate(8);
    }
  }
}
