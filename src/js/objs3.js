function normalize() {
	console.log(this.coords.map(n => n/this.length));
}

normalize.call({coords:[0, 2, 3], length: 5});
