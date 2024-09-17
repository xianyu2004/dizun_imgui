#include "draw.h"
#include "main_hack.hpp"

bool permeate_record = false;
bool permeate_record_ini = false;
struct Last_ImRect LastCoordinate = {0, 0, 0, 0};

static uint32_t orientation = -1;
ANativeWindow *window;
// 屏幕信息
android::ANativeWindowCreator::DisplayInfo displayInfo;
// 窗口信息
ImGuiWindow *g_window;
// 绝对屏幕X _ Y
int abs_ScreenX, abs_ScreenY;

int native_window_screen_x, native_window_screen_y;

std::unique_ptr<AndroidImgui> graphics;
ImFont *zh_font = NULL;
ImFont *icon_font_0 = NULL;
ImFont *icon_font_1 = NULL;
ImFont *icon_font_2 = NULL;

bool M_Android_LoadFont(float SizePixels)
{
    ImGuiIO &io = ImGui::GetIO();
    io.Fonts->AddFontDefault();
    return zh_font != nullptr;
}
void init_My_drawdata()
{
    ImGui::My_Android_LoadSystemFont(30.0f); //(加载系统字体 无法释放)
    M_Android_LoadFont(30.0f);               // 加载字体(还有图标)
}

void screen_config()
{
    ::displayInfo = android::ANativeWindowCreator::GetDisplayInfo();
}

void drawBegin()
{
    if (::permeate_record_ini)
    {
        LastCoordinate.Pos_x = ::g_window->Pos.x;
        LastCoordinate.Pos_y = ::g_window->Pos.y;
        LastCoordinate.Size_x = ::g_window->Size.x;
        LastCoordinate.Size_y = ::g_window->Size.y;

        graphics->Shutdown();
        android::ANativeWindowCreator::Destroy(::window);
        ::window = android::ANativeWindowCreator::Create("test", native_window_screen_x, native_window_screen_y, permeate_record);
        graphics->Init_Render(::window, native_window_screen_x, native_window_screen_y);
        ::init_My_drawdata(); // 初始化绘制数据
    }

    screen_config();
    if (::orientation != displayInfo.orientation)
    {
        ::orientation = displayInfo.orientation;
        Touch::setOrientation(displayInfo.orientation);
        if (g_window != NULL)
        {
            g_window->Pos.x = 100;
            g_window->Pos.y = 125;
        }
        // cout << " width:" << displayInfo.width << " height:" << displayInfo.height << " orientation:" << displayInfo.orientation << endl;
    }
}

void Layout_tick_UI(bool *main_thread_flag)
{
    static bool show_draw_Line = false;
    static bool show_demo_window = false;
    static bool show_another_window = false;
    {

        ImGui::Begin("帝尊绘制", main_thread_flag);
        if (::permeate_record_ini)
        {
            ImGui::SetWindowPos({LastCoordinate.Pos_x, LastCoordinate.Pos_y});
            ImGui::SetWindowSize({LastCoordinate.Size_x, LastCoordinate.Size_y});
            permeate_record_ini = false;
        }

        ImGui::Text("默认功能全开，开关自己写(懒...)");

        ImGui::SliderInt("每帧遍历次数", &MaxCount, 5, 30);

        if (ImGui::Button("初始化"))
        {
            init_esp(::abs_ScreenX / 2, ::abs_ScreenY / 2);
        }
        
        if (ImGui::Button("截屏"))
        {
            system("screencap -p /sdcard/screenshot.png");
        }

        if (ImGui::Checkbox("过录制", &::permeate_record))
        {
            ::permeate_record_ini = true;
        }

        draw_esp();

        ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "应用平均 %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        g_window = ImGui::GetCurrentWindow();
        ImGui::End();
    }

    if (show_demo_window)
    {
        ImGui::ShowDemoWindow(&show_demo_window);
    }

    if (show_draw_Line)
        ImGui::GetForegroundDrawList()->AddLine(ImVec2(0, 0), ImVec2(displayInfo.width, displayInfo.height), IM_COL32(255, 0, 0, 255), 4);
}
