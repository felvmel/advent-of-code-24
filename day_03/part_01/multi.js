const fs = require('node:fs');

let text = fs.readFileSync('../input', 'utf8');

let exp = /mul\(\d{1,3},\d{1,3}\)/g;
let num = /(\d{1,3})/g;
let matches = [];

let match;
while (match = exp.exec(text)) {
    matches.push(match[0]);
}

let sum = 0;
let nr;
for (match of matches) {
    nr = match.match(num)
    sum += nr[0] * nr[1];
}

console.log(sum);