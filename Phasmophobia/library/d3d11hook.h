#pragma once

#ifndef _DX11HOOK_
#define _DX11HOOK_

#include <d3d11.h>
#include <functional>
#include "detours/HookManager.h"
#include "kiero/kiero.h"

#pragma comment(lib, "d3d11.lib")

namespace dx_hook {
	class Hk11 {
		using IDXGISwapChainPresent = HRESULT(*)(IDXGISwapChain*, UINT, UINT);

	public:
		static auto Build(const std::function<void()>& fn) -> bool {
			if (!fn) return false;

			Init(kiero::RenderType::D3D11);
			if (kiero::Bind(8, MyPresent) == kiero::Status::Success) {
				present = fn;
				return true;
			}
			return false;
		}

		static auto SetWndProc(char (*wndProc)(HWND, UINT, WPARAM, LPARAM)) -> void {
			Hk11::wndProc    = wndProc;
			oldWndProc = reinterpret_cast<WNDPROC>(GetWindowLongPtr(hWnd, GWLP_WNDPROC));
			SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(NewWndProc));
		}

		static auto Unbuild() -> void { HookManager::Detach(MyPresent); }

		static auto GetHwnd() -> HWND { return hWnd; }
		static auto GetDevice() -> ID3D11Device* { return gDevice; }
		static auto GetSwapChain() -> IDXGISwapChain* { return gSwapChain; }
		static auto GetContext() -> ID3D11DeviceContext* { return gContext; }
		static auto GetTargetView() -> ID3D11RenderTargetView* const * { return &gTargetView; }

	private:
		inline static bool init{false};

		inline static HWND    hWnd{};
		inline static WNDPROC oldWndProc{};

		inline static std::function<void()> present;
		inline static char (*               wndProc)(HWND, UINT, WPARAM, LPARAM);

		inline static ID3D11Device*           gDevice{};
		inline static IDXGISwapChain*         gSwapChain{};
		inline static ID3D11DeviceContext*    gContext{};
		inline static ID3D11RenderTargetView* gTargetView{};

		static auto WINAPI MyPresent(IDXGISwapChain* a, const UINT b, const UINT c) -> HRESULT {
			if (!init) {
				gSwapChain        = a;
				if (const auto result = a->GetDevice(__uuidof(gDevice), reinterpret_cast<void**>(&gDevice)); SUCCEEDED(result)) {
					gDevice->GetImmediateContext(&gContext);
					DXGI_SWAP_CHAIN_DESC sd;
					a->GetDesc(&sd);
					hWnd = sd.OutputWindow;
					ID3D11Texture2D* pBackBuffer{};
					a->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<LPVOID*>(&pBackBuffer));
					gDevice->CreateRenderTargetView(pBackBuffer, nullptr, &gTargetView);
					pBackBuffer->Release();
					init = true;
				}
			}

			present();

			return HookManager::Scall(MyPresent, a, b, c);
		}

		static auto NewWndProc(const HWND hWnd, const UINT uMsg, const WPARAM wParam, const LPARAM lParam) -> LRESULT {
			const auto ret = wndProc(hWnd, uMsg, wParam, lParam);
			if (ret == 1) return CallWindowProc(oldWndProc, hWnd, uMsg, wParam, lParam);
			if (ret == 0) return DefWindowProc(hWnd, uMsg, wParam, lParam);
			if (ret == 2) return NULL;
			return NULL;
		}
	};
}

#endif
