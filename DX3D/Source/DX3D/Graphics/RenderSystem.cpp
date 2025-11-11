#include "RenderSystem.h"
#include <DX3D/Graphics/GraphicsLogUtils.h>
#include <DX3D/Graphics/SwapChain.h>

using namespace dx3d;

RenderSystem::RenderSystem(const RenderSystemDesc& desc)
	:Base(desc.base)
{
	D3D_FEATURE_LEVEL featureLevel{};
	UINT createDeviceFlag{};

#ifdef _DEBUG
	createDeviceFlag |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	// D3D11 디바이스와 컨텍스트를 생성합니다.
	// 새로 추가된 DX3DGraphicsLogErrorAndThow 매크로를 사용하여 오류를 처리합니다.
	DX3DGraphicsLogErrorAndThow(
		D3D11CreateDevice(NULL, 
			D3D_DRIVER_TYPE_HARDWARE, 
			NULL, 
			createDeviceFlag, 
			NULL, 
			0, 
			D3D11_SDK_VERSION,
			&m_d3dDevice, 
			&featureLevel, 
			&m_d3dContext),
			"Direct3D11 initialization failed");

	// SwapChain 생성을 위해 D3D11Device로부터 DXGI 인터페이스들을 얻어옵니다.
	// 1. D3D11Device에서 QueryInterface를 통해 IDXGIDevice를 얻습니다.
	DX3DGraphicsLogErrorAndThow(
		m_d3dDevice->QueryInterface(IID_PPV_ARGS(&m_dxgiDevice)),
		"QyeryInterface failed to retrieve IDXGIDevice.");

	// 2. IDXGIDevice에서 GetParent를 통해 물리적 GPU 장치를 나타내는 IDXGIAdapter를 얻습니다.
	DX3DGraphicsLogErrorAndThow(
		m_dxgiDevice->GetParent(IID_PPV_ARGS(&m_dxgiAdapter)),
		"GetParent failed to retrieve IDXGIAdapter.");
	
	// 3. IDXGIAdapter에서 GetParent를 통해 DXGI 리소스(e.g., SwapChain)를 생성하는 IDXGIFactory를 얻습니다.
	DX3DGraphicsLogErrorAndThow(
		m_dxgiAdapter->GetParent(IID_PPV_ARGS(&m_dxgiFactory)),
		"GetParent failed to retrieve IDXGIFactor.");
}


RenderSystem::~RenderSystem()
{
}

// SwapChain을 생성하는 팩토리 메서드 구현입니다.
SwapChainPtr RenderSystem::createSwapChain(const SwapChainDesc& desc) const
{
	// std::make_shared를 사용하여 SwapChain 객체를 동적 할당하고 shared_ptr로 감싸 반환합니다.
	// SwapChain 생성자에는 SwapChain 자체에 필요한 정보(desc)와
	// 모든 그래픽 리소스에 공통적으로 필요한 정보(getGraphicsResourceDesc()가 반환)를 전달합니다.
	return std::make_shared<SwapChain>(desc, getGraphicsResourceDesc());
}

// 그래픽 리소스 생성에 필요한 공통 정보들을 담은 GraphicsResourceDesc 구조체를 만들어 반환합니다.
GraphicsResourceDesc dx3d::RenderSystem::getGraphicsResourceDesc() const noexcept
{
	// 중괄호 초기화(brace-initialization)를 사용하여 구조체를 간결하게 생성합니다.
	// {m_logger}: BaseDesc 초기화
	// shared_from_this(): RenderSystem 자신에 대한 shared_ptr 전달 (수명 관리용)
	// *m_d3dDevice.Get(): D3D 디바이스 참조 전달
	// *m_dxgiFactory.Get(): DXGI 팩토리 참조 전달
	return { {m_logger},
		shared_from_this(),
		*m_d3dDevice.Get(),
		*m_dxgiFactory.Get()};
}
