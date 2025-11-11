//MIT License
//
//C++ 3D Game Tutorial Series(https://github.com/PardCode/CPP-3D-Game-Tutorial-Series)
//
//Copyright(c) 2019 - 2025, PardCode
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files(the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions :
//
//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.



#include <DX3D/Game/Game.h>
#include <DX3D/Window/Window.h>
#include <DX3D/Graphics/GraphicsEngine.h>
#include <DX3D/Core/Logger.h>
#include <DX3D/Game/Display.h>

// Game 클래스 생성자: GameDesc 구조체로부터 설정을 받아 초기화합니다.
dx3d::Game::Game(const GameDesc& desc)
	// Base 클래스 생성자에 Logger 인스턴스를 주입합니다.
	: Base({*std::make_unique<Logger>(desc.logLevel).release()}),
	m_loggerPtr(&m_logger)
{
	// GraphicsEngine을 생성하고, 의존성으로 Logger를 주입합니다.
	m_graphicsEngine = std::make_unique<GraphicsEngine>(GraphicsEngineDesc{m_logger});
	
	// Window 대신 Display를 생성합니다.
	// Display 생성에는 Window 생성 정보(Logger, 창 크기)와
	// SwapChain 생성에 필요한 RenderSystem 참조가 모두 필요합니다.
	m_display = std::make_unique<Display>(DisplayDesc{ 
			{m_logger, desc.windowSize}, // WindowDesc 초기화
			m_graphicsEngine->getRenderSystem() }); // RenderSystem 참조 전달


	// 새로 만든 로깅 매크로를 사용하여 초기화 메시지를 출력합니다.
	DX3DLogInfo("Game initialized");
}

dx3d::Game::~Game()
{
	// 새로 만든 로깅 매크로를 사용하여 소멸 메시지를 출력합니다.
	DX3DLogInfo("Game deallocation started.");
}


