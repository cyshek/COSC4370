#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
  // TODO: Your code here
  // Remember to set gl_Position (correctly) or you will get a black screen...
  // Pass the normal vector to the fragment shader
  Normal = normal;

  // Calculate the position of the vertex in screen coordinates
  gl_Position = projection * view * model * vec4(position, 0.99);

  // Calculate the position of the vertex in world coordinates
  FragPos = vec3(vec4(position, 0.99) * model);
} 
