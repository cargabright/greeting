const greetModule = require('./build/Release/greet');

console.log("Exports: ", greetModule);
console.log();

console.log("greetModule.greetHello(): ", greetModule.greetHello("Luke"));
console.log();


