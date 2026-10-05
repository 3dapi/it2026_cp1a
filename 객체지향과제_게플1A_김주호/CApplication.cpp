#include "CApplication.h"
#include "glc2d.h"

#include <cstdio>

namespace
{
	enum WindowSetting
	{
		WINDOW_WIDTH = 1672,
		WINDOW_HEIGHT = 941
	};

	enum CardSetting
	{
		FIRST_CARD_KEY = 1,
		LAST_CARD_KEY = 52,
		CARDS_PER_SUIT = 13,
		LAST_AVAILABLE_NUMBER = 10,

		CARD_SCALE = 4,
		CARD_WIDTH = 35 * CARD_SCALE,
		CARD_GAP = 20,
		DEALER_CARD_Y = 180,
		PLAYER_CARD_Y = 600
	};

	bool IsNewKeyPress(
		const KEYCODE* keyboard,
		int key,
		bool wasPressed)
	{
		return keyboard[key] != 0 && !wasPressed;
	}

	int GetCardNumberFromKey(int key)
	{
		return (key - 1) % CARDS_PER_SUIT + 1;
	}

	bool HasCardImage(int key)
	{
		return GetCardNumberFromKey(key) <= LAST_AVAILABLE_NUMBER;
	}

	int GetAvailableImageKey(int cardKey)
	{
		const int cardNumber = GetCardNumberFromKey(cardKey);

		if (cardNumber <= LAST_AVAILABLE_NUMBER)
		{
			return cardKey;
		}

		return cardKey - (cardNumber - LAST_AVAILABLE_NUMBER);
	}

	float GetHandStartX(std::size_t cardCount)
	{
		if (cardCount == 0)
		{
			return WINDOW_WIDTH * 0.5f;
		}

		const float cardSpacing = CARD_WIDTH + CARD_GAP;
		const float handWidth =
			CARD_WIDTH + (cardCount - 1) * cardSpacing;

		return (WINDOW_WIDTH - handWidth) * 0.5f;
	}
}

CApplication g_app;

int AppUpdate()
{
	return g_app.Update();
}

int AppRender()
{
	return g_app.Render();
}

int CApplication::Init()
{
	g2_InitSdk();
	g2_CreateWin(
		0,
		0,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		"Blackjack");

	g2_SetFrameMove(AppUpdate);
	g2_SetRender(AppRender);

	LoadTextures();
	LoadSounds();
	g_gameManager.Init(1000);

	printf("Blackjack started.\n");
	return 0;
}

int CApplication::Update()
{
	HandleInput();
	UpdateWindowTitle();

	return 0;
}

int CApplication::Render()
{
	if (tableTexture >= 0)
	{
		g2_Draw2D(tableTexture, nullptr);
	}

	DrawHand(
		g_gameManager.GetDealerHand(),
		DEALER_CARD_Y,
		g_gameManager.IsDealerCardHidden());

	DrawHand(
		g_gameManager.GetPlayerHand(),
		PLAYER_CARD_Y,
		false);

	return 0;
}

int CApplication::Destroy()
{
	ReleaseSounds();
	ReleaseTextures();
	g2_DestroyWin();

	return 0;
}

void CApplication::LoadTextures()
{
	for (int& texture : cardTextures)
	{
		texture = -1;
	}

	tableTexture = g2_TextureLoad("resource/Table.png");
	backTexture = g2_TextureLoad("resource/cards/back.png");

	for (int key = FIRST_CARD_KEY; key <= LAST_CARD_KEY; ++key)
	{
		if (!HasCardImage(key))
		{
			continue;
		}

		char filePath[64] = {};
		sprintf_s(filePath, "resource/cards/%d.png", key);

		cardTextures[key] = g2_TextureLoad(filePath);
	}
}

void CApplication::ReleaseTextures()
{
	for (int& texture : cardTextures)
	{
		if (texture < 0)
		{
			continue;
		}

		g2_TextureRelease(texture);
		texture = -1;
	}

	if (backTexture >= 0)
	{
		g2_TextureRelease(backTexture);
		backTexture = -1;
	}

	if (tableTexture >= 0)
	{
		g2_TextureRelease(tableTexture);
		tableTexture = -1;
	}
}

void CApplication::LoadSounds()
{
	cardSound = g2_SoundLoad("resource/sounds/card.wav");
	bgmSound = g2_SoundLoad("resource/sounds/casino_jazz.mp3");

	if (bgmSound >= 0)
	{
		g2_SoundPlay(bgmSound, true);
	}
}

void CApplication::ReleaseSounds()
{
	if (cardSound >= 0)
	{
		g2_SoundRelease(cardSound);
		cardSound = -1;
	}

	if (bgmSound >= 0)
	{
		g2_SoundRelease(bgmSound);
		bgmSound = -1;
	}
}

void CApplication::PlayCardSound()
{
	if (cardSound < 0)
	{
		return;
	}

	g2_SoundReset(cardSound);
	g2_SoundPlay(cardSound);
}

void CApplication::HandleInput()
{
	const KEYCODE* keyboard = g2_GetKeyboard();

	if (keyboard == nullptr)
	{
		return;
	}

	const bool betKey = keyboard['1'] != 0;
	const bool DoublebetKey = keyboard['2'] != 0;
	const bool fourfoldbetKey = keyboard['3'] != 0;
	const bool AllInbetKey = keyboard['A'] != 0;
	const bool hitKey = keyboard['H'] != 0;
	const bool standKey = keyboard['S'] != 0;
	const bool restartKey = keyboard['R'] != 0;

	if (IsNewKeyPress(keyboard, '1', previousBetKey))
	{
		const int amount = 100;
		if (g_gameManager.PlayerBet(amount))
		{
			PlayCardSound();
		}
	}
	if(IsNewKeyPress(keyboard, '2', previousBetKey))
	{
		const int amount = 200;
		if (g_gameManager.PlayerBet(amount))
		{
			PlayCardSound();
		}
	}
	if(IsNewKeyPress(keyboard, '3', previousBetKey))
	{
		const int amount = 400;
		if (g_gameManager.PlayerBet(amount))
		{
			PlayCardSound();
		}
	}
	if(IsNewKeyPress(keyboard, 'A', previousBetKey))
	{
		const int amount = g_gameManager.GetPlayerCash();
		if (g_gameManager.PlayerBet(amount))
		{
			PlayCardSound();
		}
	}
	if (IsNewKeyPress(keyboard, 'H', previousHitKey))
	{
		if (g_gameManager.PlayerHit())
		{
			PlayCardSound();
		}
	}

	if (IsNewKeyPress(keyboard, 'S', previousStandKey))
	{
		const std::size_t dealerCardCount =
			g_gameManager.GetDealerHand().size();

		if (g_gameManager.PlayerStand() &&
			g_gameManager.GetDealerHand().size() > dealerCardCount)
		{
			PlayCardSound();
		}
	}

	const bool canRestart =
		g_gameManager.GetGameState() == GameState::GameOver;

	if (canRestart &&
		IsNewKeyPress(keyboard, 'R', previousRestartKey))
	{
		g_gameManager.RestartGame();
	}

	previousBetKey = betKey;
	previousHitKey = hitKey;
	previousStandKey = standKey;
	previousRestartKey = restartKey;
}

void CApplication::UpdateWindowTitle()
{
	const int playerCash = g_gameManager.GetPlayerCash();
	const int currentBet = g_gameManager.GetCurrentBet();
	const int playerScore = g_gameManager.GetPlayerScore();

	if (g_gameManager.IsDealerCardHidden())
	{
		g2_SetWindowTitle(
			"Blackjack | Cash: %d | Bet: %d | Player: %d | Dealer: ? | [1] Bet 100 | [2] Bet 200 | [3] Bet 400 | [A] All In | [H] Hit [S] Stand [R] Next Round",
			playerCash,
			currentBet,
			playerScore);
		return;
	}

	g2_SetWindowTitle(
		"Blackjack | Cash: %d | Bet: %d | Player: %d | Dealer: %d | [1] Bet 100 | [2] Bet 200 | [3] Bet 400 | [A] All In | [H] Hit [S] Stand [R] Next Round",
		playerCash,
		currentBet,
		playerScore,
		g_gameManager.GetDealerScore());
}

void CApplication::DrawHand(
	const std::vector<Card>& hand,
	float y,
	bool hideSecondCard)

	//진짜 랜더링 모르겠어서 이건 gpt 도움을 받았습니다 진짜 죄송합니다 살려주세요 진짜 모르겠어요.
{
	const float cardSpacing = CARD_WIDTH + CARD_GAP;
	const float startX = GetHandStartX(hand.size());
	const VEC2 scale(CARD_SCALE, CARD_SCALE);

	for (std::size_t index = 0; index < hand.size(); ++index)
	{
		const bool isHiddenCard = hideSecondCard && index == 1;
		const int texture = GetCardTexture(
			hand[index],
			isHiddenCard);

		if (texture < 0)
		{
			continue;
		}

		const float x = startX + index * cardSpacing;
		const VEC2 position(x, y);

		g2_Draw2D(texture, nullptr, &position, &scale);
	}
}

int CApplication::GetCardTexture(
	const Card& card,
	bool useBackTexture) const
{
	if (useBackTexture)
	{
		return backTexture;
	}

	const int imageKey = GetAvailableImageKey(card.key);
	return cardTextures[imageKey];
}

int CApplication::Initsdk()
{
	return 0;
}
