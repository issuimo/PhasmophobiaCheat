#pragma once
#ifndef HOT_KEY
#define HOT_KEY

#include <map>
#include <mutex>
#include <ranges>
#include <vector>

class HotKey {
public:
	using Method = void(*)();

	static auto BuildKey(const int key, const Method method) -> void {
		std::lock_guard lock(mutex);
		map[key].push_back(method);
	}

	static auto UnBuild(const int key, const Method method) -> void {
		std::lock_guard lock(mutex);
		auto& methods = map[key];
		if (const auto it = std::ranges::find(methods, method); it != methods.end()) methods.erase(it);
	}

	static auto UnBuildAll() -> void {
		std::lock_guard lock(mutex);
		for (auto methods : map | std::views::values) methods.clear();
	}

	static auto PotMsg(const int msg) -> void {
		std::lock_guard lock(mutex);
		for (const auto method : map[msg]) method();
	}
private:
	inline static std::mutex mutex;
	inline static std::map<int, std::vector<Method>> map;
};

#endif
