var cells = [];

function setup() {
    createCanvas(800, 800);
    cells.push(new Cell());
}

function draw() {
    background(200);
    for(let i = 0; i < cells.length; ++i) {
        cells[i].move();
        cells[i].show();
    }
}

function mousePressed() {
    for(let i = cells.length - 1; i >= 0; --i) {
        if(cells[i].clicked(mouseX, mouseY)) {
            cells.push(cells[i].mitosis());
            cells.push(cells[i].mitosis());
            cells.splice(i, 1);
            // console.log("Clicked");
        }
    }
}