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


#include <DX3D/Window/Window.h>
#include <Windows.h>
#include <stdexcept>

// 윈도우 프로시저 함수: 윈도우 메시지를 처리합니다.
static LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_CLOSE:
	{
		PostQuitMessage(0);
		break;
	}
	default:
		return DefWindowProc(hwnd, msg, wparam, lparam);
	}
	return 0;
}

// Window 클래스의 생성자입니다.
dx3d::Window::Window(const WindowDesc& desc)
	// Base 클래스 생성자를 호출하여 Logger를 초기화합니다.
	: Base(desc.base)
	// m_size 멤버를 desc에 전달된 크기로 초기화합니다.
	, m_size(desc.size)
{
	// 윈도우 클래스를 등록하는 람다 함수입니다.
	auto registerWindowClassFunction = []()
		{
			WNDCLASSEX wc{};
			wc.cbSize = sizeof(WNDCLASSEX);
			wc.lpszClassName = L"DX3DWindow_Joo";
			wc.lpfnWndProc = &WindowProcedure;
			return RegisterClassEx(&wc);
		};

	// 람다 함수를 호출하여 윈도우 클래스를 등록하고, ID를 정적 변수에 저장하여 한 번만 등록되도록 합니다.
	static const auto windowClassId = std::invoke(registerWindowClassFunction);

	// 윈도우 클래스 등록 실패 시, 새로 만든 매크로를 사용하여 오류를 기록하고 예외를 던집니다.
	if (!windowClassId){
		DX3DLogErrorAndThrow("RegisterClassEx failed.");
	}

	// 클라이언트 영역의 크기를 m_size 멤버 변수를 사용하여 설정합니다.
	RECT rc{ 0,0,m_size.width,m_size.height };
	// 지정된 클라이언트 영역 크기를 얻기 위해 필요한 윈도우 전체 크기를 계산합니다.
	AdjustWindowRect(&rc, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, false);

	// 윈도우를 생성합니다.
	m_handle = CreateWindowEx(NULL, 
		MAKEINTATOM(windowClassId), 
		L"JooCode | C++ 3D Game Tutorial Series",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, 
		CW_USEDEFAULT, CW_USEDEFAULT, 
		rc.right - rc.left, rc.bottom - rc.top, 
		NULL, NULL, NULL, NULL); 

	// 윈도우 생성 실패 시, 새로 만든 매크로를 사용하여 오류를 기록하고 예외를 던집니다.
	if (!m_handle){
		DX3DLogErrorAndThrow("CreateWindowEx failed.");
	}


	// 생성된 윈도우를 화면에 표시합니다.
	ShowWindow(static_cast<HWND>(m_handle), SW_SHOW);
}



// Window 클래스의 소멸자입니다.
dx3d::Window::~Window()
{
	// 윈도우 핸들과 연관된 윈도우를 파괴합니다.
	DestroyWindow(static_cast<HWND>(m_handle));
}
