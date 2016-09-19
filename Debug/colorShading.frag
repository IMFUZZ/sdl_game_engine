#version 130

in vec2 fragmentPosition;
in vec4 fragmentColor;

out vec4 color;

uniform float time;

void main() {
	color = vec4(fragmentColor.r * (cos(fragmentPosition.x*0.1 + time) + 1.0) * 0.5, 
				 fragmentColor.g * (cos(fragmentPosition.y*0.1 + time) + 1.0) * 0.5,
				 fragmentColor.b * (cos(fragmentPosition.x*0.1 + time) + 1.0) * 0.5,
				 fragmentColor.a);
}