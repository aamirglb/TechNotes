class Walker {
    constructor() {
        this.tx = 0;
        this.ty = 10000;
        this.x = width / 2;
        this.y = height / 2;
    }

    show() {
        strokeWeight(2);
        fill(127);
        stroke(0);
        circle(this.x, this.y, 40);
    }

    step() {
        let xstep_size = map(noise(this.tx), 0, 1, -2, 2);
        let ystep_size = map(noise(this.ty), 0, 1, -2, 2);

        this.x += xstep_size;
        this.y += ystep_size;

        // if( this.x < 0 ) this.x = 0;
        // if( this.x > width) this.x = 0;
        // if( this.y < 0 ) this.y = 0;
        // if(this.y > height) this.y = 0;
        // this.x = map(noise(this.tx), 0, 1, 0, width);
        // this.y = map(noise(this.ty), 0, 1, 0, height);

        this.tx += 0.01;
        this.ty += 0.01;
    }
}