layout(location = 0) in vec3 positions;
layout(location = 1) in vec3 uvs;

uniform mat4 projection;
uniform mat4 model;
out vec2 uv_cords;

void main() {
    vec2 position2D = (projection * model * vec4(positions, 1.0)).xy;
    gl_Position = vec4(position2D, 0.0, 1.0);
    uv_cords = uvs.xy;
}
