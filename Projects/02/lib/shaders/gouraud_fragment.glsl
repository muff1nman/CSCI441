#version 420

out vec3 fragcolor;
noperspective in vec3 color;
void main() {
	fragcolor = color;
}
