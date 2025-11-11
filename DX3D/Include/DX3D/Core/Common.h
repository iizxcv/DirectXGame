#pragma once
#include <DX3D/Core/Core.h>
#include <DX3D/Core/Logger.h>
// 사각형을 표현하는 Rect 클래스를 포함합니다. 창 크기 등을 지정하는 데 사용됩니다.
#include <DX3D/Math/Rect.h>
namespace dx3d
{
	struct BaseDesc
	{
		Logger& logger;
	};

	struct WindowDesc
	{
		BaseDesc base;
		// 창의 크기(너비, 높이)를 저장하는 Rect 구조체입니다.
		Rect size{};
	};
	
	// Display 클래스 생성에 필요한 정보들을 그룹화한 구조체입니다.
	struct DisplayDesc
	{
		// Display가 상속받는 Window를 생성하는 데 필요한 정보입니다.
		WindowDesc window;
		// SwapChain을 생성하기 위해 RenderSystem에 대한 참조가 필요합니다.
		RenderSystem& renderSystem;
	};

	struct GraphicsEngineDesc
	{
		BaseDesc base;
	};

	struct RenderSystemDesc
	{
		BaseDesc base;
	};

	// SwapChain 생성에 필요한 정보들을 그룹화한 구조체입니다.
	struct SwapChainDesc
	{
		// SwapChain을 연결할 창의 핸들입니다.
		void* winHandle{};
		// SwapChain의 버퍼 크기가 될 창의 크기 정보입니다.
		Rect winSize{};
	};

	// Game 클래스 생성에 필요한 정보들을 그룹화한 구조체입니다.
	struct GameDesc
	{
		// 게임 창의 기본 크기를 지정합니다.
		Rect windowSize{ 1280,720 };
		// 로거가 출력할 로그의 최소 레벨을 지정합니다.
		Logger::LogLevel logLevel = Logger::LogLevel::Error;

	};
}