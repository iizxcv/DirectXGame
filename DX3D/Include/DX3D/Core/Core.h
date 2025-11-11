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
#include <stdexcept>
#include <memory>

namespace dx3d
{
	class Base;
	class Window;
	class Game;

	class GraphicsEngine;
	class RenderSystem;

	class Logger;
	// SwapChain 클래스를 전방 선언합니다. 실제 정의를 포함하지 않고 이름만 알려주어 컴파일 속도를 높입니다.
	class SwapChain;
	// Display 클래스를 전방 선언합니다.
	class Display;

	// C++ 기본 데이터 타입에 대한 별칭(alias)을 정의하여 코드 가독성과 이식성을 높입니다.
	// 32비트 정수
	using i32 = int;
	// 64비트 부호 없는 정수
	using ui64 = unsigned int;
	// 32비트 부동 소수점
	using f32 = float;
	// 64비트 부동 소수점
	using d64 = double;

	// SwapChain에 대한 std::shared_ptr의 별칭입니다.
	// 이를 통해 SwapChain 객체의 수명을 여러 소유자가 안전하게 공유하여 관리할 수 있습니다.
	using SwapChainPtr = std::shared_ptr<SwapChain>;

}