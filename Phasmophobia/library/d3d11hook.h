#pragma once
#include "detours/HookManager.h"
#include <d3d11.h>
#include <functional>

#pragma comment(lib, "d3d11.lib")
 
namespace dxhook {
	class Hk11 {
		using IDXGISwapChainPresent = HRESULT(*)(IDXGISwapChain*, UINT, UINT);
	public:
		static auto Build(std::function<void()> fn) -> bool {
            if (!fn)
                return false;

            if (IDXGISwapChainPresent pre = findDirect11Present()) {
                present = fn;
                return HookManager::install(pre, MyPresent);
            }

            return false;
		}

		static auto SetWndProc(char(*wndProc)(HWND, UINT, WPARAM, LPARAM)) -> void {
            WndProc = wndProc;
            oldWndProc = reinterpret_cast<WNDPROC>(GetWindowLongPtr(hwnd, GWLP_WNDPROC));
            SetWindowLongPtr(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(NewWndProc));
		}

		static auto Unbuild() -> void { HookManager::detach(MyPresent); }

		inline static auto GetHwnd() -> HWND { return hwnd; }
		inline static auto GetDevice() -> ID3D11Device* { return g_Device; }
		inline static auto GetSwapChain() -> IDXGISwapChain* { return g_SwapChain; }
		inline static auto GetContext() -> ID3D11DeviceContext* { return g_Context; }
		inline static auto GetTargetView() -> ID3D11RenderTargetView* const * { return &g_TargetView; }

	private:
		inline static bool inited{false};

		inline static HWND hwnd{};
		inline static WNDPROC oldWndProc{};
        inline static UINT g_ResizeWidth;
        inline static UINT g_ResizeHeight;

		inline static std::function<void()> present;
		inline static char(*WndProc)(HWND, UINT, WPARAM, LPARAM);

		inline static ID3D11Device* g_Device{};
		inline static IDXGISwapChain* g_SwapChain{};
		inline static ID3D11DeviceContext* g_Context{};
		inline static ID3D11RenderTargetView* g_TargetView{};

		static auto findDirect11Present() -> IDXGISwapChainPresent {
            WNDCLASSEX wc{ 0 };
            wc.cbSize = sizeof(wc);
            wc.lpfnWndProc = DefWindowProc;
            wc.lpszClassName = TEXT("Class");

            if (!RegisterClassEx(&wc))
                return nullptr;

            HWND hWnd = CreateWindow(wc.lpszClassName, TEXT(""), WS_DISABLED, 0, 0, 0, 0, NULL, NULL, NULL, nullptr);
            IDXGISwapChain* pSwapChain;

            D3D_FEATURE_LEVEL    featureLevel;
            DXGI_SWAP_CHAIN_DESC swapChainDesc;
            ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
            swapChainDesc.BufferCount = 1;
            swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
            swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
            swapChainDesc.OutputWindow = hWnd;
            swapChainDesc.SampleDesc.Count = 1;
            swapChainDesc.Windowed = ((GetWindowLong(hWnd, GWL_STYLE) & WS_POPUP) != 0) ? FALSE : TRUE;
            swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
            swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
            swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

            ID3D11DeviceContext* pContext = nullptr;
            ID3D11Device* pDevice = nullptr;

            if (FAILED(
                D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_WARP, nullptr, 0, nullptr, 1, D3D11_SDK_VERSION, &
                    swapChainDesc, &pSwapChain, &pDevice, &featureLevel, &pContext)) && FAILED(
                        D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION,
                            &swapChainDesc, &pSwapChain, &pDevice, &featureLevel, &pContext))) {
                DestroyWindow(swapChainDesc.OutputWindow);
                UnregisterClass(wc.lpszClassName, GetModuleHandle(nullptr));

                return nullptr;
            }
            const DWORD_PTR* pSwapChainVtable = reinterpret_cast<DWORD_PTR*>(pSwapChain);
            pSwapChainVtable = reinterpret_cast<DWORD_PTR*>(pSwapChainVtable[0]);

            auto swapChainPresent = reinterpret_cast<IDXGISwapChainPresent>(pSwapChainVtable[8]);

            pDevice->Release();
            pContext->Release();
            pSwapChain->Release();
            DestroyWindow(swapChainDesc.OutputWindow);
            UnregisterClass(wc.lpszClassName, GetModuleHandle(nullptr));

            return swapChainPresent;
		}

		static auto MyPresent(IDXGISwapChain* a, UINT b, UINT c) -> HRESULT {
            if (!inited) {
                g_SwapChain = a;
                auto result = a->GetDevice(__uuidof(g_Device), reinterpret_cast<void**>(&g_Device));
                if (SUCCEEDED(result)) {
                    g_Device->GetImmediateContext(&g_Context);
                    DXGI_SWAP_CHAIN_DESC sd;
                    a->GetDesc(&sd);
                    hwnd = sd.OutputWindow;
                    ID3D11Texture2D* pBackBuffer{};
                    a->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<LPVOID*>(&pBackBuffer));
                    g_Device->CreateRenderTargetView(pBackBuffer, nullptr, &g_TargetView);
                    pBackBuffer->Release();
                    inited = true;
                }
            }

            // Handle window resize (we don't resize directly in the WM_SIZE handler)
            if (g_ResizeWidth != 0 && g_ResizeHeight != 0) {
                g_TargetView->Release();
                g_SwapChain->ResizeBuffers(0, g_ResizeWidth, g_ResizeHeight, DXGI_FORMAT_UNKNOWN, 0);
                g_ResizeWidth = g_ResizeHeight = 0;
                ID3D11Texture2D* pBackBuffer;
                g_SwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
                g_Device->CreateRenderTargetView(pBackBuffer, nullptr, &g_TargetView);
                pBackBuffer->Release();
            }

            present();

            return HookManager::call(MyPresent, a, b, c);
		}

		static auto CALLBACK NewWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) -> LRESULT {
			switch (uMsg) {
	            case WM_SIZE:
	                if (wParam == SIZE_MINIMIZED)
	                    return 0;
                    g_ResizeWidth  = static_cast<UINT>(LOWORD(lParam)); // Queue resize
                    g_ResizeHeight = static_cast<UINT>(HIWORD(lParam));
			}

			const auto ret = WndProc(hWnd, uMsg, wParam, lParam);
            if (ret == 1)
                return CallWindowProc(oldWndProc, hWnd, uMsg, wParam, lParam);
            if (ret == 0)
                return DefWindowProc(hWnd, uMsg, wParam, lParam);
            if (ret == 2) {
                return NULL;
            }
		}
	};
}
