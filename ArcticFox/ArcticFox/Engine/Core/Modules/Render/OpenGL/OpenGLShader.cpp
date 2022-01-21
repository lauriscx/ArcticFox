#include "OpenGLShader.h"
#include "Glad/glad.h"
#include <string>
#include <iostream>


Graphics::OpenGL::OpenGLShader::OpenGLShader() {
unsigned int m_VertexShader;
unsigned int m_FragmentShader;
unsigned int m_Shader;

	std::string vert = "#version 330 core\n"
		"layout(location = 0) in vec3 position;\n"
		"void main(){\n"
		"gl_Position = vec4(position, 1.0);\n"
		"}";
	std::string frag = "#version 330 core\n"
		"out vec4 color;\n"
		"void main(){\n"
		"color = vec4(1.0, 0.0, 0.0, 1.0);\n"
		"}";

	m_Shader = glCreateProgram();

	m_VertexShader = glCreateShader(GL_VERTEX_SHADER);
	const char* v = vert.c_str();
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
	const char* f = frag.c_str();
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

Graphics::OpenGL::OpenGLShader::~OpenGLShader()
{
}
