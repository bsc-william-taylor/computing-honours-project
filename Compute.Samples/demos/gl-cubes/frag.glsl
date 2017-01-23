#version 330

uniform sampler2D sampler;

in vec2 uv;

out vec3 color;

void main()
{
  color = texture2D(sampler, uv).rgb;
}
