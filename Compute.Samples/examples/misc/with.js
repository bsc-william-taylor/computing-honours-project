const point = {
    x: 100,
    y: 200
};

with (point) {
    console.log('X: ' + x); // x, y are now available
    console.log('Y: ' + Y);
}
