const addon = require('./build/Release/module');
const value = 18;
const value1 = 4;

const year = 2018;
const month = 07;
const day = 22;
const UT = 0.0;
const lat = 42;
const lon = -84;
const tz = -4;

julian_date = addon.get_jd(year, month, day, UT);
console.log('jd: ', julian_date);

// console.log(
// 	`${value} times ${value1} equals`,
// 	addon.my_function(value, value1)
// );
//
// result = addon.get_mathed(3, 2, 5);
// console.log('RESULT: ', result);
