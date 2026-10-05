#include "SceneBattle.h"
#include "Window.h"
#include "WindowImage.h"
#include "Battle/Battle.h"
#include "Battle/Character.h"
#include "Battle/Dice.h"

void SceneBattle::Initialize()
{
	InitializeImageLoad();

	InitializeObject();
}

void SceneBattle::InitializeImageLoad()
{
	m_background = g2_TextureLoad("Resources/Textures/Background/background.png");

	m_iconNone= g2_TextureLoad("Resources/Textures/UI/Icon_None.png");
	m_iconNone2= g2_TextureLoad("Resources/Textures/UI/Icon_None.png");
	m_iconAttack = g2_TextureLoad("Resources/Textures/UI/Icon_attack.png");
	m_iconAvoid = g2_TextureLoad("Resources/Textures/UI/Icon_avoid.png");
	m_iconGuard = g2_TextureLoad("Resources/Textures/UI/Icon_guard.png");

	m_playerAttack = g2_TextureLoad("Resources/Textures/Player/player_attack.png");
	m_playerAvoid = g2_TextureLoad("Resources/Textures/Player/player_avoid.png");
	m_playerCorpse = g2_TextureLoad("Resources/Textures/Player/player_corpse.png");
	m_playerGuard = g2_TextureLoad("Resources/Textures/Player/player_guard.png");
	m_playerIdle = g2_TextureLoad("Resources/Textures/Player/player_idle.png");

	m_enemyAttack = g2_TextureLoad("Resources/Textures/Enemy/Enemy_attack.png");
	m_enemyAvoid = g2_TextureLoad("Resources/Textures/Enemy/Enemy_avoid.png");
	m_enemyCorpse = g2_TextureLoad("Resources/Textures/Enemy/Enemy_corpse.png");
	m_enemyGuard = g2_TextureLoad("Resources/Textures/Enemy/Enemy_guard.png");
	m_enemyIdle = g2_TextureLoad("Resources/Textures/Enemy/Enemy_idle.png");
}

void SceneBattle::InitializeObject()
{
	m_dice.DiceSetup();
	m_player.SetSetupStandard("Player", &m_dice, 3);
	m_enemy.SetSetupStandard("Enemy", &m_dice, 3);
	m_battle.Setup(&m_player, &m_enemy);

	m_backgroundObject.Initialize(m_background, 0, 0);
	m_playerObject.Initialize(m_playerIdle, WINDOWX/8, WINDOWY/8*5);
	m_enemyObject.Initialize(m_enemyIdle, WINDOWX/8*5, WINDOWY/8*5);
	m_playerActionObject.Initialize(m_iconNone, WINDOWX / 8, WINDOWY / 4);
	m_enemyActionObject.Initialize(m_iconNone2, WINDOWX / 8, WINDOWY / 4);

}
