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
	static bool install(Fn func, Fn handler) {
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
	inline static Fn getOrigin(Fn handler) noexcept {
		std::lock_guard map(lock);
		if (holderMap.count(reinterpret_cast<void*>(handler)) == 0) {
			return nullptr;
		}
		return reinterpret_cast<Fn>(holderMap[reinterpret_cast<void*>(handler)]);
	}

	template <typename Fn>
	static void detach(Fn handler) noexcept {
		std::lock_guard map(lock);
		disable(handler);
		holderMap.erase(reinterpret_cast<void*>(handler));
	}

	template <typename RType, typename... Params>
	inline static RType call(RType(* handler)(Params...), Params... params) {
		auto origin = getOrigin(handler);
		if (origin != nullptr)
			return origin(params...);

		return RType();
	}

	template <typename RType, typename... Params>
	inline static RType ccall(RType(__cdecl* handler)(Params...), Params... params) {
		auto origin = getOrigin(handler);
		if (origin != nullptr)
			return origin(params...);

		return RType();
	}

	template <typename RType, typename... Params>
	inline static RType scall(RType(__stdcall* handler)(Params...), Params... params) {
		auto origin = getOrigin(handler);
		if (origin != nullptr)
			return origin(params...);

		return RType();
	}

	template <typename RType, typename... Params>
	inline static RType fcall(RType(__fastcall* handler)(Params...), Params... params) {
		auto origin = getOrigin(handler);
		if (origin != nullptr)
			return origin(params...);

		return RType();
	}

	template <typename RType, typename... Params>
	inline static RType vcall(RType(__vectorcall* handler)(Params...), Params... params) {
		auto origin = getOrigin(handler);
		if (origin != nullptr)
			return origin(params...);

		return RType();
	}

	static void detachAll() noexcept {
		std::lock_guard map(lock);
		for (const auto& [key, value] : holderMap) {
			disable(key);
		}
		holderMap.clear();
	}

private:
	inline static std::mutex lock{};
	inline static std::unordered_map<void*, void*> holderMap{};

	template <typename Fn>
	static void disable(Fn handler) {
		Fn origin = getOrigin(handler);
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourDetach(&(PVOID&)origin, handler);
		DetourTransactionCommit();
	}

	template <typename Fn>
	static bool enable(Fn& func, Fn handler) {
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		bool ret = !DetourAttach(&(PVOID&)func, handler);
		DetourTransactionCommit();
		return ret;
	}
};

