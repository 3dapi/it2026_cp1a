#pragma once
#include <vector>
#include "Scene.h"
#include "Button.h"

using std::vector;

class SceneGameBegin : public Scene
{
public:
	int Init() override;
	int Update(float deltaTime) override;
	int Destroy() override;
	int Render() override;

private:
	void SelectButton(Button* button);

private:
	int m_txBg{ -1 };
	int m_txTitle{ -1 };
	int m_font{ -1 };
	int m_selectedIndex{};

	Button m_startButton;
	Button m_exitButton;

	Button* m_selectedButton{};

	vector<Button*> buttons{};
};

