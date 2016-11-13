#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 colour;

uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;

out vec3 inputColor;

void main()
{
  gl_Position = projection * view * model * vec4(position, 1.0);
  inputColor = colour;
}
