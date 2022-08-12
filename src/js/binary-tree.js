class Node {
    constructor(val) {
        this.val = val;
        this.left = null;
        this.right = null;
    }
}

const a = new Node('a');
const b = new Node('b');
const c = new Node('c');
const d = new Node('d');
const e = new Node('e');
const f = new Node('f');

a.left = b;            //           a
a.right = c;           //          / \
b.left = d;            //         b   c
b.right = e;           //        / \ / \
c.right = f;           //        d e   f


// Recursive solution
const depthFirstVal = (root) => {
    if(root === null) return [];
    const leftVals = depthFirstVal(root.left);
    const rightVals = depthFirstVal(root.right);
    return [ root.val, ...leftVals, ...rightVals]
}

// Iterative solution
const depthFirstValues = (root) => {
    if(root === null) return;
    const stack = [root];

    while(stack.length > 0) {
        const curr = stack.pop();
        console.log(curr.val);

        if(curr.right != null) stack.push(curr.right);
        if(curr.left != null) stack.push(curr.left);
    }
}

// Breath first search

// depthFirstValues(a);
console.log(depthFirstVal(a));



