#version 420

out vec3 fragcolor;
smooth in vec3 color;
void main() {
	fragcolor = color;
}
