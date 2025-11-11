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



#pragma once
#include <DX3D/Core/Base.h>
#include <DX3D/Core/Core.h>



namespace dx3d
{
	class Game: public Base
	{
	public:
		// 생성자가 GameDesc 구조체를 받도록 변경되었습니다.
		// 이를 통해 창 크기, 로그 레벨 등 게임 초기화에 필요한 여러 설정을 한번에 전달할 수 있습니다.
		Game(const GameDesc& desc);
		virtual ~Game() override;

		virtual void run() final;
	private:
		Logger* m_loggerPtr{};
		std::unique_ptr<GraphicsEngine> m_graphicsEngine{}; 
		// m_display의 타입이 Window에서 Display로 변경되었습니다.
		// Display는 Window 기능에 더해 SwapChain을 관리하여 실제 렌더링이 가능하게 합니다.
		std::unique_ptr<Display> m_display{};
		bool m_isRunning{ true };
	};
}
