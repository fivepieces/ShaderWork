#include "Model.h"
#include <GL/glew.h>

namespace GAME {
	class SkyBox : public Model {
	private:
		const char * positive_x_image_;
		const char * negative_x_image_;
		const char * positive_y_image_;
		const char * negative_y_image_;
		const char * positive_z_image_;
		const char * negative_z_image_;
		class Shader *skyBoxShader;

		Model* Lake;
		GLuint textureID;
		GLuint texture;
		GLuint projectionMatrixID;
		GLuint modelViewMatrixID;
	public:
		SkyBox(const char * positive_x_image,
			const char * negative_x_image,
			const char * positive_y_image,
			const char * negative_y_image,
			const char * positive_z_image,
			const char * negative_z_image);
		virtual ~SkyBox();


		virtual bool OnCreate();
		virtual void Render(const Matrix4 & projectionMatrix, const Matrix4 & modelViewMatrix, const Matrix4 & normalMatrix) const;
		virtual void OnDestroy();
		virtual void Update(const float time);


	};
}