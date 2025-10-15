
#version 440 core
uniform mat4 uProj;
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
out vec3 vColor;
void main() {
   vColor = aColor;
   gl_Position = uProj*vec4(aPos, 1.0);
}
