#include "GameUI.h"

int GameUI::Init()
{
    m_pixel = g2_TextureLoad("resource/ui/white.png", 0);
    m_selectSound = g2_SoundLoad("resource/sound/se_select.mp3");
    if (m_selectSound < 0)
        return -1;
    const int sizes[] = {28, 38, 96};
    for (int i = 0; i < 3; ++i)
    {
        m_fonts[i] = g2_FontCreate("A2Z 6 SemiBold", sizes[i] * g2_GetScnH() / 1440);
        if (m_fonts[i] < 0)
            return -1;
    }
    if (m_pixel < 0)
        return -1;
    s_active = this;
    m_previousProc =
        reinterpret_cast<WNDPROC>(SetWindowLongPtr(g2_GetHwnd(), GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(WindowProc)));
    return m_previousProc ? 0 : -1;
}

void GameUI::Destroy()
{
    if (m_selectSound >= 0)
    {
        g2_SoundStop(m_selectSound);
        g2_SoundRelease(m_selectSound);
        m_selectSound = -1;
    }
    if (m_previousProc && IsWindow(g2_GetHwnd()))
        SetWindowLongPtr(g2_GetHwnd(), GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(m_previousProc));
    m_previousProc = nullptr;
    s_active = nullptr;
    if (m_pixel >= 0)
        g2_TextureRelease(m_pixel);
    m_pixel = -1;
}

void GameUI::PlaySelect() const
{
    if (m_selectSound >= 0)
    {
        g2_SoundStop(m_selectSound);
        g2_SoundPlay(m_selectSound);
    }
}

void GameUI::Update()
{
    for (int key = 0; key < 256; ++key)
    {
        m_pressed[key] = m_pending[key];
        m_pending[key] = false;
    }
    GetCursorPos(&m_mouse);
    ScreenToClient(g2_GetHwnd(), &m_mouse);
    RECT client{};
    GetClientRect(g2_GetHwnd(), &client);
    if (client.right > 0 && client.bottom > 0)
    {
        m_mouse.x = m_mouse.x * 1920 / client.right;
        m_mouse.y = m_mouse.y * 1440 / client.bottom;
    }
}

bool GameUI::Hit(const RECT &r) const
{
    return m_mouse.x >= r.left && m_mouse.x < r.right && m_mouse.y >= r.top && m_mouse.y < r.bottom;
}

void GameUI::Image(int texture, float x, float y, float width, float height, DWORD color) const
{
    if (texture < 0)
        return;
    float sx = g2_GetScnW() / 1920.0f, sy = g2_GetScnH() / 1440.0f;
    VEC2 position(x * sx, y * sy);
    VEC2 scale(width * sx / g2_TextureWidth(texture), height * sy / g2_TextureHeight(texture));
    g2_Draw2D(texture, nullptr, &position, &scale, nullptr, 0, color);
}

void GameUI::Panel(const RECT &r, DWORD color) const
{
    Image(m_pixel, float(r.left), float(r.top), float(r.right - r.left), float(r.bottom - r.top), color);
}

void GameUI::Text(const char *text, const RECT &r, int size, DWORD color) const
{
    RECT scaled{r.left * g2_GetScnW() / 1920, r.top * g2_GetScnH() / 1440, r.right * g2_GetScnW() / 1920,
                r.bottom * g2_GetScnH() / 1440};
    g2_FontDrawText(m_fonts[size], scaled, color, "%s", text);
}

void GameUI::Button(const char *label, const RECT &r) const
{
    Panel(r, Hit(r) ? 0xEE456074 : 0xE51A2939);
    Panel({r.left, r.top, r.left + 5, r.bottom}, 0xFFD4BB86);
    Text(label, {r.left + 30, r.top + 22, r.right - 16, r.bottom - 8});
}

GameUI *GameUI::s_active = nullptr;

LRESULT CALLBACK GameUI::WindowProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
    GameUI &ui = *s_active;
    // Capture short presses between frames; ignore OS keyboard auto-repeat.
    if (message == WM_KEYDOWN && wParam < 256 && !(lParam & (1LL << 30)))
        ui.m_pending[wParam] = true;
    if (message == WM_LBUTTONDOWN)
        ui.m_pending[VK_LBUTTON] = true;
    if (message == WM_KILLFOCUS)
        for (bool &key : ui.m_pending)
            key = false;
    return CallWindowProc(ui.m_previousProc, window, message, wParam, lParam);
}
