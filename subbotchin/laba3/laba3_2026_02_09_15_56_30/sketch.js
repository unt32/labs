let x = 200;
let dx = 2;
let w = 80;
let h = 40;

function setup() {
  createCanvas(400, 200);
  rectMode(CENTER);
  angleMode(DEGREES);
}

function draw() {
  background(100, 150, 250);

  
  translate(x, height / 2);
  scale(abs(2 * (x - width / 2) / width));
  rotate(abs(x));
  
  fill(250, 0, 150);
  rect(0, 0, w, h);
  
  x = x + dx;
  
  if(x > width - w / 2 || x < w / 2)
    dx = -dx;
}