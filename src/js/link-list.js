class Node {
    constructor(val) {
        this.val = val;
        this.next = null;
    }
}

const printLinkList = (head) => {
    let curr = head;
    while(curr != null) {
        console.log(curr.val);
        curr = curr.next;
    }
}

const printRecursive = (head) => {
    if(head === null) return;
    console.log(head.val);
    printRecursive(head.next);
}

const a = new Node('A');
const b = new Node('B');
const c = new Node('C');
const d = new Node('D');

a.next = b;
b.next = c;
c.next = d;

// printLinkList(a);
printRecursive(a);