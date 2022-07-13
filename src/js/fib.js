// memoization
// Use js object

const fib = (n, memo = {}) => {
    if(n in memo) return memo[n];

    if(n <= 2) return 1;
    memo[n] = fib(n-1, memo) + fib(n-2, memo);
    return memo[n];
};

console.log(fib(6));
console.log(fib(7));
console.log(fib(8));
let memo = {};
console.log(fib(50, memo));
for(let key in memo) {
    console.log(key, ": ", memo[key]);
}
memo = {};
console.log(fib(150, memo));
for(let key in memo) {
    // console.log(key, ": ", memo[key]);
    console.log(key, ": ",
                memo[key].toLocaleString('fullwide', { useGrouping: false }),
                memo[key].toString(16)
                );
}
