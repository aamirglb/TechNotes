let board;
let snake;
let size = 20;
let dir;
let pause = false;
let showGrid = false;
let borderOffset = 4;
let gameLevel = 1;

function keyPressed() {
  if(keyCode === LEFT_ARROW) {
    dir = createVector(-1, 0);
  } else if(keyCode === RIGHT_ARROW) {
    dir = createVector(1, 0);
  } else if(keyCode === UP_ARROW) {
    dir = createVector(0, -1);
  } else if(keyCode === DOWN_ARROW) {
    dir = createVector(0, 1);
  } else if(keyCode === 32) {
    pause = !pause;
    if(pause) {
      noLoop();
    } else {
      loop();
    }
  }
  board.setDirection(dir);
}

function setup() {
  let canvas = createCanvas(408, 408+150);
  canvas.parent('p5-container');

  let gridCheckbox = createCheckbox('Grid', false);
  gridCheckbox.changed(checkboxChanged);

  gridCheckbox.parent('grid');
  board = new Board(20, 20, size);
  // snake = new Snake(10, 10, size);
  dir = createVector(1, 0);
  board.setDirection(dir);

  frameRate(4);
}

function checkboxChanged() {
  showGrid = this.checked();
}

function draw() {
  background(0);
  board.update();
  board.draw();
}
