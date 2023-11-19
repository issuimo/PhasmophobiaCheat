#pragma once

#ifndef _DX11HOOK_
#define _DX11HOOK_

#include "detours/HookManager.h"
#include <d3d11.h>
#include <functional>
#include "kiero/kiero.h"

#pragma comment(lib, "d3d11.lib")

namespace DxHook {
	class Hk11 {
		using IDXGISwapChainPresent = HRESULT(*)(IDXGISwapChain*, UINT, UINT);
	public:
		static auto Build(const std::function<void()>& fn) -> bool {
            if (!fn)
                return false;

            kiero::Init(kiero::RenderType::D3D11);
            if (kiero::Bind(8, MyPresent) == kiero::Status::Success) {
                present_ = fn;
                return true;
            }

            LOG_ERROR("Hook d3d11失败!");
            return false;
		}

		static auto SetWndProc(char(*wndProc)(HWND, UINT, WPARAM, LPARAM)) -> void {
            wndProc_ = wndProc;
            oldWndProc = reinterpret_cast<WNDPROC>(GetWindowLongPtr(hWnd_, GWLP_WNDPROC));
            SetWindowLongPtr(hWnd_, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(NewWndProc));
		}

		static auto Unbuild() -> void { HookManager::detach(MyPresent); }

		inline static auto GetHwnd() -> HWND { return hWnd_; }
		inline static auto GetDevice() -> ID3D11Device* { return g_Device; }
		inline static auto GetSwapChain() -> IDXGISwapChain* { return g_SwapChain; }
		inline static auto GetContext() -> ID3D11DeviceContext* { return g_Context; }
		inline static auto GetTargetView() -> ID3D11RenderTargetView* const * { return &g_TargetView; }

	private:
		inline static bool init_{false};

		inline static HWND hWnd_{};
		inline static WNDPROC oldWndProc{};

		inline static std::function<void()> present_;
		inline static char(*wndProc_)(HWND, UINT, WPARAM, LPARAM);

		inline static ID3D11Device* g_Device{};
		inline static IDXGISwapChain* g_SwapChain{};
		inline static ID3D11DeviceContext* g_Context{};
		inline static ID3D11RenderTargetView* g_TargetView{};

		static auto MyPresent(IDXGISwapChain* a, UINT b, UINT c) -> HRESULT {
            if (!init_) {
                g_SwapChain       = a;
				const auto result = a->GetDevice(__uuidof(g_Device), reinterpret_cast<void**>(&g_Device));
                if (SUCCEEDED(result)) {
                    g_Device->GetImmediateContext(&g_Context);
                    DXGI_SWAP_CHAIN_DESC sd;
                    a->GetDesc(&sd);
                    hWnd_ = sd.OutputWindow;
                    ID3D11Texture2D* pBackBuffer{};
                    a->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<LPVOID*>(&pBackBuffer));
                    g_Device->CreateRenderTargetView(pBackBuffer, nullptr, &g_TargetView);
                    pBackBuffer->Release();
                    init_ = true;
                }
            }

            present_();

            return HookManager::call(MyPresent, a, b, c);
		}

		static auto CALLBACK NewWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) -> LRESULT {
			const auto ret = wndProc_(hWnd, uMsg, wParam, lParam);
            if (ret == 1)
                return CallWindowProc(oldWndProc, hWnd, uMsg, wParam, lParam);
            if (ret == 0)
                return DefWindowProc(hWnd, uMsg, wParam, lParam);
            if (ret == 2) {
                return NULL;
            }
            return NULL;
		}
	};
}

#endif
