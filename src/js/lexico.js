function swap(a, i, j) {
    var temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}
const lexico = (vals) => {

    while(true) {
    console.log(vals);

    // STEP 1 of the algorithm
    // https://www.quora.com/How-would-you-explain-an-algorithm-that-generates-permutations-using-lexicographic-ordering
    var largestI = -1;
    for (var i = 0; i < vals.length - 1; i++) {
        if (vals[i] < vals[i + 1]) {
        largestI = i;
        }
    }
    if (largestI == -1) {
        console.log('finished');
        return;
    }

    // STEP 2
    var largestJ = -1;
    for (var j = 0; j < vals.length; j++) {
        if (vals[largestI] < vals[j]) {
        largestJ = j;
        }
    }

    // STEP 3
    swap(vals, largestI, largestJ);

    // STEP 4: reverse from largestI + 1 to the end
    var endArray = vals.splice(largestI + 1);
    endArray.reverse();
    vals = vals.concat(endArray);
}
}

lexico([0, 1, 2]);

