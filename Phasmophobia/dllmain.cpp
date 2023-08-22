#include "Init.h"
#include "library/Font.hpp"
#include "library/d3d11hook.h"
#include "library/log.h"
#include "library/imgui/imgui_impl_dx11.h"
#include "library/imgui/imgui_impl_win32.h"

extern auto ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT;

auto APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) -> BOOL {
    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
            AntiAntiCheat();
            std::thread([hModule] {
                // 打开控制台
                easyLog::Log::OpenConsole();

                // 初始化Mono
                unity::Il2cpp::SetModule(GetModuleHandleA("GameAssembly.dll"));

                // 初始化功能列表
                initSpace::Feature::Init();

                // 安装D3D11HOOK
                dxhook::Hk11::Build([hModule] {
                    if (!initSpace::guiInfo.imGuiInit) {
                        IMGUI_CHECKVERSION();

                        // 创建ImGui上下文 
                        ImGui::CreateContext();
                        ImPlot::CreateContext();

                        // 获取ImGui IO 并设置 键盘和手柄控制
                        auto io = ImGui::GetIO();
                        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
                        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

                        // 设置中文字体
                        io.Fonts->AddFontFromMemoryTTF(fontdata,
                                                       sizeof fontdata,
                                                       15,
                                                       nullptr,
                                                       io.Fonts->GetGlyphRangesChineseFull());

                        // 设置ImGui主题
                        ImGui::StyleColorsClassic();

                        // 初始化ImGui D3D11设备和窗口
                        ImGui_ImplWin32_Init(dxhook::Hk11::GetHwnd());
                        ImGui_ImplDX11_Init(dxhook::Hk11::GetDevice(), dxhook::Hk11::GetContext());

                        // 接管窗口消息
                        dxhook::Hk11::SetWndProc([](HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) -> char {
                            ImGuiIO& io = ImGui::GetIO();
                            POINT    mPos;
                            GetCursorPos(&mPos);
                            ScreenToClient(dxhook::Hk11::GetHwnd(), &mPos);
                            ImGui::GetIO().MousePos.x = static_cast<float>(mPos.x);
                            ImGui::GetIO().MousePos.y = static_cast<float>(mPos.y);
                            ImGui_ImplWin32_WndProcHandler(hWnd,msg,wParam,lParam);

                            // 按键处理
                            switch (msg) {
                                case WM_KEYDOWN:
                                    // 处理界面显示/隐藏
                                    if (wParam == VK_DELETE) {
                                        if (initSpace::guiInfo.mainShow)
                                            initSpace::guiInfo.mainShow = false;
                                        else
                                            initSpace::guiInfo.mainShow = true;
                                    }
                                    break;
                                case WM_KEYUP:
                                    break;
                                case WM_CLOSE:
                                    const int result = MessageBox(nullptr,L"你确定要退出游戏吗?", L"Confirmation",MB_YESNO | MB_ICONQUESTION);

                                    if (result == IDYES)
                                        exit(0);
                                    if (result == IDNO)
                                        return 2;
                                    break;
                            }

                            return true;
                        });

                        auto HexToRGBA = [](std::string Hex) {
                            int r, g, b, a;
                            sscanf_s(Hex.c_str(), "%02x%02x%02x%02x", &r, &g, &b, &a);
                            const ImVec4 color{
                                (static_cast<float>(r) / 255), (static_cast<float>(g) / 255),
                                (static_cast<float>(b) / 255), (static_cast<float>(a) / 255)
                            };
                            return color;
                        };

                        auto& styles = ImGui::GetStyle();

                        // Colors
                        auto colors                     = styles.Colors;
                        colors[ImGuiCol_Border]                = HexToRGBA("0C846ED5");
                        colors[ImGuiCol_BorderShadow]          = HexToRGBA("00000000");
                        colors[ImGuiCol_Button]                = HexToRGBA("0D9F9D9F");
                        colors[ImGuiCol_ButtonActive]          = HexToRGBA("076B3A94");
                        colors[ImGuiCol_ButtonHovered]         = HexToRGBA("0CAD4FCA");
                        colors[ImGuiCol_CheckMark]             = HexToRGBA("E6E6E680");
                        colors[ImGuiCol_ChildBg]               = HexToRGBA("00000045");
                        colors[ImGuiCol_DragDropTarget]        = HexToRGBA("333333FF");
                        colors[ImGuiCol_FrameBg]               = HexToRGBA("00000066");
                        colors[ImGuiCol_FrameBgActive]         = HexToRGBA("0D7F33B0");
                        colors[ImGuiCol_FrameBgHovered]        = HexToRGBA("09818B66");
                        colors[ImGuiCol_Header]                = HexToRGBA("0297959F");
                        colors[ImGuiCol_HeaderActive]          = HexToRGBA("07834ACC");
                        colors[ImGuiCol_HeaderHovered]         = HexToRGBA("00B8588A");
                        colors[ImGuiCol_MenuBarBg]             = HexToRGBA("069981CC");
                        colors[ImGuiCol_ModalWindowDimBg]      = HexToRGBA("3333335A");
                        colors[ImGuiCol_NavHighlight]          = HexToRGBA("7373E6CC");
                        colors[ImGuiCol_NavWindowingDimBg]     = HexToRGBA("CCCCCC33");
                        colors[ImGuiCol_NavWindowingHighlight] = HexToRGBA("FFFFFFB3");
                        colors[ImGuiCol_PlotHistogram]         = HexToRGBA("E6B300FF");
                        colors[ImGuiCol_PlotHistogramHovered]  = HexToRGBA("FF9900FF");
                        colors[ImGuiCol_PlotLines]             = HexToRGBA("FFFFFFFF");
                        colors[ImGuiCol_PlotLinesHovered]      = HexToRGBA("E6B300FF");
                        colors[ImGuiCol_PopupBg]               = HexToRGBA("1D1D24EB");
                        colors[ImGuiCol_ResizeGrip]            = HexToRGBA("FFFFFF1A");
                        colors[ImGuiCol_ResizeGripActive]      = HexToRGBA("C7D2FFE6");
                        colors[ImGuiCol_ResizeGripHovered]     = HexToRGBA("C7D2FF99");
                        colors[ImGuiCol_ScrollbarBg]           = HexToRGBA("33404D99");
                        colors[ImGuiCol_ScrollbarGrab]         = HexToRGBA("0C864E65");
                        colors[ImGuiCol_ScrollbarGrabActive]   = HexToRGBA("02B3916F");
                        colors[ImGuiCol_ScrollbarGrabHovered]  = HexToRGBA("05925966");
                        colors[ImGuiCol_Separator]             = HexToRGBA("1CA09A7E");
                        colors[ImGuiCol_SeparatorActive]       = HexToRGBA("0099B1FF");
                        colors[ImGuiCol_SeparatorHovered]      = HexToRGBA("048897FF");
                        colors[ImGuiCol_SliderGrab]            = HexToRGBA("FFFFFF4D");
                        colors[ImGuiCol_SliderGrabActive]      = HexToRGBA("04882F99");
                        colors[ImGuiCol_Tab]                   = HexToRGBA("18999F60");
                        colors[ImGuiCol_TabActive]             = HexToRGBA("038B4CD7");
                        colors[ImGuiCol_TabHovered]            = HexToRGBA("1E784BCC");
                        colors[ImGuiCol_TabUnfocused]          = HexToRGBA("FFFFFF00");
                        colors[ImGuiCol_TabUnfocusedActive]    = HexToRGBA("5A5AA700");
                        colors[ImGuiCol_TableBorderLight]      = HexToRGBA("FFFFFF00");
                        colors[ImGuiCol_TableBorderStrong]     = HexToRGBA("00014000");
                        colors[ImGuiCol_TableHeaderBg]         = HexToRGBA("2E8D89FF");
                        colors[ImGuiCol_TableRowBg]            = HexToRGBA("3E72769A");
                        colors[ImGuiCol_TableRowBgAlt]         = HexToRGBA("154D3E9B");
                        colors[ImGuiCol_Text]                  = HexToRGBA("E6E6E6FF");
                        colors[ImGuiCol_TextDisabled]          = HexToRGBA("999999FF");
                        colors[ImGuiCol_TextSelectedBg]        = HexToRGBA("00A87E5A");
                        colors[ImGuiCol_TitleBg]               = HexToRGBA("00998D8A");
                        colors[ImGuiCol_TitleBgActive]         = HexToRGBA("008D556B");
                        colors[ImGuiCol_TitleBgCollapsed]      = HexToRGBA("27B6C14A");
                        colors[ImGuiCol_WindowBg]              = HexToRGBA("00000096");

                        //Styles
                        styles.Alpha                      = 1.0;
                        styles.AntiAliasedFill            = true;
                        styles.AntiAliasedLines           = true;
                        styles.AntiAliasedLinesUseTex     = true;
                        styles.ButtonTextAlign            = ImVec2(0.5, 0.5);
                        styles.CellPadding                = ImVec2(4.0, 2.0);
                        styles.ChildBorderSize            = 1.0;
                        styles.ChildRounding              = 0.0;
                        styles.CircleTessellationMaxError = 0.30000001192092896;
                        styles.ColorButtonPosition        = 1;
                        styles.ColumnsMinSpacing          = 6.0;
                        styles.CurveTessellationTol       = 1.25;
                        styles.DisabledAlpha              = 0.6000000238418579;
                        styles.DisplaySafeAreaPadding     = ImVec2(3.0, 3.0);
                        styles.DisplayWindowPadding       = ImVec2(19.0, 19.0);
                        styles.FrameBorderSize            = 0.0;
                        styles.FramePadding               = ImVec2(4.0, 3.0);
                        styles.FrameRounding              = 0.0;
                        styles.GrabMinSize                = 10.0;
                        styles.GrabRounding               = 0.0;
                        styles.IndentSpacing              = 21.0;
                        styles.ItemInnerSpacing           = ImVec2(4.0, 4.0);
                        styles.ItemSpacing                = ImVec2(8.0, 4.0);
                        styles.LogSliderDeadzone          = 4.0;
                        styles.MouseCursorScale           = 1.0;
                        styles.PopupBorderSize            = 0.0;
                        styles.PopupRounding              = 0.0;
                        styles.ScrollbarRounding          = 0.0;
                        styles.ScrollbarSize              = 14.0;
                        styles.SelectableTextAlign        = ImVec2(0.0, 0.0);
                        styles.TabBorderSize              = 0.0;
                        styles.TabMinWidthForCloseButton  = 0.0;
                        styles.TabRounding                = 0.0;
                        styles.TouchExtraPadding          = ImVec2(0.0, 0.0);
                        styles.WindowBorderSize           = 0.0;
                        styles.WindowMenuButtonPosition   = 0;
                        styles.WindowMinSize              = ImVec2(32.0, 32.0);
                        styles.WindowPadding              = ImVec2(8.0, 8.0);
                        styles.WindowRounding             = 0.0;
                        styles.WindowTitleAlign           = ImVec2(0.0, 0.5);

                        initSpace::guiInfo.imGuiInit = true;
                        initSpace::guiInfo.mainShow  = true;
                        initSpace::guiInfo.tipsShow  = true;
                        tagRECT Rect;
                        GetClientRect(dxhook::Hk11::GetHwnd(), &Rect);
                        initSpace::guiInfo.w = Rect.right - Rect.left;
                        initSpace::guiInfo.h = Rect.bottom - Rect.top;
                    }

                    // 创建新的画面帧
                    ImGui_ImplDX11_NewFrame();
                    ImGui_ImplWin32_NewFrame();
                    ImGui::NewFrame();

                    ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(initSpace::guiInfo.w / 2, initSpace::guiInfo.h / 2), 3, 0xFF0000FF, 4, 2);

                    // 主界面
                    if (initSpace::guiInfo.mainShow && !initSpace::guiInfo.tipsShow) {
                        if (ImGui::Begin(reinterpret_cast<const char*>(u8"Phasmophobia Cheat By 遂沫"))) {

                            if (ImGui::Button(reinterpret_cast<const char*>(u8"保存"))) {
                                std::ofstream o(".\\cfg.json");
                                if (o) {
                                    nlohmann::json js;
                                    for (const auto& _features : initSpace::Feature::features | std::views::values) {
                                        for (const auto func : _features)
                                            func->Save(js);
                                    }
                                    o << js;
                                    o.close();
                                }
                            }
                            ImGui::SameLine();
                            if (ImGui::Button(reinterpret_cast<const char*>(u8"读取"))) {
                                std::ifstream i(".\\cfg.json");
                                if (i) {
                                    nlohmann::json js = nlohmann::json::parse(i);
                                    for (const auto& _features : initSpace::Feature::features | std::views::values) {
                                        for (const auto func : _features)
                                            func->Load(js);
                                    }
                                    i.close();
                                }
                            }

                            if (ImGui::BeginTabBar("memList")) {
                                for (const auto& [name, _features] : initSpace::Feature::features) {
                                    if (ImGui::BeginTabItem(name.c_str())) {
                                        for (const auto func : _features) {
                                            if (func->GetInfo().needGroup) {
                                                if (ImGui::CollapsingHeader(func->GetInfo().groupName.c_str()))
                                                    func->Render();
                                            } else
                                                func->Render();
                                        }
                                        ImGui::EndTabItem();
                                    }
                                }
                                ImGui::EndTabBar();
                            }

                            ImGui::End();
                        }
                    }
 
                    for (const auto& _features : initSpace::Feature::features | std::views::values) {
                        for (const auto func : _features)
                            func->DrawStatus();
                    }

                    if (initSpace::guiInfo.tipsShow) {
                        if (ImGui::Begin("Tips")) {
                            ImGui::Text(reinterpret_cast<const char*>(u8"按下Delete (Del) 键显示隐藏菜单界面"));
                            if (ImGui::Button("OK"))
                                initSpace::guiInfo.tipsShow = false;
                            ImGui::End();
                        }
                    }

                    // 结束并渲染
                    ImGui::EndFrame();
                    ImGui::Render();
                    dxhook::Hk11::GetContext()->OMSetRenderTargets(1,dxhook::Hk11::GetTargetView(),nullptr);
                    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
                });

                // 线程异步更新
                std::vector<std::future<void>> futuresUpdate;
                while (true) {
                    Sleep(1);

                    // 多线程并发
                    for (const auto& feature : initSpace::Feature::features | std::views::values) {
                        for (const auto func : feature)
                            futuresUpdate.push_back(std::async(std::launch::async, [&func] {
                                func->Update();
                            }));
                    }

                    // 检查是否所有任务都已完成
                    for (auto& future : futuresUpdate) {
                    wait: if (future.wait_for(std::chrono::seconds(0)) != std::future_status::ready) {
                            Sleep(1);
                            goto wait;
                        }
                    }

                    futuresUpdate.clear();
                }
            }).detach();
            break;
        case DLL_THREAD_ATTACH:
            break;
        case DLL_THREAD_DETACH:
            break;
        case DLL_PROCESS_DETACH:
            break;
    }
    return TRUE;
}
