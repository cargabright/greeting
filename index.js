const greetModule = require('./build/Release/greet');

console.log("Exports: ", greetModule);
console.log();

console.log("greetModule.showChassis(): ", greetModule.showChassis());
console.log();


console.log("greetModule.showChassis(): ", greetModule.dontShowChassis());
console.log();


