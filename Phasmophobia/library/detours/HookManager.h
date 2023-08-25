#pragma once
#include <unordered_map>
#include <mutex>
#include <Windows.h>
#include "detours.h"

#ifdef _WIN64
#pragma comment(lib, "[x64]detours.lib")
#else
#pragma comment(lib, "[x86]detours.lib")
#endif



class HookManager
{
public:
	template <typename Fn>
	static auto install(Fn func, Fn handler) -> bool {
		if (reinterpret_cast<void*>(handler) != nullptr && reinterpret_cast<void*>(func) != nullptr) {
			if (enable(func, handler)) {
				std::lock_guard map(lock);
				holderMap[reinterpret_cast<void*>(handler)] = reinterpret_cast<void*>(func);
				return true;
			}
		}
		return false;
	}

	template <typename Fn>
	inline static auto getOrigin(Fn handler) noexcept -> Fn {
		std::lock_guard map(lock);
		if (!holderMap.contains(reinterpret_cast<void*>(handler))) {
			return nullptr;
		}
		return reinterpret_cast<Fn>(holderMap[reinterpret_cast<void*>(handler)]);
	}

	template <typename Fn>
	static auto detach(Fn handler) noexcept -> void {
		std::lock_guard map(lock);
		disable(handler);
		holderMap.erase(reinterpret_cast<void*>(handler));
	}

	template <typename RType, typename... Params>
	inline static auto call(RType (*handler)(Params...), Params... params) -> RType {
		auto origin = getOrigin(handler);
		if (origin != nullptr)
			return origin(params...);

		return RType();
	}

	template <typename RType, typename... Params>
	inline static auto ccall(RType (__cdecl*handler)(Params...), Params... params) -> RType {
		auto origin = getOrigin(handler);
		if (origin != nullptr)
			return origin(params...);

		return RType();
	}

	template <typename RType, typename... Params>
	inline static auto scall(RType (__stdcall*handler)(Params...), Params... params) -> RType {
		auto origin = getOrigin(handler);
		if (origin != nullptr)
			return origin(params...);

		return RType();
	}

	template <typename RType, typename... Params>
	inline static auto fcall(RType (__fastcall*handler)(Params...), Params... params) -> RType {
		auto origin = getOrigin(handler);
		if (origin != nullptr)
			return origin(params...);

		return RType();
	}

	template <typename RType, typename... Params>
	inline static auto vcall(RType (__vectorcall*handler)(Params...), Params... params) -> RType {
		auto origin = getOrigin(handler);
		if (origin != nullptr)
			return origin(params...);

		return RType();
	}

	static auto detachAll() noexcept -> void {
		std::lock_guard map(lock);
		for (const auto& key : holderMap | std::views::keys) {
			disable(key);
		}
		holderMap.clear();
	}

private:
	inline static std::mutex lock{};
	inline static std::unordered_map<void*, void*> holderMap{};

	template <typename Fn>
	static auto disable(Fn handler) -> void {
		Fn origin = getOrigin(handler);
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourDetach(&reinterpret_cast<PVOID&>(origin), handler);
		DetourTransactionCommit();
	}

	template <typename Fn>
	static auto enable(Fn& func, Fn handler) -> bool {
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		const bool ret = !DetourAttach(&reinterpret_cast<PVOID&>(func), handler);
		DetourTransactionCommit();
		return ret;
	}
};

