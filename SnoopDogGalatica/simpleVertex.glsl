/* 
SimpleVertex.glsl

Vertex shader with position, color, normal and ModelViewProject
input and color output.

Mike Barnes
8/17/2013
*/

# version 330 core

in vec4 vPosition;
in vec4 vColor;
in vec3 vNormal;  

out vec4 Position;
out vec3 Normal;
out vec4 Color;


uniform mat4 ModelViewProjection;  // = projection * view * model
uniform mat4 ModelViewMatrix;
mat3 NormalMatrix;

void main() {
  Color = vColor;
  gl_Position = ModelViewProjection * vPosition;
  Position = (ModelViewMatrix * vPosition);
  NormalMatrix = mat3(ModelViewMatrix);
  Normal = normalize(NormalMatrix * vNormal);

  }