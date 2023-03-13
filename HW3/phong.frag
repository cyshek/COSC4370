#version 330 core
out vec4 color;

in vec3 FragPos;  
in vec3 Normal;  
  
uniform vec3 lightPos; 
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform vec3 objectColor;

// TODO: Replace with your code...

// Compute the diffuse component of the lighting equation for a given fragment
vec3 Diffuse() {
  // Declare variables for the direction of the light and the surface normal
  vec3 dir_light, nm;
  // Declare a variable to hold the amount of diffusion
  float diffusion;
  // Normalize the surface normal to get a unit vector
  nm = normalize(Normal);
  // Normalize the direction of the light to get a unit vector
  dir_light = normalize(lightPos - FragPos);
  // Compute the amount of diffusion based on the dot product of the surface normal and the light direction,
  diffusion = max(dot(nm, dir_light), 0.1);
  // Multiply the light color by the amount of diffusion to get the final diffuse component
  return lightColor * diffusion;
}

// Compute the specular component of the lighting equation for a given fragment
vec3 Specular() {
  // Declare variables for the surface normal, direction of the light, view direction,
  // reflected light direction, glossiness, and specular intensity
  vec3 nm, dir_light, view, dir_reflect;
  int glossiness = 41;
  float sp;
  // Normalize the surface normal to get a unit vector
  nm = normalize(Normal);
  // Normalize the direction of the light to get a unit vector
  dir_light = normalize(lightPos - FragPos);
  // Normalize the view direction to get a unit vector
  view = normalize(view - FragPos);
  // Compute the reflected light direction based on the surface normal and direction of the light
  dir_reflect = reflect(-dir_light, nm);
  // Compute the specular intensity based on the dot product of the view direction and
  // reflected light direction, raised to the power of the glossiness value
  sp = pow(max(dot(view, dir_reflect), 0.0), glossiness);
  // Multiply the specular intensity by a constant value and the light color to get the
  // final specular component of the lighting equation
  return sp * 0.61 * lightColor;
}

void main() {
  vec3 spec, diff, rgb;
  //I used 0.13 as a small constant ambient factor
  vec3 ambient  = (0.13 * lightColor) * objectColor;
	spec = Specular();
  diff = Diffuse();
	rgb = (diff + spec + ambient) * objectColor;
	color = vec4(rgb, 1.0);
} 