#include <DX3D/Graphics/GraphicsEngine.h>
#include <DX3D/Graphics/RenderSystem.h>

using namespace dx3d;


GraphicsEngine::GraphicsEngine(const GraphicsEngineDesc& desc)
	:Base(desc.base)
{
	// 주석 코드 무슨얘기 하는지 전혀 모르겠음.
	//SwapChainPtr sc{};
	//{
	//	auto sys = std::make_unique<RenderSystem>(RenderSystemDesc{ m_logger });
	//	sc = sys->createSwapChain({});
	//}

	m_renderSystem = std::make_shared<RenderSystem>(RenderSystemDesc{ m_logger });
}

GraphicsEngine::~GraphicsEngine() 
{
}

RenderSystem& GraphicsEngine::getRenderSystem() const noexcept
{
	return *m_renderSystem;
}
