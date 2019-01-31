#include <GL/glew.h>
#include <SDL.h>
#include <SDL_image.h>
#include "shader.h"
#include "Skybox.h"
#include "ObjLoader.h"

using namespace GAME;

SkyBox::SkyBox(const char * positive_x_image, const char * negative_x_image, const char * positive_y_image, const char * negative_y_image, const char * positive_z_image, const char * negative_z_image)
{
	positive_x_image_ = positive_x_image;
	negative_x_image_ = negative_x_image;
	positive_y_image_ = positive_y_image;
	negative_y_image_ = negative_y_image;
	positive_z_image_ = positive_z_image;
	negative_z_image_ = negative_z_image;

}

SkyBox::~SkyBox()
{
}

bool SkyBox::OnCreate() {

	Lake = new Model(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
	Lake->OnCreateLake();

	Lake->setPos(Vec3(0.0f, -10.0f, 0.0f));



	if (Lake->LoadMesh("Lake.obj") == false) {
		return false;
	}


	ObjLoader obj;
	if (obj.loadOBJ("cube.obj") == false) {
		return false;
	}
		
	meshes.push_back(new Mesh(GL_TRIANGLES, obj.vertices, obj.normals, obj.uvCoords));

	SDL_Surface *textureSurface;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
	/// Wrapping and filtering options
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	textureSurface = IMG_Load(positive_x_image_);
	if (textureSurface == nullptr) return false;
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, textureSurface->w, textureSurface->h,
		0, GL_RGB, GL_UNSIGNED_BYTE, textureSurface->pixels);
	SDL_FreeSurface(textureSurface);
	textureSurface = nullptr;

	textureSurface = IMG_Load(negative_x_image_);
	if (textureSurface == nullptr) return false;
	///mode = (textureSurface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, textureSurface->w, textureSurface->h,
		0, GL_RGB, GL_UNSIGNED_BYTE, textureSurface->pixels);
	SDL_FreeSurface(textureSurface);
	textureSurface = nullptr;


	textureSurface = IMG_Load(positive_y_image_);
	if (textureSurface == nullptr) return false;
	///mode = (textureSurface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, textureSurface->w, textureSurface->h,
		0, GL_RGB, GL_UNSIGNED_BYTE, textureSurface->pixels);
	SDL_FreeSurface(textureSurface);
	textureSurface = nullptr;

	textureSurface = IMG_Load(negative_y_image_);
	if (textureSurface == nullptr) return false;
	///mode = (textureSurface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, textureSurface->w, textureSurface->h,
		0, GL_RGB, GL_UNSIGNED_BYTE, textureSurface->pixels);
	SDL_FreeSurface(textureSurface);
	textureSurface = nullptr;


	textureSurface = IMG_Load(positive_z_image_);
	if (textureSurface == nullptr) return false;
	///mode = (textureSurface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, textureSurface->w, textureSurface->h,
		0, GL_RGB, GL_UNSIGNED_BYTE, textureSurface->pixels);
	SDL_FreeSurface(textureSurface);
	textureSurface = nullptr;


	textureSurface = IMG_Load(negative_z_image_);
	if (textureSurface == nullptr) return false;
	///mode = (textureSurface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, textureSurface->w, textureSurface->h,
		0, GL_RGB, GL_UNSIGNED_BYTE, textureSurface->pixels);
	SDL_FreeSurface(textureSurface);
	textureSurface = nullptr;



	skyBoxShader = new Shader("skyboxVert.glsl", "skyboxFrag.glsl", 1, 0, "vVertex");
	projectionMatrixID = glGetUniformLocation(skyBoxShader->getProgram(), "projectionMatrix");
	/// You may prefer to send the view and model matrices separately 
	modelViewMatrixID = glGetUniformLocation(skyBoxShader->getProgram(), "modelViewMatrix");
	textureID = glGetUniformLocation(skyBoxShader->getProgram(), "cubeTexture");
	return true;
}

void SkyBox::Render(const Matrix4& projectionMatrix, const Matrix4& modelViewMatrix, const Matrix4& normalMatrix) const
{


	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glUseProgram(skyBoxShader->getProgram());
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
	glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, projectionMatrix);
	glUniformMatrix4fv(modelViewMatrixID, 1, GL_FALSE, modelViewMatrix*MMath::scale(20.0f,20.0f,20.0f));
	for (Mesh* mesh : meshes)
		mesh->Render();

	Lake->Render();
	glEnableVertexAttribArray(0);
}

void GAME::SkyBox::OnDestroy()
{

}

void GAME::SkyBox::Update(const float time)
{

	Lake->Update(time);
}
