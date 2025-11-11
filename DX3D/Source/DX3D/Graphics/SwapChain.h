#pragma once
#include <DX3D/Graphics/GraphicsResource.h>


namespace dx3d {

	// SwapChain 클래스는 렌더링된 백 버퍼를 프론트 버퍼로 교체(swap)하여
	// 화면에 그래픽을 표시하는 핵심적인 역할을 합니다.
	class SwapChain final : public GraphicsResource
	{
	public:
		// 생성자: SwapChain 생성에 필요한 정보(desc)와
		// 부모 클래스(GraphicsResource) 초기화에 필요한 정보(gDesc)를 받습니다.
		SwapChain(const SwapChainDesc& desc, const GraphicsResourceDesc& gDesc);
	
	private:
		// DirectX의 IDXGISwapChain 인터페이스에 대한 COM 포인터입니다.
		// ComPtr을 사용하여 참조 카운트를 자동으로 관리합니다.
		Microsoft::WRL::ComPtr<IDXGISwapChain> m_swapChain{};
	};

}