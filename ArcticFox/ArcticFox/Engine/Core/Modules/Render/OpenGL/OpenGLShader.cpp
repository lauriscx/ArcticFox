#include "OpenGLShader.h"
#include "Glad/glad.h"
#include <string>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>


Graphics::OpenGL::OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertex, const std::string& fragment) : m_Name(name) {
	m_Shader = glCreateProgram();

	m_VertexShader = glCreateShader(GL_VERTEX_SHADER);
	const char* v = vertex.c_str();
	glShaderSource(m_VertexShader, 1, &v, 0);
	glCompileShader(m_VertexShader);

	int result;
	glGetShaderiv(m_VertexShader, GL_COMPILE_STATUS, &result);
	if (!result) {
		int lenght;
		glGetShaderiv(m_VertexShader, GL_INFO_LOG_LENGTH, &lenght);
		char* message = new char[lenght];
		glGetShaderInfoLog(m_VertexShader, lenght, &lenght, message);
		std::cout << "Vertex error " << message << std::endl;
	}

	m_FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const char* f = fragment.c_str();
	glShaderSource(m_FragmentShader, 1, &f, 0);
	glCompileShader(m_FragmentShader);

	glGetShaderiv(m_FragmentShader, GL_COMPILE_STATUS, &result);
	if (!result) {
		int lenght;
		glGetShaderiv(m_FragmentShader, GL_INFO_LOG_LENGTH, &lenght);
		char* message = new char[lenght];
		glGetShaderInfoLog(m_FragmentShader, lenght, &lenght, message);
		std::cout << "fragment error " << message << std::endl;
	}

	glAttachShader(m_Shader, m_VertexShader);
	glAttachShader(m_Shader, m_FragmentShader);
	glLinkProgram(m_Shader);
	glValidateProgram(m_Shader);


	glDeleteShader(m_VertexShader);
	glDeleteShader(m_FragmentShader);
	glUseProgram(m_Shader);
}


void Graphics::OpenGL::OpenGLShader::Bind() {
	glUseProgram(m_Shader);
}

void Graphics::OpenGL::OpenGLShader::Unbind() {
	glUseProgram(0);
}

void Graphics::OpenGL::OpenGLShader::UploadUniform(const std::string& name, const glm::mat4 & matrix) {
	glUseProgram(m_Shader);
	int location = glGetUniformLocation(m_Shader, name.c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Graphics::OpenGL::OpenGLShader::UploadUniform(const std::string & name, const glm::vec4 & vector) {
	glUseProgram(m_Shader);
	int location = glGetUniformLocation(m_Shader, name.c_str());
	glUniform4fv(location, 1, glm::value_ptr(vector));
}

void Graphics::OpenGL::OpenGLShader::UploadUniform(const std::string & name, const glm::vec3 & vector) {
	glUseProgram(m_Shader);
	int location = glGetUniformLocation(m_Shader, name.c_str());
	glUniform3fv(location, 1, glm::value_ptr(vector));
}

void Graphics::OpenGL::OpenGLShader::UploadUniform(const std::string & name, const glm::vec2 & vector) {
	glUseProgram(m_Shader);
	int location = glGetUniformLocation(m_Shader, name.c_str());
	glUniform2fv(location, 1, glm::value_ptr(vector));

}

void Graphics::OpenGL::OpenGLShader::UploadUniform(const std::string& name, int value) {
	glUseProgram(m_Shader);
	int location = glGetUniformLocation(m_Shader, name.c_str());
	glUniform1i(location, value);
}

Graphics::OpenGL::OpenGLShader::~OpenGLShader()
{
}

const std::string & Graphics::OpenGL::OpenGLShader::GetName() const {
	return m_Name;
}
