#version 330

out vec4 color;
in vec3 normal;

struct DirectionalLight 
{ 
   vec3 colour; 
   vec3 direction; 
   float ambient; 
}; 

void main()
{
  vec4 surfaceColour = vec4(1.0, 0.0, 0.0, 1.0);

  DirectionalLight sun; 
  sun.colour = vec3(1.0, 0.0, 0.0);
  sun.direction = normalize(vec3(-5.0, -1.0, 0.0));
  sun.ambient = 0.25;

  float diffuse = max(0.0, dot(normalize(normal), -sun.direction));
  color = surfaceColour * vec4(sun.colour * (sun.ambient + diffuse), 1.0);
}