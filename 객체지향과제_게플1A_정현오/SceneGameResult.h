#pragma once
#include <vector>
#include "Scene.h"
#include "Button.h"

using std::vector;

class SceneGameResult : public Scene
{
public:
	int Init() override;
	int Update(float deltaTime) override;
	int Destroy() override;
	int Render() override;

public:
	void SetScore(int value);

private:
	void SelectButton(Button* button);

protected:
	int m_txBg{ -1 };
	int m_txResultBg{ -1 };
	int m_gameOverFont{ -1 };
	int m_scoreFont{ -1 };

	int m_selectedIndex{};

	Button m_retryButton;
	Button m_returnButton;

	Button* m_selectedButton{};

	vector<Button*> buttons{};

	int score{};
	LONG startX{};
};

