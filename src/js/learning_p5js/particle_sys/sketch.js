let emitters = [];

function mousePressed() {
    emitters.push(new Emitter(mouseX, mouseY));
}

function setup() {
    createCanvas(800, 800);
    emitters[0] = new Emitter(200, 20);

    // particles.push(new Particle(200, 200))
    // for(let i = 0; i < 100; ++i) {
    //     particles[i] = new Particle(width/2, 20);
    // }
}

function draw() {
    background(0);
    for(let emitter of emitters) {
        emitter.emit(5);
        emitter.show();
        emitter.update();
    }
    // for(let i = 0; i < 5; ++i) {
    //     particles.push(new Particle(200, 20));
    // }

}