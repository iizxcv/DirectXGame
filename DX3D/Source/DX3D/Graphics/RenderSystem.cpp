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

	DX3DGraphicsLogErrorAndThow(
		m_d3dDevice->QueryInterface(IID_PPV_ARGS(&m_dxgiDevice)),
		"QyeryInterface failed to retrieve IDXGIDevice.");

	DX3DGraphicsLogErrorAndThow(
		m_dxgiDevice->GetParent(IID_PPV_ARGS(&m_dxgiAdapter)),
		"GetParent failed to retrieve IDXGIAdapter.");
	DX3DGraphicsLogErrorAndThow(
		m_dxgiAdapter->GetParent(IID_PPV_ARGS(&m_dxgiFactory)),
		"GetParent failed to retrieve IDXGIFactor.");

	
}


RenderSystem::~RenderSystem()
{
}

SwapChainPtr RenderSystem::createSwapChain(const SwapChainDesc& desc) const
{
	return std::make_shared<SwapChain>(desc, getGraphicsResourceDesc());
}

GraphicsResourceDesc dx3d::RenderSystem::getGraphicsResourceDesc() const noexcept
{
	return { {m_logger},shared_from_this() ,*m_d3dDevice.Get(), *m_dxgiFactory.Get()};
}
