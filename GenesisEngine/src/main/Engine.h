#pragma once

// For use in Applications using the GameEngine.dll/lib

#include "Application.h"
#include "Layer.h"
#include "Log.h"

#include "main/TimeStep.h"

#include "Input.h"
#include "Events/KeyCodes.h"
#include "Events/MouseCode.h"

//------------UI---------------
#include "ImGui/ImGuiLayer.h"
//-----------------------------

//----------ECS--------------
#include "Scene/Scene.h"
#include "Scene/Entity.h"
#include "Scene/Component.h"
//-----------------------------

//----------Renderer--------------
#include "Renderer/Renderer.h"
#include "Renderer/Renderer2D.h"
#include "Renderer/Shader.h"
#include "Renderer/Framebuffer.h"
#include "Renderer/Texture.h"
#include "Renderer/SubTexture2D.h"
#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/RenderCommand.h"
//----------------------------------

//--------------Cameras-----------------
#include "Cameras/OrthographicCamera.h"
#include "Cameras/OrthographicCameraController.h"
//--------------------------------------


