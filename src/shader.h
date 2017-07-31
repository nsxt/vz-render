#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class VzShader {
public:
	GLuint ID;

public:
	VzShader(const char* vs_file_path, const char* fs_file_path, const char* gs_file_path = nullptr) {
		std::string vs_code;
		std::string fs_code;
		std::string gs_code;

		std::ifstream vs_file;
		std::ifstream fs_file;
		std::ifstream gs_file;

		vs_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fs_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		gs_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try {
			vs_file.open(vs_file_path);
			fs_file.open(fs_file_path);

			std::stringstream vs_str_stream, fs_str_stream;
			vs_str_stream << vs_file.rdbuf();
			fs_str_stream << fs_file.rdbuf();

			vs_file.close();
			fs_file.close();

			vs_code = vs_str_stream.str();
			fs_code = fs_str_stream.str();

			if (gs_file_path != nullptr) {
				gs_file.open(gs_file_path);
				std::stringstream gs_str_stream;
				gs_str_stream << gs_file.rdbuf();
				gs_file.close();
				gs_code = gs_str_stream.str();
			}
		}
		catch (std::ifstream::failure e) {
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}

		const char* vs_code_strbuf = vs_code.c_str();
		const char* fs_code_strbuf = fs_code.c_str();
		GLuint vs, fs;

		// vertex shader
		vs = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vs, 1, &vs_code_strbuf, NULL);
		glCompileShader(vs);
		_error_log(vs, "VERTEX");

		// fragment shader
		fs = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fs, 1, &fs_code_strbuf, NULL);
		glCompileShader(fs);
		_error_log(vs, "FRAGMENT");

		// if geometry shader is given, compile geometry shader
		GLuint gs;
		if (gs_file_path != nullptr) {
			const char* gs_code_strbuf = gs_code.c_str();
			gs = glCreateShader(GL_GEOMETRY_SHADER);
			glShaderSource(gs, 1, &gs_code_strbuf, NULL);
			glCompileShader(gs);
			_error_log(vs, "GEOMETRY");
		}

		// shader program
		ID = glCreateProgram();
		glAttachShader(ID, vs);
		glAttachShader(ID, fs);
		if (gs_file_path != nullptr) {
			glAttachShader(ID, gs);
		}

		glLinkProgram(ID);
		_error_log(vs, "PROGRAM");

		glDeleteShader(vs);
		glDeleteShader(fs);
		if (gs_file_path != nullptr) {
			glDeleteShader(gs);
		}		
	}

	// ------------------------------------------------------------------------
	void set_bool(const std::string &name, bool value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}
	// ------------------------------------------------------------------------
	void set_int(const std::string &name, int value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}
	// ------------------------------------------------------------------------
	void set_float(const std::string &name, float value) const
	{
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}
	// ------------------------------------------------------------------------
	void set_vec2(const std::string &name, const glm::vec2 &value) const
	{
		glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}
	void set_vec2(const std::string &name, float x, float y) const
	{
		glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
	}
	// ------------------------------------------------------------------------
	void set_vec3(const std::string &name, const glm::vec3 &value) const
	{
		glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}
	void set_vec3(const std::string &name, float x, float y, float z) const
	{
		glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
	}
	// ------------------------------------------------------------------------
	void set_vec4(const std::string &name, const glm::vec4 &value) const
	{
		glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}
	void set_vec4(const std::string &name, float x, float y, float z, float w)
	{
		glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
	}
	// ------------------------------------------------------------------------
	void set_mat2(const std::string &name, const glm::mat2 &mat) const
	{
		glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
	// ------------------------------------------------------------------------
	void set_mat3(const std::string &name, const glm::mat3 &mat) const
	{
		glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
	// ------------------------------------------------------------------------
	void set_mat4(const std::string &name, const glm::mat4 &mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}

private:
	void _error_log(GLuint shader, std::string type) {
		GLint success;
		GLchar info_log[1024];

		if (type != "PROGRAM") {
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(shader, 1024, NULL, info_log);
				std::cout << "ERROR:SHADER_COMPILATION_ERROR of type : " << type << "\n" << info_log << std::endl;
				std::cout << "------------------------------------------------" << std::endl;
			}
		}
		else {
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success) {
				glGetProgramInfoLog(shader, 1024, NULL, info_log);
				std::cout << "ERROR:PROGRAM_LINKING_ERROR of type : " << type << "\n" << info_log << std::endl;
				std::cout << "------------------------------------------------" << std::endl;
			}
		}
	}
};