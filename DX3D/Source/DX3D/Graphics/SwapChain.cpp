#include <DX3D/Graphics/SwapChain.h>

// SwapChain 생성자 구현
dx3d::SwapChain::SwapChain(const SwapChainDesc& desc, const GraphicsResourceDesc& gDesc)
	// 1. 부모 클래스인 GraphicsResource의 생성자를 호출하여 공통 리소스(device, factory 등)를 초기화합니다.
	:GraphicsResource(gDesc)
{
	// 2. DirectX SwapChain을 생성하기 위해 필요한 설정들을 DXGI_SWAP_CHAIN_DESC 구조체에 채웁니다.
	DXGI_SWAP_CHAIN_DESC dxgiDesc{};
	// 버퍼의 너비와 높이를 설정합니다. 0이 되면 안되므로 최소 1로 설정합니다.
	dxgiDesc.BufferDesc.Width = std::max(1, desc.winSize.width);
	dxgiDesc.BufferDesc.Height = std::max(1, desc.winSize.height);
	// 버퍼의 픽셀 포맷을 설정합니다. (R8G8B8A8, UNORM)
	dxgiDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	// 버퍼의 개수를 설정합니다. 창 모드에서는 2개의 백 버퍼를 사용(총 3개 버퍼로 트리플 버퍼링 효과)
	dxgiDesc.BufferCount = 2;
	// 버퍼의 사용 목적을 설정합니다. 렌더 타겟으로 사용될 것입니다.
	dxgiDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	
	// SwapChain이 출력될 윈도우의 핸들을 지정합니다.
	dxgiDesc.OutputWindow = static_cast<HWND>(desc.winHandle);
	// 멀티샘플링 설정을 합니다. (지금은 사용 안 함)
	dxgiDesc.SampleDesc.Count = 1;
	// 화면 전환 효과를 설정합니다. (플립-버리고-다시-만들기 모델)
	dxgiDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	// 창 모드로 실행하도록 설정합니다.
	dxgiDesc.Windowed = TRUE;


	// 3. 설정이 완료된 dxgiDesc를 사용하여 IDXGIFactory의 CreateSwapChain 메서드를 호출합니다.
	//    생성된 SwapChain 객체는 m_swapChain 멤버에 저장됩니다.
	DX3DGraphicsLogErrorAndThow(
		m_factory.CreateSwapChain(&m_device, &dxgiDesc, &m_swapChain)
		, "CreateSwapChain Failed.");
}