#version 330

in  vec3 eyeDir;
in  vec3 vertNormal;
in  vec3 lightDir;

out vec4 fragColor;
uniform samplerCube cubeTexture; 


uniform mat4 modelMatrix; 
uniform mat4 viewMatrix;


void main() { 
mat3 scale = mat3(vec3(-1.0,0.0,0.0),
					  vec3(0.0,1.0,0.0),
					  vec3(0.0,0.0,1.0));
	vec3 reflection = reflect(eyeDir, vertNormal);
	vec3 refraction = refract (eyeDir, vertNormal, 1.0/1.6);
	reflection = vec3 (inverse (viewMatrix * modelMatrix) * vec4 (reflection, 0.0));
	refraction = vec3 (inverse (viewMatrix * modelMatrix) * vec4 (refraction, 0.0));
	fragColor =  texture(cubeTexture, scale * refraction);
	//fragColor =  mix(texture(cubeTexture, scale * refraction),vec4(0,0.2,0.2,0), noiseVec.x) ;

	//fragColor = vec4(1,0,0,0);
}
