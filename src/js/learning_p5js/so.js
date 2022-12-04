let started = false;
let worldSpacing = 10;
let offx = 0;
let offy = 0;
let worldcharacters = [];
let worldfill = [];
let characters = ["o", "o", "o", " ", "o", "o", " ", "o", "T", "o", "T"];
let worldcharsizes = [];

let worldBuffer;

function setup() {
  createCanvas(windowWidth, windowHeight);

  for (let i = 0; i < width * height; i++) {
    worldcharacters.push(characters[round(random(0, 8))]);

    if (worldcharacters[i] == "T") {
      worldfill.push("rgb(69,26,2)");
      worldcharsizes.push(11)
    } else {
      worldfill.push("rgb(0,106,0)");
      worldcharsizes.push(12.5)
    }
  }

  worldBuffer = createGraphics(width, height);
  drawWorld(worldBuffer);
}

function drawWorld(buffer) {
    for (let j = 0; j < (height / worldSpacing) * 2; j++) {
      for (let i = 0; i < (width / worldSpacing) * 2; i++) {
        buffer.fill(worldfill[i * j]);
        buffer.textSize(worldcharsizes[i * j]);
        buffer.text(
          worldcharacters[i * j],
          i * worldSpacing + offx,
          j * worldSpacing + offy
        );
      }
    }
  }

function draw() {
  background(0, 0, 30);


  if (mouseIsPressed) {
    started = true;
  }

  if (started) {
    image(worldBuffer, offx, offy);
  } else {
    fill("yellow");
    textSize(((width * 15) / height) * 2);
    text("Click To Start!", ((width * 15) / height) * 9, height / 2);
  }

  if (keyIsPressed) {
    if (key == "w") {
      offy += 1.5;
    }
    if (key == "s") {
      offy -= 1.5;
    }
    if (key == "a") {
      offx += 1.5;
    }
    if (key == "d") {
      offx -= 1.5;
    }
  }
}