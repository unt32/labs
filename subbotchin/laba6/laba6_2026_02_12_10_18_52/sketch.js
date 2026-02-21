let particles = [];
let g;

function setup() {
  createCanvas(500, 500);
  g = createVector(0, 0.05);

  for (let i = 0; i < 200; i++) {
    particles.push(new Particle(random(width), random(height)));
  }
}

function draw() {
  background(20, 20, 50);

  for (let p of particles) {
    p.update();
  }

  for (let i = 0; i < particles.length; i++) {
    for (let j = i + 1; j < particles.length; j++) {
      checkCollision(particles[i], particles[j]);
    }
  }

  for (let p of particles) {
    p.draw();
  }

  fill(0);
  rect(0, 480, 140, 20);
  fill(255);
  text("Saenco Vladislav TI-256", 3, 495);
}

class Particle {
  constructor(x, y) {
    this.pos = createVector(x, y);
    this.vel = createVector(random(-3, 3), random(-3, 3));
    this.r = 6;
    this.d = 2 * this.r;
    this.col = color(random(100, 255), random(100, 255), random(100, 255));
  }

  update() {
    this.vel.add(g);
    this.pos.add(this.vel);

    if (this.pos.x - this.r < 0 || this.pos.x + this.r > width) {
      this.vel.x *= -1;

      if (this.pos.x < width / 2) this.pos.x = this.r;
      else this.pos.x = width - this.r;
    }

    if (this.pos.y - this.r < 0 || this.pos.y + this.r > height) {
      this.vel.y *= -1;

      if (this.pos.y < height / 2) this.pos.y = this.r;
      else this.pos.y = height - this.r;
    }
  }

  draw() {
    noStroke();
    fill(this.col);
    circle(this.pos.x, this.pos.y, this.d);
  }
}

function checkCollision(p1, p2) {
  let distance = p5.Vector.dist(p1.pos, p2.pos);
  let minDist = p1.r + p2.r;

  if (distance < minDist) {
    let normal = p5.Vector.sub(p2.pos, p1.pos).normalize();
    let relativeVelocity = p5.Vector.sub(p1.vel, p2.vel);
    let speed = relativeVelocity.dot(normal);

    if (speed < 0) return;

    let impulse = normal.copy().mult(speed);
    p1.vel.sub(impulse);
    p2.vel.add(impulse);

    let overlap = minDist - distance;
    let correction = normal.copy().mult(overlap / 2);
    p1.pos.sub(correction);
    p2.pos.add(correction);
  }
}
