function make2DArray(cols, rows) {
    let arr = new Array(cols);
    for(let i = 0; i < arr.length; ++i) {
        arr[i] = new Array(rows);
    }
    return arr;
}

class Terrain {
    constructor(scl, w, h) {
        this.scl = scl;
        this.w = w;
        this.h = h;

        this.cols = floor(w/scl);
        this.rows = floor(h/scl);

        this.z = make2DArray(this.cols, this.rows);
        this.zoff = 0;
    }

    calculate() {
        let xoff = 0;
        for(let i = 0; i < this.cols; ++i) {
            let yoff = 0;
            for(let j = 0; j < this.rows; ++j) {
                this.z[i][j] = map(noise(xoff, yoff, this.zoff), 0, 1, -120, 120);
                yoff += 0.1;
            }
            xoff += 0.1;
        }
        this.zoff += 0.01;
    }

    render() {
        for(let x = 0; x < this.z.length - 1; x++) {
            beginShape(QUAD_STRIP);

            for(let y = 0; y < this.z[x].length; ++y) {
                stroke(0);
                let currentElevation = this.z[x][y];
                let currentShade = map(currentElevation, -120, 120, 0, 255);
                fill(currentShade, 255);

                let xCoordinate = x*this.scl - this.w/2;
                let yCoordinate = y*this.scl - this.h/2;

                vertex(xCoordinate, yCoordinate, this.z[x][y]);
                vertex(xCoordinate + this.scl, yCoordinate, this.z[x+1][y]);
            }
            endShape();
        }
    }
}