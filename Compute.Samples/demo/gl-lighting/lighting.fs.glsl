#version 330

out vec4 colour;

in vec3 normal;

struct DirectionalLight 
{ 
   vec3 colour; 
   vec3 direction; 
   float ambient; 
}; 

void main()
{
  DirectionalLight sun; 
  sun.direction = normalize(vec3(-5.0, -1.0, 0.0));
  sun.colour = vec3(1.0, 0.0, 0.0);
  sun.ambient = 0.25;

  float diffuse = max(0.0, dot(normalize(normal), -sun.direction));
  colour = vec4(1.0, 0.0, 0.0, 1.0) * vec4(sun.colour * (sun.ambient + diffuse), 1.0);
}