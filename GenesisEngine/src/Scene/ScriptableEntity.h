#pragma once

#include "Entity.h"

namespace GE {

	class ScriptableEntity
	{
	public:

		template<typename T>
		T& GetComponent()
		{
			return m_Entity.GetComponent<T>();
		}

	protected:
		virtual void OnCreate() {}
		virtual void OnUpdate() {}
		virtual void OnDestroy() {}


	private:
		Entity m_Entity;
		friend class Scene;
	};

}