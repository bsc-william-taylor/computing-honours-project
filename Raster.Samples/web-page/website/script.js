
let shapes = null;

fetch('http://localhost:3010/shapes').then(function(response) {
  return response.json();
}).then(function(json) {
   shapes = json;
   console.log(shapes);
});

$("#save").click(function() {
    if(shapes != null) {
        var request = new Request('http://locahost:3010/shapes', {
            method: 'POST', 
            mode: 'cors',
            headers: new Headers({
                'Content-Type': 'application/json'
            }),
            body: JSON.stringify(shapes)
        });

        fetch(request).then(res => { 
            console.log(res) 
        }).catch(res => { 
            console.log(res) 
        });
    }
});

$("#pyramid-right").click(() => shapes.pyramid.translate.x += 1);
$("#pyramid-down").click(() => shapes.pyramid.translate.y -= 1);
$("#pyramid-left").click(() => shapes.pyramid.translate.x -= 1);
$("#pyramid-up").click(() => shapes.pyramid.translate.y += 1);
$("#pyramid-red").click(function() {
    shapes.pyramid.faces.forEach((face, index) => {
        shapes.pyramid.colours[index] = { r: 1.0, g: 0.0, b: 0.0};
    });
});

$("#pyramid-green").click(function() {
   shapes.pyramid.faces.forEach((face, index) => {
        shapes.pyramid.colours[index] = { r: 0.0, g: 1.0, b: 0.0};
    });
});

$("#pyramid-blue").click(function() {
  shapes.pyramid.faces.forEach((face, index) => {
        shapes.pyramid.colours[index] = { r: -.0, g: 0.0, b: 1.0};
    });
});

$("#pyramid-black").click(function() {
   shapes.pyramid.faces.forEach((face, index) => {
        shapes.pyramid.colours[index] = { 
            r: Math.random(), 
            g: Math.random(), 
            b: Math.random() };
    });
});


$("#cube-right").click(() => shapes.cube.translate.x += 1);
$("#cube-down").click(() => shapes.cube.translate.y -= 1);
$("#cube-left").click(() => shapes.cube.translate.x -= 1);
$("#cube-up").click(() => shapes.cube.translate.y += 1);
$("#cube-red").click(function() {
  shapes.cube.faces.forEach((face, index) => {
        shapes.cube.colours[index] = { r: 1.0, g: 0.0, b: 0.0};
    });
});

$("#cube-green").click(function() {
  shapes.cube.faces.forEach((face, index) => {
        shapes.cube.colours[index] = { r: 0.0, g: 1.0, b: 0.0};
    });
});

$("#cube-blue").click(function() {
  shapes.cube.faces.forEach((face, index) => {
        shapes.cube.colours[index] = { r: -.0, g: 0.0, b: 1.0};
    });
});

$("#cube-black").click(function() {
  shapes.cube.faces.forEach((face, index) => {
        shapes.cube.colours[index] = { 
            r: Math.random(), 
            g: Math.random(), 
            b: Math.random() };
    });
});