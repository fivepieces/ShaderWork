#version 330
in  vec4 vVertex;
in  vec4 vNormal;

out vec3 eyeDir;
out vec3 vertNormal;
out vec3 lightDir;
out vec3 noiseVec;

uniform mat4 projectionMatrix;
uniform float elapsedTime;
uniform sampler3D noiseTexture;

// Camera
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;

uniform mat3 normalMatrix;
uniform vec3 lightPos;


void main() {

	vertNormal = normalMatrix * vNormal.xyz; /// Rotate the normal to the correct orientation 
	eyeDir = normalize(vec3(viewMatrix * modelMatrix * vVertex)); /// Create the eye vector 
	lightDir = normalize(lightPos - eyeDir.xyz); /// Create the light direction 

	noiseVec = normalize(vec3(texture(noiseTexture, vNormal.xyz + elapsedTime * 0.3)));
	vec3 offset = vNormal.xyz * dot(vertNormal, noiseVec) * 1.15;

	gl_Position = projectionMatrix * viewMatrix * modelMatrix * (vVertex*7.5 + (vec4(offset, 1.0)));
}


