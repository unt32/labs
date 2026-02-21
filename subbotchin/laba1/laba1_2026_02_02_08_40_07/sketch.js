function setup() {
  createCanvas(400, 400);
  background(0, 200, 200);
  
  //ground
  noStroke();
  fill(0, 170, 0);
  rect(0, 200, 400, 200);

  //head
  stroke(0);
  fill(160, 110, 70);
  ellipse(200, 200, 220, 200);

  //ears
  circle(130, 120, 70);
  circle(270, 120, 70);

  //eyes
  fill(0);
  ellipse(170, 190, 15);
  ellipse(230, 190, 15);

  //nose
  fill(80, 50, 30);
  ellipse(200, 230, 30, 20);

  //mouth
  noFill();
  arc(200, 250, 40, 30, 0, PI);
  
  //hat
  fill(200, 0, 0);
  triangle(170, 105, 230, 105, 200, 30);
  
  fill(255);
  text("Saenco Vladislav TI-256", 5, 395);
}
