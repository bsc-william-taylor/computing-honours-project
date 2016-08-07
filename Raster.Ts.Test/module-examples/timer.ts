
import { setTimeout, setInterval, clearInterval } from 'time';
import * as console from 'console';

const ms = console.readNumber('Enter delay time: ');

setTimeout(() => {
    console.log(`Hi after ${ms} ms`);

    let intervals = console.readNumber('Enter a number: ');
    let timeID = setInterval(() => {
        if(intervals-- <= 0) {
            clearInterval(timeID);
        } else {
            console.log(`Interval Pass ${intervals+1}`);
        }
    }, 1000);
}, ms);
