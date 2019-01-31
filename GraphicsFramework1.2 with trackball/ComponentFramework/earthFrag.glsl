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
	
	//brown
	vec4 brown = vec4(0.5, 0.27, 0.07, 1.0);

	//gold
	vec4 gold = vec4(0.1, 0.1, 0.1, 1.0);


	
	fragColor = mix (brown, gold, noiseVec.x);

	//fragColor = vec4(1,0,0,0);
}