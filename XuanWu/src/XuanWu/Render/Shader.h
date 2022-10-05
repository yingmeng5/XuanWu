#pragma once

#include <string>

namespace XuanWu {

	class Shader
	{
	public:
		Shader(const std::string& vertexPath, const std::string& fragmentPath);
		~Shader();

		void Bind() const;
		void Unbind() const;
	private:
		uint32_t m_RenderID;
	};
}