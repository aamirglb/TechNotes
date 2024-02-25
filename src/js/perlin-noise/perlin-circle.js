let x;
let y;
let r = 50;
let a;
let noiseScale = 0.008;
let noiseAmount = 40;
let rep;
let xs = [];
let ys = [];
let fr;

function setup() {
  createCanvas(800, 650);
//   noLoop();
  background(0);
  randomSeed(500000);
    
    fr = createP('');
}

function draw() {
  stroke(255);
  fill(0);
  strokeWeight(1);

  r += 2;
  if( r >= 300) noLoop();
  rep += 1;
//   if(rep == 100) noLoop();

  //begin recording vertices for a shape.
//   beginShape();
  
//   for (rep=0; rep<100; rep++) {
    // r+=2;
    noiseScale+=0.00005;
    
    for (a=0; a < TWO_PI; a += 0.01) {
      x=r*cos(a);
      y=r*sin(a);
      
      x += map(noise(noiseScale*x+100000, noiseScale*y+100000, 0), 0, 1, -noiseAmount, noiseAmount);
      y += map(noise(noiseScale*x+100000, noiseScale*y+100000, 1), 0, 1, -noiseAmount, noiseAmount);

      //specify coordinates for the vertices.
    //   vertex(x, y);
    xs.push(x);
    ys.push(y);
    // }
  }

    beginShape();
  for(let i = 0; i < xs.length; ++i) {
    vertex(xs[i], ys[i]);
  }

    translate(width/2, height/2);
    endShape();

    fr.html(floor(frameRate()));
//   translate(width/2, height/2);
  //end recording vertices for a shape.
//   endShape();
}


/*
void setup() {
  size(600, 600);
  pixelDensity(displayDensity());
  noLoop();
  //randomSeed(10);
}

float x;
float y;
//declare radius variable and assign a value to it.
float r=50;
//declare angle variable.
float a;
float noiseScale = .008, noiseAmount=40;
//declare variable controlling the number of circles being drawn.
float rep;

void draw() {
  background(0);
  stroke(255);
  fill(0);
  strokeWeight(1);
  randomSeed(500000);

  //begin recording vertices for a shape.
  beginShape();
  //loop allowing the generation of rings, specifying their quantity, consecutive increase in radius & in "noiseScale".
  for (rep=0; rep<100; rep++) {
    r+=2;
    noiseScale+=0.00005;
    
    
    //loop increment must be adequately small so that the shape is closed.
    for (a=0; a<TWO_PI; a+=0.01) {
      //translation from polar to cartesian coordinates. could also be "x = width/2 + r*cos(a)" instead of a translation before "endShape" to centre the image.
      x=r*cos(a);
      //apply perlin noise to x-coordinate. a large number is added to avoid noise generating symmetrical patterns (it does so as perlin noise is mirrored around 0.
      x += map(noise(noiseScale*x+100000, noiseScale*y+100000, 0), 0, 1, -noiseAmount, noiseAmount);
      //translation from polar to cartesian coordinates. could also be "y = height/2 + r*sin(a)" instead of a translation before "endShape" to centre the image.
      y=r*sin(a);
      //apply perlin noise to y-coordinate. a large number is added to avoid noise generating symmetrical patterns (it does so as perlin noise is mirrored around 0.
      y += map(noise(noiseScale*x+100000, noiseScale*y+100000, 1), 0, 1, -noiseAmount, noiseAmount);
      //specify coordinates for the vertices.
      vertex(x, y);
    }
  }

  translate(width/2, height/2);
  //end recording vertices for a shape.
  endShape();
  
  save("perlin_test.jpg");
}
*/