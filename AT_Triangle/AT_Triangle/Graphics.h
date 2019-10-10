#pragma once
#include "WinDisable.h"
#include "Exception.h"
#include <d3d11.h>

class Graphics
{
public:
	// Error handling classes
	class GraphicsException : public Exception
	{
		using Exception::Exception;
	};

	class HrException : public GraphicsException
	{
	public:
		// Details of the error
		HrException(int line, const char* file, HRESULT hr) noexcept;
		const char* what() const noexcept override; 
		const char* GetType() const noexcept override;
		HRESULT GetErrorCode() const noexcept;
		std::string GetErrorString() const noexcept;
		std::string GetErrorDescription() const noexcept;
	private:
		HRESULT hr;
	};

	class DeviceRemovedException : public HrException
	{
		using HrException::HrException;
	public:
		const char* GetType() const noexcept override;
	};

public:
	Graphics(HWND hWnd);
	Graphics(const Graphics&) = delete;
	Graphics& operator = (const Graphics&) = delete;
	~Graphics();

	void EndFrame();
	void ClearBuffer(float red, float green, float blue) noexcept;

private:
	ID3D11Device* pDevice = nullptr;
	IDXGISwapChain* pSwap = nullptr;
	ID3D11DeviceContext* pContext = nullptr;
	ID3D11RenderTargetView* pTarget = nullptr;
};