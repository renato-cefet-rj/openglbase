#ifndef __SHADER_H__
#define __SHADER_H__

#include <App.hpp>

#define ShaderNull (Shader*)0

class Shader
{
	public:
		Shader(const char* programName);
		virtual ~Shader();
		virtual bool useProgram();
		virtual void setMVP(glm::mat4 mvp);

	private:
		GLuint compileShader(GLchar* src, GLenum shaderType);
		char* fileReadContents(const char* fileName);
		GLuint compileShaderFromFile(const char* fileName, GLenum shaderType);
		GLuint createProgram(const char* programName);

		GLuint programId;
};

#endif
