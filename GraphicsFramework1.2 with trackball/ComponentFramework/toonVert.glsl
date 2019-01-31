#version 330
in  vec4 vVertex;
in  vec4 vNormal;
in  vec4 vColor;

out vec3 normal;
out vec3 lightDir;
out vec4 eyePos;

uniform mat4 projectionMatrix;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat3 normalMatrix;
uniform vec4 light_Pos;

void main() {
	normal = normalMatrix * vNormal.xyz; /// Rotate the normal to the correct orientation 
	eyePos = viewMatrix * modelMatrix * vVertex; /// Create the eye vector 
	lightDir = normalize(light_Pos.xyz - eyePos.xyz); /// Create the light direction
	gl_Position =  projectionMatrix * viewMatrix *modelMatrix * vVertex; 
}