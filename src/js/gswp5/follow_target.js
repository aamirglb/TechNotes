let startX = 20, stopX = 160;
let startY = 30, stopY = 80;

// let x = startX, y = startY;
let x = 0, y = 0;
let step = 0.005;
let pct = 0.0;

let targetPos = false;
let targets = [];
let currTarget = null;

function setup() {
  createCanvas(600, 600);
}

function mouseClicked() {
  targets.push({x: mouseX, y: mouseY});
}
function draw() {
  background(0);
  
  if(currTarget == null && targets.length > 0) {
    currTarget = targets[0];
    startX = x;
    startY = y;
    console.log("target: ", currTarget);
  }
  
  if(targets.length > 0) {
    stopX = currTarget.x;
    stopY = currTarget.y;
    let d = Math.abs(dist(stopX, stopY, x, y));
    
    if( d > 5) {
      // higher the distance, higher the step
      // step = map(d, 0, 800, 0.005, 0.005*5);
      if(pct < 1.0) {
        x = startX + ((stopX - startX) * pct);
        y = startY + ((stopY - startY) * pct);
        pct += step;
      }
      
      // console.log("x=",x,"y=",y);
      // console.log("d = ", d, " pct = ", pct, "x-delta = ", (stopX - startX) * pct);
      // console.log(x, y);
    } else {
      // remove the current target
      currTarget = null;
      targets.shift();
      pct = 0.0;
    }
    
  }
  
  noStroke();
  fill(255);
  ellipse(x, y, 20, 20);
  
  // let d = Math.abs(dist(stopX, stopY, x, y));
  // step = map(d, 0, 800, 0.005, 0.005*5);
  // // console.log(d, " - ", step);
  // if(pct < 1.0) {
  // // if(true) {
  //   x = startX + ((stopX - startX) * pct);
  //   y = startY + ((stopY - startY) * pct);
  //   pct += step;
  // }
  // noStroke();
  // fill(255);
  // ellipse(x, y, 20, 20);
  
  for(let target of targets) {
    noStroke();
    fill(255, 0, 0);
    circle(target.x, target.y, 10);
  }
  // if(targetPos) {
  //   noStroke();
  //   fill(255, 0, 0);
  //   circle(stopX, stopY, 10);
  // }
}