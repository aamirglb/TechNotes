function Cell(i, j) {
    this.i = i;
    this.j = j;
    // top, right, bottom, left
    this.walls = {
        "top"    : true,
        "right"  : true,
        "bottom" : true,
        "left"   : true,
    }
    this.visited = false;
    // this.walls = [true, true, true, true];

    this.checkNeighbors = () => {
        var neighbors = [];
        var top = grid[getIndex(i, j-1)];
        var right = grid[getIndex(i+1, j)];
        var bottom = grid[getIndex(i, j+1)];
        var left = grid[getIndex(i- 1, j)];

        if(top && !top.visited) {
            neighbors.push(top);
        }
        if(right && !right.visited) {
            neighbors.push(right);
        }
        if(bottom && !bottom.visited) {
            neighbors.push(bottom);
        }
        if(left && !left.visited) {
            neighbors.push(left);
        }

        if(neighbors.length > 0) {
            var r = floor(random(0, neighbors.length));
            return neighbors[r];
        } else {
            return undefined;
        }
    }

    this.highlight = () => {
        var x = this.i * w;
        var y = this.j * w;
        noStroke();
        fill(0, 255, 0, 100);
        rect(x, y, w, w);
    }

    this.show = () => {
        var x = this.i * w;
        var y = this.j * w;
        stroke(255);

    /*
    (x, y)          (x+w, y)
        *-----------*
        |           |
        |           |
        |           |
        *-----------*
    (x, y+w)        (x+w, y+w)
    */
        if(this.walls.top)
            line(x,   y,   x+w, y);

        if(this.walls.right)
            line(x+w, y,   x+w, y+w);

        if(this.walls.bottom)
            line(x+w, y+w, x,   y+w);

        if(this.walls.left)
            line(x,   y,   x,   y+w);


        if(this.visited) {
            noStroke();
            fill(255, 0, 255, 100);
            rect(x, y, w, w);
        }
        // noFill();

    }
}