class Rabbit {
	constructor(type) {
		this.type = type;
	}

	speak(line) {
		console.log(`The ${this.type} rabbit says '${line}'`);
	}
}

let killerRabbit = new Rabbit("killer");
let blackRabbit = new Rabbit("black");

killerRabbit.speak("i am killer rabbit");
blackRabbit.speak("i am black rabbit");

class Matrix {
	constructor(width, height, element = (x, y) => undefined) {
		this.width = width;
		this.height = height;
		this.content = [];

		for(let y = 0; y < height; y++) {
			for(let x = 0; x < width; x++) {
				this.content[y* width + x] = element(x, y);
			}
		}
	}

	get(x, y) {
		return this.content[y * this.width + x];
	}

	set(x, y, value) {
		this.content[y*this.width+x] = value
	}
}

class MatrixIterator {
	constructor(matrix) {
		this.x = 0;
		this.y = 0;
		this.matrix = matrix;
	}

	next() {
		if(this.y == this.matrix.height) return {done: true};
		let value = {x: this.x,
			y: this.y,
			value: this.matrix.get(this.x, this.y)
		};
		this.x++;
		if(this.x == this.matrix.width) {
			this.x = 0;
			this.y++;
		}
		return { value, done:false};
	}
}

Matrix.prototype[Symbol.iterator] = function() {
	return new MatrixIterator(this);
};

let matrix = new Matrix(4, 4, (x, y) => `value ${x},${y}`);
for(let {x, y, value} of matrix) {
	console.log(x, y, value);
}
