class Walker {
    constructor() {
        this.x = width / 2;
        this.y = height / 2;
    }

    show() {
        stroke(floor(random(255)), floor(random(255)), floor(random(255)));
        point(this.x, this.y);
    }

    step() {
        // walker which tend to move right
        let r = random(1);

        // if( r < 0.4) {
        //     this.x += 1;
        // } else if (r < 0.6) {
        //     this.x -= 1;
        // } else if ( r < 0.8) {
        //     this.y += 1;
        // } else {
        //     this.y -= 1;
        // }
        let xstep = floor(random(3)) - 1;
        let ystep = floor(random(3)) - 1;

        if( mouseX > width / 2) {
            xstep = 1;
        } else {
            xstep = -1;
        }

        if(mouseY > height / 2) {
            ystep = 1;
        } else {
            ystep = -1;
        }
        this.x += xstep;
        this.y += ystep;

        // let choice = floor(random(4));
        // switch(choice) {
        //     case 0:
        //         this.x += 1;
        //         break;
        //     case 1:
        //         this.x -= 1;
        //         break;
        //     case 2:
        //         this.y += 1;
        //         break;
        //     case 3:
        //         this.y -= 1;
        //         break;
        // }
    }
}