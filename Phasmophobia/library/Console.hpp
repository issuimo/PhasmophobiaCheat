#pragma once
#include <Windows.h>
#include <cstdio>
#include <print>
#include <string>
#define LOG_DEBUG(text) console::OutConsole(console::Debug,text,__FILE__,__LINE__)
#define LOG_INFO(text) console::OutConsole(console::Info,text,__FILE__,__LINE__)
#define LOG_WARNING(text) console::OutConsole(console::Warning,text,__FILE__,__LINE__)
#define LOG_ERROR(text) console::OutConsole(console::Error,text,__FILE__,__LINE__)

namespace console {
	enum OutType : short int {
		Info,
		Debug,
		Warning,
		Error
	};

	enum Color : short int {
		Black,
		Blue,
		Green,
		LightGreen,
		Red,
		Purple,
		Yellow,
		White,
		Grey,
		LightBlue,
		ThinGreen,
		LightLightGreen,
		LightRed,
		Lavender,
		CanaryYellow,
		BrightWhite
	};

	static auto OutConsole(const OutType type, const std::string& text, const std::string& file, int line) -> void {
		const auto hWnd_ = GetStdHandle(STD_OUTPUT_HANDLE);
		switch (type) {
			case Info: SetConsoleTextAttribute(hWnd_, BACKGROUND_INTENSITY | Green * 16);
				std::print(" ");
				SetConsoleTextAttribute(hWnd_, BACKGROUND_INTENSITY | Black);
				SetConsoleTextAttribute(hWnd_, FOREGROUND_INTENSITY | White);
				std::print("[");
				SetConsoleTextAttribute(hWnd_, FOREGROUND_INTENSITY | Green);
				std::print("Info ");
				break;
			case Debug: SetConsoleTextAttribute(hWnd_, BACKGROUND_INTENSITY | Blue * 16);
				std::print(" ");
				SetConsoleTextAttribute(hWnd_, BACKGROUND_INTENSITY | Black);
				SetConsoleTextAttribute(hWnd_, FOREGROUND_INTENSITY | White);
				std::print("[");
				SetConsoleTextAttribute(hWnd_, FOREGROUND_INTENSITY | Blue);
				std::print("Debug");
				break;
			case Warning: SetConsoleTextAttribute(hWnd_, BACKGROUND_INTENSITY | Yellow * 16);
				std::print(" ");
				SetConsoleTextAttribute(hWnd_, BACKGROUND_INTENSITY | Black);
				SetConsoleTextAttribute(hWnd_, FOREGROUND_INTENSITY | White);
				std::print("[");
				SetConsoleTextAttribute(hWnd_, FOREGROUND_INTENSITY | Yellow);
				std::print("Warn ");
				break;
			case Error: SetConsoleTextAttribute(hWnd_, BACKGROUND_INTENSITY | Red * 16);
				std::print(" ");
				SetConsoleTextAttribute(hWnd_, BACKGROUND_INTENSITY | Black);
				SetConsoleTextAttribute(hWnd_, FOREGROUND_INTENSITY | White);
				std::print("[");
				SetConsoleTextAttribute(hWnd_, FOREGROUND_INTENSITY | Red);
				std::print("Error");
				break;
		}
		SetConsoleTextAttribute(hWnd_, FOREGROUND_INTENSITY | White);
		std::print("]>[");
		SetConsoleTextAttribute(hWnd_, FOREGROUND_INTENSITY | Purple);
		std::print("{}:{}", file.substr(file.find_last_of('\\') + 1), line);
		SetConsoleTextAttribute(hWnd_, FOREGROUND_INTENSITY | White);
		std::print("] :{}", text);
	}

	static auto StartConsole(const wchar_t* title, const bool close) -> HWND {
		HWND hWnd_ = nullptr;
		AllocConsole();
		SetConsoleTitleW(title);
		while (nullptr == hWnd_) hWnd_ = GetConsoleWindow();
		const auto menu_ = GetSystemMenu(hWnd_, FALSE);
		if (!close) DeleteMenu(menu_, SC_CLOSE, MF_BYCOMMAND);
		SetWindowLong(hWnd_, GWL_STYLE, GetWindowLong(hWnd_, GWL_STYLE) & ~WS_MAXIMIZEBOX);
		SetWindowLong(hWnd_, GWL_STYLE, GetWindowLong(hWnd_, GWL_STYLE) & ~WS_THICKFRAME);
		freopen_s(reinterpret_cast<FILE**>(stdout), "CONOUT$", "w+", stdout);
		freopen_s(reinterpret_cast<FILE**>(stderr), "CONOUT$", "w+", stderr);
		freopen_s(reinterpret_cast<FILE**>(stdin), "CONIN$", "r+", stdin);
		return hWnd_;
	}

	static auto EndConsole() -> void {
		fclose(stdout);
		fclose(stderr);
		fclose(stdin);
		FreeConsole();
	}
}
