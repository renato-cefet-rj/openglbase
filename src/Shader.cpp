#include <Shader.hpp>

Shader::Shader(const char* programName)
{
	this->programId = this->createProgram(programName);
	if(this->programId)
	{
		this->useProgram();
		// this->setMVP(projection*view*model);
		SDL_Log("Shader %s carregado com sucesso",programName);
	}
}

Shader::~Shader()
{
	if(this->programId)
	{
		glDeleteProgram(this->programId);
		this->programId = 0;
	}
}

bool Shader::useProgram()
{
	if(this->programId)
	{
		glUseProgram(this->programId);
		return true;
	}
	return false;
}

GLuint Shader::compileShader(GLchar* src, GLenum shaderType)
{
	static GLchar message[1024];
	GLint compiled;
	GLuint shaderId;
	GLsizei length = 0;

	shaderId = glCreateShader(shaderType);
	glShaderSource(shaderId, 1, &src, NULL); 
	glCompileShader(shaderId);
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compiled);
	if(compiled != GL_TRUE)
	{
		glGetShaderInfoLog(shaderId, 1024, &length, message);
		SDL_Log("Unable to compile shader: %s", message);
        return 0;
	}
	return shaderId;
}

char* Shader::fileReadContents(const char* fileName)
{
	int fileSize;
	FILE* f = fopen(fileName, "r");
	char* fileContents;
	if(!f)
	{
		return (char*) 0;
	}
	fseek(f,0,SEEK_END);
	fileSize = ftell(f);
	fseek(f,0,SEEK_SET);
	fileContents = (char*) malloc(fileSize+1);
	fread(fileContents,1,fileSize,f);
	fileContents[fileSize] = '\0';
	fclose(f);
	return fileContents;
}

GLuint Shader::compileShaderFromFile(const char* fileName, GLenum shaderType)
{
	char* src;
	GLuint shaderId = 0;

	src = this->fileReadContents(fileName);
	if(src)
	{
		shaderId = this->compileShader(src,shaderType);
		free(src);
	}
	else
	{
		SDL_Log("Unable to load vertex shader: %s", fileName);
	}
	return shaderId;
}

GLuint Shader::createProgram(const char* programName)
{
	static char buffer[1024];
	GLuint vertexShaderId = 0;
	GLuint fragmentShaderId = 0;
	GLuint programId = 0;
	GLint linked = 0;
	GLint length = 0;

	sprintf(buffer,"shader/%s.vs.glsl",programName);
	vertexShaderId = this->compileShaderFromFile(buffer, GL_VERTEX_SHADER);
	if(!vertexShaderId)
	{
		return 0;
	}
	sprintf(buffer,"shader/%s.fs.glsl",programName);
	fragmentShaderId = this->compileShaderFromFile(buffer, GL_FRAGMENT_SHADER);
	if(!fragmentShaderId)
	{
		glDeleteShader(vertexShaderId);
		return 0;
	}
	programId = glCreateProgram();
	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);
	glLinkProgram(programId);
	glGetProgramiv(programId, GL_LINK_STATUS, &linked);
	if(linked != GL_TRUE)
	{
		glGetProgramInfoLog(programId, 1024, &length, buffer);
		SDL_Log("Unable to link program: %s", buffer);
		glDetachShader(programId, vertexShaderId);
		glDetachShader(programId, fragmentShaderId);
		glDeleteProgram(programId);
		programId = 0;
	}
	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderId);
	return programId;
}

void Shader::setMVP(glm::mat4 mvp)
{
	GLuint mvpId = glGetUniformLocation(this->programId, "MVP");
	glUniformMatrix4fv(mvpId, 1, GL_FALSE, &mvp[0][0]);
}
