#version 420

out vec3 fragcolor;
flat in vec3 color;
void main() {
	fragcolor = color;
}
