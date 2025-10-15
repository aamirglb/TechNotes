let table;

function preload() {
    table = loadTable("color_web_safe.csv");
}

function setup() {
    let canvas = createCanvas(900, 900);
    canvas.parent("p5-container");

    for(let i = 1; i < table.getRowCount(); ++i) {
        let hexCode = table.get(i, 0);
        print(hexCode);
    }
}

function draw() {
    let r = 10;
    let c = 0;
    for(let i = 0; i < table.getRowCount(); ++i) {
        let hexCode = table.get(i, 0);
        stroke(0);
        fill(hexCode);
        rect(c*45, r, 40, 30);
        c += 1;
        if((c*45) >= width) {
            c = 0;
            r += 50;
        }
    }
    noLoop();
}