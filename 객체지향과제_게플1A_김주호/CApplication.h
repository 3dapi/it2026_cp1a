#pragma once
#include "TableGameManager.h"
class CApplication
{

public:
	int Init();
	int Update();
	int Render();
	int Destroy();

protected:
	int Initsdk();

private:
	// 게임에 사용하는 테이블과 카드 텍스처를 준비하고 정리한다.
	void LoadTextures();
	void ReleaseTextures();
	void LoadSounds();
	void ReleaseSounds();
	void PlayCardSound();

	// 키보드 입력을 처리하고 현재 게임 정보를 창 제목에 표시한다.
	void HandleInput();
	void UpdateWindowTitle();

	// 한쪽의 카드 패를 지정한 높이에 차례대로 그린다.
	void DrawHand(
		const std::vector<Card>& hand,
		float y,
		bool hideSecondCard);

	// 카드 뒷면 표시 여부와 카드 번호에 맞는 텍스처를 반환한다.
	int GetCardTexture(
		const Card& card,
		bool useBackTexture) const;

	int tableTexture = -1;
	int cardTextures[53] = {};
	int backTexture = -1;
	int cardSound = -1;
	int bgmSound = -1;

	bool previousBetKey = false;
	bool previousHitKey = false;
	bool previousStandKey = false;
	bool previousRestartKey = false;
};

int AppUpdate();
int AppRender();
