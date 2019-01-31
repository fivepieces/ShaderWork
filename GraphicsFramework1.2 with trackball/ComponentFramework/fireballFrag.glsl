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
	
	//red
	vec4 red = vec4(1.0, 0.0, 0.0, 1.0);

	//orange
	vec4 orange = vec4(1.0, 0.70, 0.0, 1.0);


	
	fragColor = mix (red, orange, noiseVec.x);

	//fragColor = vec4(1,0,0,0);
}

