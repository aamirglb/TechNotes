document.getElementById("hdr").innerHTML = "Hello DOM";
let s = document.getElementById("hdr");
s.setAttribute("rotation", 45);
document.getElementsByClassName("cls")[0].innerHTML = "New Paragraph-1";
document.getElementsByClassName("cls")[1].innerHTML = "New Paragraph-2";
document.getElementById("hdr").onclick = function() { alert("Welcome to Simple HTML page"); }

const button1 = document.createElement("button");
button1.innerText = "Create Triangle";
button1.onclick = () => {
	document.getElementsByClassName("cls")[0].innerHTML = createTriangle();
};
document.body.appendChild(button1);

const button2 = document.createElement("button");
button2.innerText = "Fizz Buzz";
button2.onclick = () => {
	document.getElementsByClassName("cls")[1].innerHTML = fizzBuzz();
};
document.body.appendChild(button2);

const button3 = document.createElement("button");
button3.innerText = "Chessboard";
button3.onclick = () => {
	document.getElementsByClassName("cls")[2].innerHTML = chessBoard();
	//const para = document.createElement("p");
	//const node = document.createTextNode(chessBoard());
	//para.appendChild(node);
	//document.body.appendChild(para);
	//const element = document.getElementById("hdr");
	//element.appendChild(para)
};
document.body.appendChild(button3);

const button4 = document.createElement("button");
button4.innerText = "Canvas"
button4.onclick = () => {
	let cx = document.querySelector("canvas").getContext("2d");
	cx.strokeStyle = "blue";
	cx.strokeRect(5, 5, 50, 50);
	cx.lineWidth = 5;
	cx.strokeRect(135, 5, 50, 50);
};
document.body.appendChild(button4);
//for (let i = 0; i < 2; i++) {
//  const button = document.createElement("button");
//  button.innerText = 'Button ' + i;
//  button.onclick = () => {
//	  document.getElementsByClassName("cls")[0].innerHTML = createTriangle();
//  };
//  document.body.appendChild(button);
//}

function createTriangle() {
	let triangle = "";
	for(let i = 0; i < 7; ++i) {
		let tmp = "";
		for(let j = 0; j <= i; ++j) {
			tmp += "#";
		}
		triangle += tmp;
		triangle += "<br/>";
	}
	return triangle;
}

function fizzBuzz() {
	let out = "";
	for(let i = 1; i<=100; ++i) {
		if( (i%3 == 0) && (i%5==0)) {
			out += "FizzBuzz";
		}
		else if( i % 3 == 0) {
			out += "Fizz";
		} else if(i % 5 == 0) {
			out += "Buzz";
		} else {
			out += i.toString();
		}
		if(i % 10 == 0) {
			out += "<br/>";
		} else {
			out += "\t";
		}
	}
	return out;
}

function chessBoard() {
	let board = "";
	let chars = [" . ", " # "];
	for(let i = 1; i <= 8; i++) {
		for(let j = 1; j <=8; ++j) {
			board += chars[j%2];
		}
		board += "<br/>"
		if(i%2==0) {
			chars = [" . ", " # "];
		} else {
			chars = [" # ", " . "];
		}
	}
	return board;
}

