
#version 440 core
in vec3 vColor;
out vec4 FragColor;
void main() {
  vec3 color=vColor.grb;
   FragColor = vec4(color, 1.0);
}
