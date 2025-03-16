
let var1 = "I'm global variable";

function outerFunction() {
    let var2 = "I'm in outside function";

    function innerFunction() {
        let var3 = "I'm in inside function";
        console.log(var3);   // Accessible here
        console.log(var2);   // Accessible due to closure
        console.log(var1);  // Accessible (global scope)
    }

    innerFunction();
    // console.log(var3); // Error: var3 is not accessible here
}

outerFunction();