let socket;

function setup() {
    createCanvas(800, 800);
    background(51);

    socket = io.connect('http://localhost:4434');
    socket.on('mouse', newDrawing);
}

function newDrawing(data) {
    noStroke();
    fill(255, 0, 100);
    ellipse(data.x, data.y, 18, 18);
}
function mouseDragged() {
    console.log(mouseX + '. ' + mouseY);
    noStroke();
    fill(255);
    ellipse(mouseX, mouseY, 18, 18);

    const data = {
        x: mouseX,
        y: mouseY
    }
    socket.emit('mouse', data);
}

function draw() {
}