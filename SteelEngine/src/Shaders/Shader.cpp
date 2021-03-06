#include "Shader.h";


namespace Steel
{
	namespace Shaders
	{
		Shader::Shader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource, unsigned int* program)
		{
			m_VertexShaderSource = vertexShaderSource;
			m_FragmentShaderSource = fragmentShaderSource;
			m_Program = *program;
		}

		void Shader::Create()
		{
			unsigned int vertexShader = Compile(GL_VERTEX_SHADER);
			unsigned int fragmentShader = Compile(GL_FRAGMENT_SHADER);

			glAttachShader(m_Program, vertexShader);
			glAttachShader(m_Program, fragmentShader);

			glLinkProgram(m_Program);
			glValidateProgram(m_Program);

			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);
		}

		void Shader::SetUniform4f(const char* name, float v1, float v2, float v3, float v4)
		{
			int location = glGetUniformLocation(m_Program, name);

			glUniform4f(location, v1, v2, v3, v4);
		}

		void Shader::SetUniform3f(const char* name, float v1, float v2, float v3)
		{
			int location = glGetUniformLocation(m_Program, name);

			glUniform3f(location, v1, v2, v3);
		}

		unsigned int Shader::Compile(unsigned int type)
		{
			unsigned int shaderID = glCreateShader(type);

			const char* src = (type == GL_VERTEX_SHADER ? m_VertexShaderSource.c_str(): m_FragmentShaderSource.c_str());

			glShaderSource(shaderID, 1, &src, nullptr);
			glCompileShader(shaderID);

			int result;
			glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);

			if (result == GL_FALSE)
			{
				int length;
				glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);

				char* message = (char*)_malloca(length * sizeof(char));

				glGetShaderInfoLog(shaderID, length, &length, message);
				std::cout << message << std::endl;
				glDeleteShader(shaderID);

				return 0;
			}

			return shaderID;
		}


	}
}