
#include "main/Engine.h"
#include "main/EntryPoint.h"

#include "Layers/EditorLayer.h"


namespace GE {
	class GenesisEditor : public Application
	{
	public:
		GenesisEditor()
			: Application("Genesis Editor")
		{
			PushLayer(new EditorLayer());
		}

		~GenesisEditor()
		{

		}
	};

	Application* CreateApplication()
	{
		return new GenesisEditor;
	}

}