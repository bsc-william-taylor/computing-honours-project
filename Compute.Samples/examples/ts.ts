let bool: boolean = false;
let word: string = "HelloWorld";
let num: number = 100

// Type annotations for both parameter and return type
function timesTen(value: number) : number {
    return value * 10;
}

timesTen(num);   // Fine
timesTen(word);  // Compile error 
timesTen(bool);  // Compile error
