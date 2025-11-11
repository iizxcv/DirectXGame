#pragma once
#include <DX3D/Graphics/GraphicsResource.h>
#include <DX3D/Core/Common.h>
#include <DX3D/Core/Base.h>
#include <d3d11.h>
#include <wrl.h>

namespace dx3d
{
	// RenderSystem은 이제 std::enable_shared_from_this를 상속받습니다.
	// 이를 통해 RenderSystem 객체 내부에서 this 포인터로부터 안전하게 std::shared_ptr를 생성할 수 있습니다.
	// (shared_from_this() 메서드 사용 가능)
	class RenderSystem final : public Base, public std::enable_shared_from_this<RenderSystem>
	{
	public:
		explicit RenderSystem(const RenderSystemDesc& desc);
		virtual  ~RenderSystem() override;

		// SwapChain을 생성하는 팩토리 메서드입니다.
		// SwapChain 생성에 필요한 정보를 받아 SwapChain 객체를 생성하고,
		// 그 소유권을 담은 스마트 포인터(SwapChainPtr)를 반환합니다.
		SwapChainPtr createSwapChain(const SwapChainDesc& desc) const;

	private:
		// 그래픽 리소스 생성에 필요한 정보(device, factory, logger 등)를 담은
		// GraphicsResourceDesc 구조체를 생성하여 반환하는 헬퍼 메서드입니다.
		GraphicsResourceDesc getGraphicsResourceDesc() const noexcept;

	private:
		Microsoft::WRL::ComPtr<ID3D11Device> m_d3dDevice{};
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_d3dContext{};

		// 아래는 SwapChain과 같은 DXGI(DirectX Graphics Infrastructure) 리소스를 생성하기 위해
		// D3D11Device로부터 얻어오는 인터페이스들입니다.
		Microsoft::WRL::ComPtr<IDXGIDevice> m_dxgiDevice{};
		Microsoft::WRL::ComPtr<IDXGIAdapter> m_dxgiAdapter{};
		Microsoft::WRL::ComPtr<IDXGIFactory> m_dxgiFactory{};
	};
}

