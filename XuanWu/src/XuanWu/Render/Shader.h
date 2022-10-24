#pragma once

#include <string>
#include <glm/glm.hpp>

namespace XuanWu {

	class Shader
	{
	public:
		Shader(const std::string& vertexPath, const std::string& fragmentPath);
		~Shader();

		void Bind() const;
		void Unbind() const;

		void setMat4(const std::string& name, const glm::mat4& matrix) const;
	private:
		uint32_t m_RenderID;
	};
}