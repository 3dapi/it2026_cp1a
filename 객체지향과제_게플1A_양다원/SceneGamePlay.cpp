#include "SceneGamePlay.h"
#include "glc2d.h"
#include "TexturePath.h"
#include "CApplication.h"

#include "stdio.h"


int SceneGamePlay::Init()
{
	player = new Player();
	enemy = new Slime();
	pKeyboard = g2_GetKeyboard();
	printf("생성됨");
	TextureLoad();
	_playTime = 0.0f;
	_isWin = false;

	return 0;
}
int SceneGamePlay::Update(CApplication& cApp)
{
	player->DeltaTime();
	// ESC
	if (pKeyboard[VK_ESCAPE] == EINPUT_DOWN)
	{
		_isInputEsc = !_isInputEsc;
	}

	if (_isInputEsc)
	{
		g2_SoundStop(texture.battleSound);
		if (cApp.InputMouse(gameReplayPos) == TRUE)
		{
			printf("재시작 선택\n");
			g2_SoundPlay(texture.startSound);
			if (!g2_SoundIsPlaying(texture.startSound))
			{
				printf("효과음 종료, 씬 전환 시도\n");
				// 효과음 종료 후 씬 전환
				Destroy();
				Init();
				_isInputEsc = false;
			}
		}
		else if (cApp.InputMouse(gameExitPos) == TRUE)
		{
			printf("게임종료 선택");
			cApp.Destroy();
			return 0;
		}

		return 0;
	}

	g2_SoundPlay(texture.battleSound, true);
	_playTime += player->GetDeltaTime();

	//커서이동
	player->CursorMOve(player->GetDeltaTime());
	
	// 스페이스 입력 받았을 시 공격 로직 시작
	if (InputSpace()&& !g2_SoundIsPlaying(texture.attackSound))
	{		
		CombatManager(enemy);

		if (player->Die() || _isWin)
		{
			cApp.Outcome(_isWin, _playTime);
			// 씬 전환
			printf("%d\n", cApp.GetScene());
			cApp.ChangeScene(GAMEOVER);
			printf("씬변경, %d\n", cApp.GetScene());
			return 0;
		}
	}

	//전투
	//

	

	return 0;
}
int SceneGamePlay::Render()
{
	g2_Draw2D(texture.backgroundTexture, NULL);
	g2_Draw2D(texture.gaugeTexture, NULL, &player->gaugePosition); //이름, 이미지사용, 생성위치

	g2_Draw2D(texture.cursorTexture, NULL, &player->cursorPosition);

	//조건따른 몬스터 그리기
	ChangeEnemy(enemy);	

	//hp바 표시
	g2_FontDrawText(combatFont, playerHp, 0xFFFFFFFF, "HP : %d", player->GetHP());
	g2_FontDrawText(combatFont, enemy->GetStage()!=4 ? enemyHp : bossHp, 0xFFFFFFFF
		, "%d / %d", enemy->GetHp(), enemy->GetMaxHp());
	//라운드 표시
	g2_FontDrawText(combatFont, stagePos, 0xFFFFFFFF, "STAGE %d / %d", enemy->GetStage(), enemy->GetMaxStage());
	// 나가기
	if (_isInputEsc)
	{		
		//검은 창
		g2_Draw2D(texture.escwindowTexture, NULL, &escScreenPos);
		//다시시작
		g2_FontDrawText(escButton, gameReplayPos, 0xFFFFFFFF, "다시 하기");
		//게임 종료
		g2_FontDrawText(escButton, gameExitPos, 0xFFFFFFFF, "게임 종료");
	}

	return 0;
}
int SceneGamePlay::Destroy()
{
	g2_SoundStop(texture.battleSound);
	TextureRelease();

	if (player != nullptr)
	{
		delete player;
		player = nullptr;
	}
	if (enemy != nullptr)
	{
		delete enemy;
		enemy = nullptr;
	}

	return 0;
}

bool SceneGamePlay::InputSpace()
{
	if (pKeyboard[VK_SPACE] == EINPUT_DOWN)
	{
		printf("키보드 입력");
		// 커서 위치 저장
		s_cursorX = player->cursorPosition.x;
		return TRUE;
	}
	return FALSE;
}

void SceneGamePlay::Battle(Enemy* _enemy)
{
	//공격사운드 재생 및 판정결과출력
	g2_SoundPlay(texture.attackSound);
	player->Attack(s_cursorX, *_enemy);
	printf("적의 남은 체력 : %d\n", _enemy->GetHp());
	
	//적이 죽었을 경우
	if (_enemy->Die())
	{
		//적제거, 다음 라운드 적 생성, 플레이어 수치 초기화, 보스 처치 시 클리어
		ChangeStage(_enemy);
		printf("적을 처치했다\n");
		return;
	}

	_enemy->Attack(*player);
	printf("플레이어의 남은 체력 : %d\n", player->GetHP());

	//플레이어가 죽었을 경우
	if (player->Die())
	{
		printf("플레이어가 사망했습니다\n");
		_isWin = false;
		return;
	}
}
void SceneGamePlay::ChangeStage(Enemy* _enemy)
{
	stage = _enemy->GetStage();
	nextStage = stage + 1;

	switch (nextStage)
	{
	case(2):
		delete(_enemy);
		enemy = new Goblin;
		player->SetHP(5);
		player->SetSpeed(1200);
		break;

	case(3):
		delete(_enemy);
		enemy = new Orc;
		player->SetHP(5);
		player->SetSpeed(1500);
		break;

	case(4):
		delete(_enemy);
		enemy = new Dragon;
		player->SetHP(5);
		player->SetSpeed(1800);
		break;
		
	case(5):
		BossClear();
		break;
	default:
		break;
	}	
}
void SceneGamePlay::BossClear()
{
	_isWin = true;
}
void SceneGamePlay::BossCombat(Enemy* _enemy)
{
	if (_enemy->GetHp() <= 25 && _enemy->GetHp() > 15) player->SetSpeed(2100);
	else if (_enemy->GetHp() <= 15 && _enemy->GetHp() > 5) player->SetSpeed(2500);
	else if (_enemy->GetHp() <= 5) player->SetSpeed(3000);

	if (!player->MissRange(s_cursorX))
	{
		g2_SoundPlay(texture.attackSound);
		player->Attack(s_cursorX, *_enemy);
		printf("적의 남은 체력 : %d\n", _enemy->GetHp());

		//적이 죽었을 경우
		if (_enemy->Die())
		{
			//적제거, 다음 라운드 적 생성, 플레이어 수치 초기화, 보스 처치 시 클리어
			ChangeStage(_enemy);
			printf("적을 처치했다\n");
			return;
		}
	}
	else
	{
		g2_SoundPlay(texture.damageSound);
		printf("공격 미스\n");

		_enemy->Attack(*player);
		printf("플레이어의 남은 체력 : %d\n", player->GetHP());
	
		//플레이어가 죽었을 경우
		if (player->Die())
		{
			printf("플레이어가 사망했습니다\n");
			_isWin = false;
			return;
		}
	}
}
void SceneGamePlay::EnemyTakeDamage(Enemy* _enemy)
{
	//데미지 받을 시 좌우 흔들
}
void SceneGamePlay::CombatManager(Enemy* _enemy)
{
	if (_enemy->GetStage() != 4) Battle(_enemy);
	else BossCombat(_enemy);
}
void SceneGamePlay::ChangeEnemy(Enemy* _enemy)
{
	stage = _enemy->GetStage();
	enemyPos = _enemy->GetPos();

	switch (stage)
	{
	case(1):
		g2_Draw2D(texture.slimeTexture, NULL, &enemyPos);
		break;

	case(2):		
		g2_Draw2D(texture.goblinTexture, NULL, &enemyPos);
		break;

	case(3):
		g2_Draw2D(texture.orcTexture, NULL, &enemyPos);
		break;

	case(4):
		g2_Draw2D(texture.dragonTexture, NULL, &enemyPos);

	default:
		break;
	}

}
void SceneGamePlay::TextureLoad()
{
	//그림
	texture.backgroundTexture = g2_TextureLoad(TX_BACKGROUND);
	texture.gaugeTexture = g2_TextureLoad(TX_GAUGE);
	texture.cursorTexture = g2_TextureLoad(TX_CURSOR);
	texture.escwindowTexture = g2_TextureLoad(TX_ESC);

	texture.slimeTexture = g2_TextureLoad(TX_SLIME);
	texture.goblinTexture = g2_TextureLoad(TX_GOBLIN);
	texture.orcTexture = g2_TextureLoad(TX_ORC);
	texture.dragonTexture = g2_TextureLoad(TX_DRAGON);

	//문자열
	combatFont = g2_FontCreate("굴림", 50, 0);
	attackFont = g2_FontCreate("굴림", 70, 1);
	escButton = g2_FontCreate("굴림", 50, 0);

	//사운드
	texture.startSound = g2_SoundLoad(VFX_START);
	texture.battleSound = g2_SoundLoad(VFX_BGM);
	texture.attackSound = g2_SoundLoad(VFX_ATTACK);
	texture.damageSound = g2_SoundLoad(VFX_TAKEDAMAGE);
}
void SceneGamePlay::TextureRelease()
{
	g2_TextureRelease(texture.backgroundTexture);
	g2_TextureRelease(texture.gaugeTexture);
	g2_TextureRelease(texture.cursorTexture);
	g2_TextureRelease(texture.escwindowTexture);

	g2_TextureRelease(texture.slimeTexture);
	g2_TextureRelease(texture.goblinTexture);
	g2_TextureRelease(texture.orcTexture);
	g2_TextureRelease(texture.dragonTexture);

	g2_SoundRelease(texture.startSound);
	g2_SoundRelease(texture.battleSound);
	g2_SoundRelease(texture.attackSound);
	g2_SoundRelease(texture.damageSound);
}