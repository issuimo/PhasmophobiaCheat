#pragma once
#include <Windows.h>
#include <stdio.h>

namespace easyLog {
	class Log {
	public:
		// 打开控制台并重定向标准输入输出
		static auto OpenConsole() -> void {
			AllocConsole(); // 分配新的控制台窗口

			// 重定向标准输入输出到控制台
			freopen("CONIN$", "r+", stdin);
			freopen("CONOUT$", "w+", stdout);
			freopen("CONOUT$", "w+", stderr);

			// 设置控制台标题
			SetConsoleTitle(L"EasyLog Console");
		}

	private:
	};
}
