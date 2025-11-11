#pragma once
#include <DX3D/Window/Window.h>

namespace dx3d {

	// Display 클래스는 게임의 최종 화면을 표시하는 역할을 합니다.
	// Window 클래스를 상속받아 윈도우의 기본 기능을 가지며,
	// 내부에 SwapChain을 소유하여 실제 렌더링 결과를 화면에 보여줄 수 있게 합니다.
	class Display final : public Window
	{
	public:
		// DisplayDesc 구조체로부터 필요한 정보(창 크기, RenderSystem 참조 등)를 받아 Display 객체를 생성합니다.
		Display(const DisplayDesc& desc);
	private:
		// 렌더링된 이미지를 화면에 표시하기 위한 SwapChain에 대한 스마트 포인터입니다.
		// shared_ptr를 사용하여 수명을 안전하게 관리합니다.
		SwapChainPtr m_swapChain{};
	};
}