let x;
let y;
let walkers = [];

class Walker {
  constructor(startX, startY, colr) {
    this.x = startX;
    this.y = startY;
    this.color = colr;
  }

  draw() {
    stroke(this.color);
    strokeWeight(2);
    noFill();
    point(this.x, this.y);
    let r = Math.floor(Math.random() * 4);
    if (r === 0) {
      this.x -= 2;
      if (this.x < 3) this.x = 3;
    }
    else if (r === 1) {
      this.x += 2;
      if (this.x > (width - 3)) this.x = width - 3;
    }
    else if (r === 2) {
      this.y -= 2;
      if (this.y < 3) this.y = 3;
    }
    else if (r === 3) {
      this.y += 2;
      if (this.y > (height - 3)) this.y = height - 3;
    }
  }
}

function setup() {
  canvas = createCanvas(812, 812);
  canvas.parent('p5-container');
  background(0);
  stroke(255);
  noFill();
  rect(2, 2, width - 4, height - 4);

  walkers.push(new Walker(width * 0.5, height * 0.5, "red"));
  walkers.push(new Walker(width * 0.25, height * 0.5, "blue"));
  walkers.push(new Walker(width * 0.75, height * 0.5, "yellow"));
}

function draw() {

  for(let walker of walkers) {
    walker.draw();
  }
}
