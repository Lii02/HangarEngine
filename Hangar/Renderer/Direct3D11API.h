#ifndef DIRECT3D11_API_H
#define DIRECT3D11_API_H
#include "IRenderAPI.h"

class Direct3D11API : public IRenderAPI {
	struct GPU {
		uint32_t index;
		DXGI_ADAPTER_DESC1 info;
		IDXGIAdapter1* adapter;
	};

	struct Monitor {
		uint32_t index;
		IDXGIOutput* output;
		DXGI_MODE_DESC* modes;
		uint32_t modeCount;
	};
private:
	ID3D11Device* device;
	ID3D11DeviceContext* deviceContext;
	IDXGIFactory2* factory;
	IDXGISwapChain* swapchain;
	ID3D11RenderTargetView* renderTargetView;
	ID3D11DepthStencilView* depthStencilView;
	ID3D11RasterizerState* rasterState;
	ID3D11BlendState* blendState;
	std::vector<GPU> adapters;
	std::vector<Monitor> monitors;
	D3D_FEATURE_LEVEL featureLevel;
	DirectX::CommonStates* commonStates;
public:
	Direct3D11API(GameWindow* windowPtr);
	~Direct3D11API();

	virtual void Initialize() override;
	virtual void DeInitialize() override;
	virtual void BeginFrame() override;
	virtual void EndFrame() override;
	virtual uint64_t CreateDataBuffer(size_t dataSize, size_t dataCount, DataBufferBinding binding) override;
	virtual void UpdateDataBuffer(uint64_t index, void* data) override;
	virtual void CleanDataBuffers() override;
	virtual void BindVertexBuffer(uint64_t index) override;
	virtual void BindIndexBuffer(uint64_t index) override;
	virtual void DrawIndexed(uint32_t count, uint32_t first) override;
	virtual void CleanShaders() override;
	virtual void BindRenderShader(uint64_t index) override;
	virtual uint64_t CreateRenderShader(std::string_view shaderSource, std::string vertexEntry, std::string pixelEntry, std::vector<InputElement> inputs) override;
	virtual void RemoveBuffer(uint64_t index) override;
private:
	void SetViewport();
};

#endif