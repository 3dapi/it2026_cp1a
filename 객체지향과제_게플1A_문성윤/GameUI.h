#pragma once
#include <glc2d.h>

// All scene coordinates use the design's 1920 x 1440 canvas.
class GameUI
{
  public:
    int Init();
    void Destroy();
    void Update();
    void PlaySelect() const;

    bool Pressed(int key) const
    {
        return m_pressed[key];
    }

    bool Advance() const
    {
        return Pressed(VK_RETURN) || Pressed(VK_SPACE);
    }

    bool Hit(const RECT &rect) const;

    bool Clicked(const RECT &rect) const
    {
        return Pressed(VK_LBUTTON) && Hit(rect);
    }

    void Image(int texture, float x, float y, float width, float height, DWORD color = 0xFFFFFFFF) const;
    void Panel(const RECT &rect, DWORD color) const;
    void Text(const char *text, const RECT &rect, int size = 1, DWORD color = 0xFFF2EEE7) const;
    void Button(const char *label, const RECT &rect) const;

  private:
    static LRESULT CALLBACK WindowProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam);
    static GameUI *s_active;
    WNDPROC m_previousProc = nullptr;
    bool m_pending[256]{};
    bool m_pressed[256]{};
    POINT m_mouse{};
    int m_pixel = -1;
    int m_selectSound = -1;
    int m_fonts[3]{-1, -1, -1};
};
