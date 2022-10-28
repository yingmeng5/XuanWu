#pragma once

#include "XuanWu/Render/Shader.h"

#include <glm/glm.hpp>

namespace XuanWu {

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		void setBool(const std::string& name, bool value) const;
		void setInt(const std::string& name, int value) const;
		void setFloat(const std::string& name, float value) const;
		void setMat4(const std::string& name, const glm::mat4& model) const;
		void setMat3(const std::string& name, const glm::mat3& model) const;
		void setVec3(const std::string& name, float x, float y, float z) const;
		void setVec3(const std::string& name, const glm::vec3& value) const;
		void setVec2(const std::string& name, const glm::vec2& value) const;
	private:
		uint32_t m_RendererID;
	};
}