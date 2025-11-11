#pragma once
#include <DX3D/Core/Common.h>
#include <DX3D/Core/Base.h>
#include <DX3D/Graphics/GraphicsLogUtils.h>
#include <d3d11.h>
#include <wrl.h>


namespace dx3d {

	// 그래픽 리소스 생성에 필요한 공통 데이터들을 그룹화한 구조체입니다.
	struct GraphicsResourceDesc 
	{
		// BaseDesc는 로거(Logger)에 대한 참조를 포함합니다.
		BaseDesc base;
		// RenderSystem에 대한 shared_ptr입니다. 리소스의 수명 동안 RenderSystem이 유효하도록 보장합니다.
		std::shared_ptr<const RenderSystem> renderSystem;
		// D3D11 디바이스에 대한 참조입니다. 리소스 생성에 사용됩니다.
		ID3D11Device& device;
		// DXGI 팩토리에 대한 참조입니다. SwapChain 같은 DXGI 리소스 생성에 사용됩니다.
		IDXGIFactory& factory;
	};

	// SwapChain, Buffer, Texture 등 모든 그래픽 리소스들의 기반이 될 클래스입니다.
	// 공통적으로 필요한 데이터(RenderSystem, Device, Factory)와 기능들을 제공합니다.
	class GraphicsResource : public Base
	{
	public:
		// 생성자: GraphicsResourceDesc를 받아 멤버들을 초기화합니다.
		GraphicsResource(const GraphicsResourceDesc& desc)
			:Base(desc.base),
			m_renderSystem(desc.renderSystem),
			m_device(desc.device),
			m_factory(desc.factory)
		{

		}
	protected:
		// 자식 클래스에서 접근할 수 있도록 protected로 선언된 멤버 변수들입니다.
		std::shared_ptr<const RenderSystem> m_renderSystem;
		ID3D11Device& m_device;
		IDXGIFactory& m_factory;
	};
}
