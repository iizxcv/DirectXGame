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
#include <DX3D/Core/Common.h>


 
namespace dx3d
{
	class Window: public Base
	{
	public:
		explicit Window(const WindowDesc& desc);
		virtual ~Window() override;

	// 접근 제어자가 private에서 protected로 변경되었습니다.
	// 이는 자식 클래스인 Display에서 윈도우 핸들(m_handle)과 크기(m_size)에
	// 접근하여 SwapChain을 생성할 수 있도록 하기 위함입니다.
	protected:
		// 윈도우 핸들(HWND)을 저장하는 포인터입니다.
		void* m_handle{};
		// 윈도우의 클라이언트 영역 크기(너비, 높이)를 저장합니다.
		Rect m_size{};
	};
}

