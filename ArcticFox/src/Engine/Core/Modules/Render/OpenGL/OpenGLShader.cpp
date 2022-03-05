#include "OpenGLShader.h"
#include "Glad/glad.h"
#include <string>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

#include <shaderc/shaderc.hpp>
#include <spirv_cross/spirv_cross.hpp>
#include <spirv_cross/spirv_glsl.hpp>


ArcticFox::Graphics::OpenGL::OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertex, const std::string& fragment, bool spirv) : m_Name(name) {
	std::unordered_map<GLenum, std::string> shaders;
	shaders[GL_FRAGMENT_SHADER] = fragment;
	shaders[GL_VERTEX_SHADER] = vertex;

	if(spirv) {

		auto VulkanBinaries = CompileVulkanBinaries(shaders);
		m_TexturesSlots.clear();
		for (const auto& data : VulkanBinaries) {
			Reflect(data.first, data.second);
		}
		auto OpenGLBinaries = CompileOpenGLBinaries(VulkanBinaries);
		CreateShaderProgram(OpenGLBinaries);

	} else {
		CreateShaderProgram(shaders);
	}
}


void ArcticFox::Graphics::OpenGL::OpenGLShader::Bind() {
	glUseProgram(m_Shader);
}

void ArcticFox::Graphics::OpenGL::OpenGLShader::Unbind() {
	glUseProgram(0);
}

void ArcticFox::Graphics::OpenGL::OpenGLShader::UploadUniform(const std::string& name, const glm::mat4 & matrix) {
	glUseProgram(m_Shader);
	int location = glGetUniformLocation(m_Shader, name.c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void ArcticFox::Graphics::OpenGL::OpenGLShader::UploadUniform(const std::string & name, const glm::vec4 & vector) {
	glUseProgram(m_Shader);
	int location = glGetUniformLocation(m_Shader, name.c_str());
	glUniform4fv(location, 1, glm::value_ptr(vector));
}

void ArcticFox::Graphics::OpenGL::OpenGLShader::UploadUniform(const std::string & name, const glm::vec3 & vector) {
	glUseProgram(m_Shader);
	int location = glGetUniformLocation(m_Shader, name.c_str());
	glUniform3fv(location, 1, glm::value_ptr(vector));
}

void ArcticFox::Graphics::OpenGL::OpenGLShader::UploadUniform(const std::string & name, const glm::vec2 & vector) {
	glUseProgram(m_Shader);
	int location = glGetUniformLocation(m_Shader, name.c_str());
	glUniform2fv(location, 1, glm::value_ptr(vector));

}

void ArcticFox::Graphics::OpenGL::OpenGLShader::UploadUniform(const std::string& name, int value) {
	glUseProgram(m_Shader);
	int location = glGetUniformLocation(m_Shader, name.c_str());
	glUniform1i(location, value);
}

void ArcticFox::Graphics::OpenGL::OpenGLShader::UploadUniform(const std::string & name, int * value, uint32_t count) {
	glUseProgram(m_Shader);
	int location = glGetUniformLocation(m_Shader, name.c_str());
	glUniform1iv(location, count, value);
}

std::vector<std::pair<std::string, uint32_t>> ArcticFox::Graphics::OpenGL::OpenGLShader::GetTextureSlots() {
	return m_TexturesSlots;
}

void ArcticFox::Graphics::OpenGL::OpenGLShader::Reflect(GLenum stage, const std::vector<uint32_t>& shaderData) {
	spirv_cross::CompilerGLSL glsl(std::move(shaderData));

	// The SPIR-V is now parsed, and we can perform reflection on it.
	spirv_cross::ShaderResources resources = glsl.get_shader_resources();

	// Get all sampled images in the shader.
	for (auto &resource : resources.sampled_images)
	{
		unsigned set = glsl.get_decoration(resource.id, spv::DecorationDescriptorSet);
		unsigned binding = glsl.get_decoration(resource.id, spv::DecorationBinding);
		std::cout << glsl.get_name(resource.id) << std::endl;
		std::cout<< glsl.get_name(resource.id) << std::endl;
		std::cout<< glsl.get_fallback_name(resource.id) << std::endl;
		printf("Image %s at set = %u, binding = %u\n", resource.name.c_str(), set, binding);

		// Modify the decoration to prepare it for GLSL.
		glsl.unset_decoration(resource.id, spv::DecorationDescriptorSet);

		// Some arbitrary remapping if we want.
		glsl.set_decoration(resource.id, spv::DecorationBinding, set * 16 + binding);

		std::string _name = "Texture";
		_name += glsl.get_fallback_name(resource.id);
		if (resource.name.empty()) {
			m_TexturesSlots.push_back(std::make_pair(_name, binding));
		} else {
			m_TexturesSlots.push_back(std::make_pair(resource.name, binding));
		}
	}


	/*spirv_cross::Compiler compiler(shaderData);
	spirv_cross::ShaderResources resource = compiler.get_shader_resources();
	

	for (const auto& image : resource.separate_images) {
		m_TexturesSlots.push_back(std::make_pair(image.name, image.id));
	}
	for (const auto& image : resource.separate_samplers) {
		m_TexturesSlots.push_back(std::make_pair(image.name, image.id));
	}
	//std::cout << resource.sampled_images.size() << std::endl;
	for (const auto& image : resource.sampled_images) {
		m_TexturesSlots.push_back(std::make_pair(image.name, image.id));
		//const auto& bufferType = compiler.get_type(image.base_type_id);
		//uint32_t bufferSize = compiler.get_declared_struct_size(bufferType);
		uint32_t binding = compiler.get_decoration(image.id, spv::DecorationBinding);
		//int memberCount = bufferType.member_types.size();

		std::cout << compiler.get_name(image.id) << std::endl;
		std::cout << compiler.get_fallback_name(image.id) << std::endl;
		//std::cout << "Size = " << bufferSize << std::endl;
		std::cout << "Binding" << binding << std::endl;
		//std::cout << "Members" << memberCount << std::endl;
	}

	for (const auto& uniform : resource.uniform_buffers) {
		//const auto& bufferType = compiler.get_type(uniform.base_type_id);
		//uint32_t bufferSize = compiler.get_declared_struct_size(bufferType);
		//uint32_t binding = compiler.get_decoration(uniform.id, spv::DecorationBinding);
		//int memberCount = bufferType.member_types.size();
		//
		//std::cout<< uniform.name << std::endl;
		//std::cout<<"Size = "<< bufferSize << std::endl;
		//std::cout<<"Binding" << binding << std::endl;
		//std::cout<<"Members"<< memberCount << std::endl;
	}*/
}

std::unordered_map<GLenum, std::vector<uint32_t>> ArcticFox::Graphics::OpenGL::OpenGLShader::CompileVulkanBinaries(const std::unordered_map<GLenum, std::string>& shadersSourceCode) {
	shaderc::Compiler compiler;//Create shaderC compiler.
	shaderc::CompileOptions options;//This is used to give options for compiler which we creater earler.
	options.SetTargetEnvironment(shaderc_target_env_vulkan, shaderc_env_version_vulkan_1_2);
	options.AddMacroDefinition("OPENGL");

	const bool optimize = true;
	if (optimize) {
		options.SetOptimizationLevel(shaderc_optimization_level_performance);
	}
	
	std::unordered_map<GLenum, std::vector<uint32_t>> ShadersData;
	
	for (auto&& [shaderType, source] : shadersSourceCode) {
		std::string path = "C:\Shaders\\" + std::to_string(shaderType);
		//shaderc_shader_kind type = shaderc_glsl_vertex_shader;//shaderc_glsl_fragment_shader;

		//shaderc::SpvCompilationResult module = compiler.CompileGlslToSpv(source, type, path.c_str(), options);
		shaderc::SpvCompilationResult module;
		if (shaderType == GL_VERTEX_SHADER) {
			module = compiler.CompileGlslToSpv(source, shaderc_glsl_vertex_shader, path.c_str(), options);
		}
		else if (shaderType == GL_FRAGMENT_SHADER) {
			module = compiler.CompileGlslToSpv(source, shaderc_glsl_fragment_shader, path.c_str(), options);
		}
		else if (shaderType == GL_GEOMETRY_SHADER) {
			module = compiler.CompileGlslToSpv(source, shaderc_glsl_geometry_shader, path.c_str(), options);
		}
		else if (shaderType == GL_COMPUTE_SHADER) {
			module = compiler.CompileGlslToSpv(source, shaderc_glsl_compute_shader, path.c_str(), options);
		}

		if (module.GetCompilationStatus() != shaderc_compilation_status_success) {
			std::cout << module.GetErrorMessage() << std::endl;
		}

		ShadersData[shaderType] = std::vector<uint32_t>(module.begin(), module.end());//Return binary WORDS.
	}

	return ShadersData;
}

std::unordered_map<GLenum, std::vector<uint32_t>> ArcticFox::Graphics::OpenGL::OpenGLShader::CompileOpenGLBinaries(const std::unordered_map<GLenum, std::vector<uint32_t>>& shadersSourceCode) {
	shaderc::Compiler compiler;//Create shaderC compiler.
	shaderc::CompileOptions options;//This is used to give options for compiler which we creater earler.
	options.SetTargetEnvironment(shaderc_target_env_opengl, shaderc_env_version_opengl_4_5);

	const bool optimize = true;
	if (optimize) {
		options.SetOptimizationLevel(shaderc_optimization_level_performance);
	}

	std::unordered_map<GLenum, std::vector<uint32_t>> ShadersData;
	std::unordered_map<GLenum, std::string> ShadersSource;

	for (auto&&[shaderType, spirv] : shadersSourceCode) {
		std::string ShaderIdentifier = "C:\Shaders\\" + std::to_string(shaderType);

		spirv_cross::CompilerGLSL glslCompiler(spirv);
		ShadersSource[shaderType] = glslCompiler.compile();
		auto& source = ShadersSource[shaderType];

		shaderc_shader_kind type = shaderc_glsl_vertex_shader;//shaderc_glsl_fragment_shader;
		//shaderc_glsl_infer_from_source this can be used to tel spirv to use from source type using #pragma annotation.

		//Compile to specific kind sader.
		shaderc::SpvCompilationResult module;
		if (shaderType == GL_VERTEX_SHADER) {
			module = compiler.CompileGlslToSpv(source, shaderc_glsl_vertex_shader, ShaderIdentifier.c_str(), options);
		}
		else if (shaderType == GL_FRAGMENT_SHADER) {
			module = compiler.CompileGlslToSpv(source, shaderc_glsl_fragment_shader, ShaderIdentifier.c_str(), options);
		}
		else if (shaderType == GL_GEOMETRY_SHADER) {
			module = compiler.CompileGlslToSpv(source, shaderc_glsl_geometry_shader, ShaderIdentifier.c_str(), options);
		}
		else if (shaderType == GL_COMPUTE_SHADER) {
			module = compiler.CompileGlslToSpv(source, shaderc_glsl_compute_shader, ShaderIdentifier.c_str(), options);
		}

		if (module.GetCompilationStatus() != shaderc_compilation_status_success) {
			std::cout << module.GetErrorMessage() << std::endl;
		}

		ShadersData[shaderType] = std::vector<uint32_t>(module.begin(), module.end());//Return binary WORDS.
	}

	return ShadersData;
}

void ArcticFox::Graphics::OpenGL::OpenGLShader::CreateShaderProgram(std::unordered_map<GLenum, std::vector<uint32_t>> openglBinary) {
	GLuint program = glCreateProgram();

	std::vector<GLuint> shadersIDS;
	
	//Attach/compile shaders from binary.
	for (auto&& [type, openglSPIRV] : openglBinary) {
		GLuint Shader = glCreateShader(type);
		shadersIDS.push_back(Shader);
		/* 1 shader with format of binary spirv, array first element pointer, sizeof array in bytes */
		glShaderBinary(1, &Shader, GL_SHADER_BINARY_FORMAT_SPIR_V, openglSPIRV.data(), openglSPIRV.size() * sizeof(uint32_t));
		glSpecializeShader(Shader, "main", 0, nullptr, nullptr);
		glAttachShader(program, Shader);
	}
	
	glLinkProgram(program);

	int result;
	glGetShaderiv(program, GL_LINK_STATUS, &result);
	if (!result) {
		int lenght;
		glGetShaderiv(program, GL_INFO_LOG_LENGTH, &lenght);
		char* message = new char[lenght];
		glGetShaderInfoLog(program, lenght, &lenght, message);
		std::cout << "fragment error " << message << std::endl;
		delete message;

		glDeleteProgram(program);
		for (auto shader : shadersIDS) {
			glDeleteShader(shader);
		}
		return;
	}

	/* Delete shaders because program already created */
	for (auto shader : shadersIDS) {
		glDetachShader(program, shader);
		glDeleteShader(shader);
	}
	glUseProgram(program);
	m_Shader = program;
}

void ArcticFox::Graphics::OpenGL::OpenGLShader::CreateShaderProgram(const std::unordered_map<GLenum, std::string>& shadersSourceCode) {
	GLuint program = glCreateProgram();

	std::vector<GLuint> shadersIDS;

	for (auto&& [type, code] : shadersSourceCode) {
		GLuint Shader = glCreateShader(type);
		shadersIDS.push_back(Shader);

		const char* v = code.c_str();
		glShaderSource(Shader, 1, &v, 0);
		glCompileShader(Shader);

		int result;
		glGetShaderiv(Shader, GL_COMPILE_STATUS, &result);
		if (!result) {
			int lenght;
			glGetShaderiv(Shader, GL_INFO_LOG_LENGTH, &lenght);
			char* message = new char[lenght];
			glGetShaderInfoLog(Shader, lenght, &lenght, message);
			std::cout << "error " << message << std::endl;

			for (auto shader : shadersIDS) {
				glDeleteShader(shader);
			}
			glDeleteProgram(program);
			return;
		}
		glAttachShader(program, Shader);
	}

	glLinkProgram(program);
	int result;
	glGetShaderiv(program, GL_LINK_STATUS, &result);
	if (!result) {
		int lenght;
		glGetShaderiv(program, GL_INFO_LOG_LENGTH, &lenght);
		char* message = new char[lenght];
		glGetShaderInfoLog(program, lenght, &lenght, message);
		std::cout << "error " << message << std::endl;
		delete message;

		glDeleteProgram(program);
		for (auto shader : shadersIDS) {
			glDeleteShader(shader);
		}
		return;
	}

	glValidateProgram(program);

	for (auto shader : shadersIDS) {
		glDetachShader(program, shader);
		glDeleteShader(shader);
	}

	glUseProgram(program);
	m_Shader = program;
}

ArcticFox::Graphics::OpenGL::OpenGLShader::~OpenGLShader() {
	glDeleteProgram(m_Shader);
}

const std::string & ArcticFox::Graphics::OpenGL::OpenGLShader::GetName() const {
	return m_Name;
}
