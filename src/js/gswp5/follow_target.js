let startX = 20, stopX = 160;
let startY = 30, stopY = 80;

let x = 10, y = 10;
let step = 0.005;
let pct = 0.0;

let targetPos = false;
let targets = [];
let currTarget = null;
let targetColors = ["red", "maroon", "purple", "fuchsia", "green", "lime", "yellow", "blue","teal", "aqua"];
let colorIdx = 0;
let numOfSteps = 0;

function setup() {
  canvas = createCanvas(800, 800);
  canvas.parent('p5-container');
  textFont("Open Sans");
}

function mouseClicked() {
  // let colr = targetColors[Math.floor(Math.random() * targetColors.length)];
  let colr = targetColors[colorIdx % targetColors.length];
  colorIdx += 1;
  targets.push({x: mouseX, y: mouseY, color: colr});
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
    
    if( d > 6 ) {
      if(pct < 1.0) {
        numOfSteps += 1;
        x = startX + ((stopX - startX) * pct);
        y = startY + ((stopY - startY) * pct);
        pct += step;
      }
      
      // console.log("d = ", d, " pct = ", pct, "x-delta = ", (stopX - startX) * pct);
    } else {
       const t = document.getElementById('text-container');
       const p = document.createElement('p');
       p.innerHTML = `no of steps to reach target: ${numOfSteps}`;
       t.appendChild(p);

      // remove the current target
      currTarget = null;
      targets.shift();
      pct = 0.0;
      numOfSteps = 0;
    }
    
  }
  
  noStroke();
  fill(255);
  ellipse(x, y, 20, 20);
  
  for(let target of targets) {
    noStroke();
    fill(target.color);
    circle(target.x, target.y, 10);
  }

  noStroke();
  fill("white");
  text("Targets: ", 5, height - 30);

  let idx = 0;
  for(let target of targets) {
    fill(target.color);
    let x = 50 + (idx * 20) + 20; 
    circle(x, height - 35, 10);
    idx += 1;
  }

  noStroke();
  fill("white");
  text(`Pending Targets: ${targets.length}`, 5, height - 10);
}