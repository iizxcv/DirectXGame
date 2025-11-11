#include <DX3D/Game/Display.h>
#include <DX3D/Graphics/RenderSystem.h>

// Display 클래스의 생성자 구현입니다.
dx3d::Display::Display(const DisplayDesc& desc)
	// 1. 부모 클래스인 Window의 생성자를 먼저 호출하여 창을 생성합니다.
	: Window(desc.window)
{
	// 2. RenderSystem의 팩토리 메서드인 createSwapChain을 호출하여 SwapChain을 생성합니다.
	//    - m_handle: 부모 Window로부터 물려받은 윈도우 핸들
	//    - m_size: 부모 Window로부터 물려받은 창 크기
	//    생성된 SwapChain은 스마트 포인터인 m_swapChain에 저장되어 수명이 관리됩니다.
	m_swapChain = desc.renderSystem.createSwapChain({ m_handle, m_size });
}
