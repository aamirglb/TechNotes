const howSum = (targetSum, numbers, memo={}) => {
    if(targetSum in memo) return memo[targetSum];

    if(targetSum === 0) return [];
    if(targetSum < 0) return null;

    for(let num of numbers) {
        const reminder = targetSum - num;
        const result = howSum(reminder, numbers, memo);
        if(result !== null) {
            memo[targetSum] = [...result, num]; // use spread operator
            return memo[targetSum];
        }
    }

    memo[targetSum] = null;
    return null;
};

let memo = {};
// console.log(howSum(7, [2, 3]));
// console.log(howSum(7, [5, 3, 4, 7]));
// console.log(howSum(7, [2, 4]));
console.log(howSum(8, [2, 3, 5], memo));
// console.log(howSum(300, [7, 14], memo));
for(let key in memo) {
    console.log(key, memo[key]);
}