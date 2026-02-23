let x = 200;
let dx = 2;
let w = 80;
let h = 40;

let r, g, b;
let dr, dg, db;

function setup() {
  createCanvas(400, 200);
  rectMode(CENTER);
  angleMode(DEGREES);

  r = random(255);
  g = random(255);
  b = random(255);

  dr = random(-5, 5);
  dg = random(-5, 5);
  db = random(-5, 5);
}

function draw() {
  background(100, 150, 250);

  
  translate(x, height / 2);
  scale(abs(2 * (x - width / 2) / width));
  rotate(abs(x));
  
  fill(r, g, b);
  rect(0, 0, w, h);
  
  x = x + dx;
  
  if(x > width - w / 2 || x < w / 2)
    dx = -dx;
    
   r = r + dr;
   if(r < 0 || r > 255)
        dr = -dr;
   g = g + dg;
   if(g < 0 || g > 255)
        dg = -dg;
   b = b + db;
   if(b < 0 || b > 255)
        db = -db;
}