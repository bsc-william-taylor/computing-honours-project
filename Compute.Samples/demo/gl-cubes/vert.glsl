#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 colour;
layout(location = 2) in vec2 uvs;

uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;

out vec2 uv;

void main()
{
  gl_Position = projection * view * model * vec4(position, 1.0);
  uv = uvs;
}
