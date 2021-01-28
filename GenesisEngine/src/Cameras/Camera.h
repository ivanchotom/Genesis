#pragma once

#include <glm/glm.hpp>

namespace GE {

    /// This is the base Camera Class
	class Camera
	{
	public:
		Camera() = default;
		/// Takes in a projection
       ///@param projection the projection that the constructor takes in
		Camera(const glm::mat4& projection)
			: m_Projection(projection) {}
		
		virtual ~Camera() = default;


		/// Getter for projection
		/// <returns></returns>
		const glm::mat4& GetProjection() const { return m_Projection; }
	private:
       

	protected:
		glm::mat4 m_Projection = glm::mat4(1.0f);
	};



}