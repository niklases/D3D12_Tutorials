// d3d12book.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers.
#endif

#include <windows.h>
#include <string>
#include <wrl.h>
#include <shellapi.h>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <D3Dcompiler.h>
#include <DirectXMath.h>
#include "../Common/d3dx12.h"


using namespace DirectX;
using Microsoft::WRL::ComPtr;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, PSTR commandLine, int nCmdShow)
{
	XMVECTOR vector = {};

	HRESULT WINAPI D312CreateDevice(
		IUnknown* pAdapter,
		D3D_FEATURE_LEVEL MinimumFeatureLevel,
		REFIID riid,  // Expected: ID3D12Device
		void** ppDevice
	);
#if defined(DEBUG) || defined(_DEBUG)
	// Enable the D3D12 debug layer.
	{
		ComPtr<ID3D12Debug> debugController;
		D3D12GetDebugInterface(IID_PPV_ARGS(&debugController));
		debugController->EnableDebugLayer();
	}
#endif
	ComPtr<IDXGIFactory4> mdxgiFactory;
	CreateDXGIFactory1(IID_PPV_ARGS(&mdxgiFactory));

	ComPtr<ID3D12Device> m3dDevice;
	// Try to create hardware device.
	HRESULT hardwareResult = D3D12CreateDevice(
		nullptr,  // default adapter
		D3D_FEATURE_LEVEL_11_0,
		IID_PPV_ARGS(&m3dDevice)
	);

	/*
	if (FAILED(hardwareResult))
	{
		ComPtr<IDXGIAdapter> pWarpAdapter;
		mdxgiFactory->EnumWarpAdapter(IID_PPV_ARGS(&pWarpAdapter));

		D312CreateDevice(
			pWarpAdapter.Get(),
			D3D_FEATURE_LEVEL_11_0,
			IID_PPV_ARGS(&m3dDevice)
		);
		// More to be added
	}
	*/

	// Check quality levels 
	// Not yet implemented

	// Enumerate adapters
	UINT c1 = 0;
	IDXGIAdapter* adapter = nullptr;
	while (mdxgiFactory->EnumAdapters(c1, &adapter) != DXGI_ERROR_NOT_FOUND)
	{
		UINT c2 = 0;
		DXGI_ADAPTER_DESC desc;
		adapter->GetDesc(&desc);
		std::wstring c_string = std::to_wstring(c1);
		std::wstring text = L"\nIdentified adapter(s): ";
		text += c_string += L" - ";
		text += desc.Description;
		text += L"\n";

		OutputDebugString(text.c_str());

		IDXGIOutput* adapterOutput = nullptr;
		while (adapter->EnumOutputs(c2, &adapterOutput) != DXGI_ERROR_NOT_FOUND)
		{
			DXGI_OUTPUT_DESC desc;
			adapterOutput->GetDesc(&desc);
			std::wstring text = L"    Output: ";
			text += std::to_wstring(c2) += L" - ";
			text += desc.DeviceName;
			text += L"\n";
			OutputDebugString(text.c_str());
			c2++;
		}

		c1++;
	}
	OutputDebugString(L"\n");

	return 0;

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

