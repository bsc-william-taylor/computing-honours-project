
var Cpp = cpp;

exports.newRenderer = function (window) {
    var renderer = new Cpp.Renderer();
    renderer.initialise(window);
    return renderer;
}

exports.newTexture = function (renderer, image) {
    var texture = new Cpp.Texture();
    texture.create(renderer, image);
    return texture;
};