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


#include <DX3D/Window/Window.h> // Window 클래스 헤더 파일을 포함합니다.
#include <Windows.h> // Windows API 헤더 파일을 포함합니다.
#include <stdexcept> // 표준 예외 처리를 위한 헤더 파일을 포함합니다.

// 윈도우 프로시저 함수: 윈도우 메시지를 처리합니다.
// HWND hwnd: 윈도우 핸들
// UINT msg: 메시지 식별자
// WPARAM wparam: 추가 메시지 정보
// LPARAM lparam: 추가 메시지 정보
static LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	// 수신된 메시지에 따라 처리를 분기합니다.
	switch (msg)
	{
	// 윈도우가 닫히려고 할 때 발생하는 메시지입니다.
	case WM_CLOSE:
	{
		// 프로그램 종료 메시지(WM_QUIT)를 메시지 큐에 보냅니다.
		PostQuitMessage(0);
		// switch 문을 빠져나갑니다.
		break;
	}
	// 위에서 처리되지 않은 모든 다른 메시지들을 처리합니다.
	default:
		// 기본 윈도우 프로시저를 호출하여 기본 메시지 처리를 수행합니다.
		return DefWindowProc(hwnd, msg, wparam, lparam);
	}
	// 메시지가 처리되었음을 나타내는 0을 반환합니다.
	return 0;
}

// Window 클래스의 생성자입니다. Base 클래스의 생성자를 호출합니다.
dx3d::Window::Window(const WindowDesc& desc)
	: Base(desc.base)
{
	// 윈도우 클래스를 등록하는 람다 함수를 정의합니다.
	auto registerWindowClassFunction = []()
		{
			// 윈도우 클래스 정보를 담는 WNDCLASSEX 구조체를 선언하고 초기화합니다.
			WNDCLASSEX wc{};
			// 구조체의 크기를 설정합니다.
			wc.cbSize = sizeof(WNDCLASSEX);
			// 윈도우 클래스의 이름을 설정합니다.
			wc.lpszClassName = L"DX3DWindow_Joo";
			// 윈도우 프로시저 함수의 포인터를 설정합니다.
			wc.lpfnWndProc = &WindowProcedure;
			// 윈도우 클래스를 운영체제에 등록하고 그 결과를 반환합니다.
			return RegisterClassEx(&wc);
		};

	// 위에서 정의한 람다 함수를 호출하여 윈도우 클래스를 등록하고,
	// 반환된 클래스 ID를 정적 변수에 저장합니다. 이렇게 하면 클래스가 한 번만 등록됩니다.
	static const auto windowClassId = std::invoke(registerWindowClassFunction);

	// 윈도우 클래스 등록이 실패했는지 확인합니다.
	if (!windowClassId){

		getLogger().log(Logger::LogLevel::Error, "RegisterClassEx failed");
		// 실패했다면 런타임 오류를 발생시킵니다.
		throw std::runtime_error("RegisterClassEx failed.");
	}

	// 클라이언트 영역의 크기를 1280x720으로 설정하는 RECT 구조체를 정의합니다.
	RECT rc{ 0,0,1280,720 };
	// 지정된 클라이언트 영역 크기를 얻기 위해 필요한 윈도우 전체 크기를 계산합니다.
	// 윈도우 스타일(테두리, 캡션, 시스템 메뉴)을 고려합니다.
	AdjustWindowRect(&rc, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, false);

	// 윈도우를 생성합니다.
	// 확장 윈도우 스타일 (없음)
	// 등록된 윈도우 클래스
	// 윈도우 제목
	// 윈도우 스타일
	// 윈도우의 기본 위치
	// 계산된 윈도우의 너비와 높이
	// 부모 윈도우, 메뉴, 인스턴스 핸들, 추가 파라미터 (모두 없음)
	m_handle = CreateWindowEx(NULL, 
		MAKEINTATOM(windowClassId), 
		L"JooCode | C++ 3D Game Tutorial Series",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, 
		CW_USEDEFAULT, CW_USEDEFAULT, 
		rc.right - rc.left, rc.bottom - rc.top, 
		NULL, NULL, NULL, NULL); 

	// 윈도우 생성이 실패했는지 확인합니다.
	if (!m_handle){
		getLogger().log(Logger::LogLevel::Error, "CreateWindowEx failed");
		// 실패했다면 런타임 오류를 발생시킵니다.
		throw std::runtime_error("CreateWindowEx failed.");
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
