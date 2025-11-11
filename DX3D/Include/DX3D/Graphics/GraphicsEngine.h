#pragma once
#include <DX3D/Core/Core.h>
#include <DX3D/Core/Base.h>


namespace dx3d
{
	class GraphicsEngine final : public Base
	{
	public:
		explicit GraphicsEngine(const GraphicsEngineDesc& desc);
		virtual ~GraphicsEngine() override;


		// RenderSystem에 대한 참조를 반환하는 getter 메서드입니다.
		// Display 같은 다른 객체들이 RenderSystem의 기능(e.g., SwapChain 생성)을 사용할 수 있도록 합니다.
		RenderSystem& getRenderSystem() const noexcept;
	private:
		// RenderSystem을 소유하는 스마트 포인터가 unique_ptr에서 shared_ptr로 변경되었습니다.
		// 이는 RenderSystem이 생성한 리소스(e.g., SwapChain)들이 RenderSystem 자체에 대한
		// shared_ptr을 소유하여, 리소스가 살아있는 동안 RenderSystem이 소멸되지 않도록 보장하기 위함입니다.
		std::shared_ptr<RenderSystem> m_renderSystem{};
	}; 


} 
