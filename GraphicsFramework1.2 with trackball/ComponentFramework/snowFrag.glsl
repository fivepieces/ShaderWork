 #version 330

in vec3 eyeDir;
in vec3 vertNormal;
in vec3 lightDir;
in vec3 noiseVec;

out vec4 fragColor;
uniform samplerCube cubeTexture; 
uniform float elapsedTime;

uniform mat4 modelMatrix; 
uniform mat4 viewMatrix;


void main() { 
	
	//blue 
	vec4 blue = vec4(0.0, 0.0, 1.0, 1.0);

	//white
	vec4 white = vec4(1.0, 1.0, 1.0, 1.0);

	
	fragColor = mix (blue, white, noiseVec.x);

	//fragColor = vec4(1,0,0,0);
}