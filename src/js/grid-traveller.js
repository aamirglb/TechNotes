const gridTraveler = (m, n, route, memo = {}) => {
    const key = m + "," + n;

    if(key in memo) return memo[key];
    if(m === 0 || n === 0) {
        // console.log(route);
        return 0;
    }
    if(m === 1 && n === 1) {
        console.log(route);
        return 1;
    }

    memo[key] = gridTraveler(m-1, n, route + " down", memo) + gridTraveler(m, n-1, route + " right", memo);
    return memo[key];
};

// console.log(gridTraveler(1, 1));
// console.log(gridTraveler(2, 3));
// console.log(gridTraveler(3, 2));
let memo = {};
let route = "";
console.log(gridTraveler(2, 3, route, memo));
for(key in memo) {
    console.log(key, ": ", memo[key]);
}
// console.log(gridTraveler(18, 18));

