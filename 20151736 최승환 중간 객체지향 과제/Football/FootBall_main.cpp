/////////////////////////////////////////////////////////////
//Е獐 啪歜 偌羹雖щ Щ煎斜楚墅
//濛撩濠 : 譆蝓��
//1 瞪羹瞳檣 啪歜掘褻 贗楚蝶��
//2 Point贗楚蝶蒂 檜辨и 螃粽薛お曖 贗楚蝶��
//3 蝶纔檜雖 薑爾諦 啪歜 褫暮 婦葬ж朝 滲熱菟擊 贗楚蝶��
/////////////////////////////////////////////////////////////

#pragma region ④渦だ橾

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#include <time.h>
//#include <fmod.h>
#include <windows.h>

#pragma endregion

#pragma region 顫殮貲 摹樹 塽 瞪羲 滲熱

#define MAX_STAGE_ 2

//////

typedef enum _GAME_STATE { INIT, READY, RUNNING, STOP, SUCCESS, FAILED, RESULT } GAME_STATE;

class EFFECT
{
public:
	clock_t StratTime; // �膩� 嫦儅 衛陝
	clock_t StayTime;  // �膩� 雖樓 衛除	
};


class STAGE_OPTION
{
public:
	char g_strPlayer[11];
	int g_nLength, g_nGoal, g_nBallCount, g_nGoalBallCount, g_nStage , g_nIsGoal;
	clock_t g_LimitTime, g_GameStartTime, g_UpdateOldTime;


	STAGE_OPTION::STAGE_OPTION()
	{
		g_nStage = -1;
		strcpy(g_strPlayer,"曲收≒收旭");
	}
};

#pragma region 蝶纔檜雖 檣ん 贗楚蝶

class STAGE_INFO_CLASS
{
public:
	int nGoalBall;			// 埤檣п撿 й 獐曖 偃熱 
	clock_t LimitTime;      // 薯и 衛除 
	int nGoalDaeLength;		// 埤渠 望檜 
	int nGoalDaeX;			// 埤渠 檜翕 X 謝ル
	int nGoalDaeY;			// 埤渠 檜翕 Y 謝ル 
	clock_t MoveTime;		// 埤渠 檜翕 衛除 除問
	int nDist;				// 埤渠 檜翕 剪葬

	static GAME_STATE g_GameState;

	void Set_Info(int GoalBall, clock_t LT, int GoalDaeLength,int GoalDaeX, int GoalDaeY,clock_t MT,int Dist);
};

GAME_STATE STAGE_INFO_CLASS::g_GameState = INIT;

void STAGE_INFO_CLASS::Set_Info(int GoalBall, clock_t LT, int GoalDaeLength,int GoalDaeX, int GoalDaeY,clock_t MT,int Dist)
{
	nGoalBall = GoalBall;	
	LimitTime = LT; 
	nGoalDaeLength = GoalDaeLength;	
	nGoalDaeX = GoalDaeX;
	nGoalDaeY = GoalDaeY;	 
	MoveTime = MT;
	nDist = Dist;
}

STAGE_INFO_CLASS g_sStageInfo[MAX_STAGE_];

STAGE_OPTION g_Opt;

#pragma endregion

//FMOD_SYSTEM *g_System;  // FMOD system 滲熱摹樹
//FMOD_SOUND  *g_Sound[7];          // 寡唳 擠學                       �膩� 擠學 
//char        *g_strFileName[7] = { "init.wav", "run.wav", "fail.wav", "ready.wav", "success.wav", "shoot.wav", "wow.wav" };
//FMOD_CHANNEL *g_Channel[7];

#pragma endregion

#pragma region 螃粽薛お 婦溼 贗楚蝶

class Point
{
public:
	Point()
	{
		x=0;
		y=0;
	}
	int get_x()
	{
		return x;
	}
	int get_y()
	{
		return y;
	}
	void set_x(int ix)
	{
		x = ix;
	}
	void set_y(int iy)
	{
		y = iy;
	}
	void set_point(int ix, int iy)
	{
		x = ix;
		y = iy;
	}
	void plus_x(int px)
	{
		x += px;
	}
	void plus_y(int py)
	{
		y += py;
	}
	void plus_point(int px ,int py)
	{
		x += px;
		y += py;
	}

private:
	int x,y;
};

class PLAYER : public Point
{
public:
    int nCenterX, nCenterY;
	//int nMoveX, nMoveY;
	int nX, nY;
};
	
class BALL : public Point
{
public:
	int nIsReady;        // 遽綠 鼻鷓(1), 螂鼻鷓(0)
	//int nMoveX, nMoveY;  // 檜翕 謝ル
	clock_t MoveTime;    // 檜翕 衛除 除問
	clock_t OldTime;     // 檜瞪 檜翕 衛陝
};
	
class GOAL_DAE : public Point
{
public:
		//int nMoveX, nMoveY;     // 檜翕 謝ル 
		int nLength;			// 埤渠 望檜	
		int nLineX[7];			// 埤檣 塭檣 x 謝ル (7偃)
		clock_t	MoveTime;		// 檜翕 衛除 除問
		clock_t	OldTime;	    // 檜瞪 檜翕 衛除
		int	nDist;				// 檜翕 剪葬
};

#pragma endregion

#pragma region Screen 贗楚蝶

class Screen
{
public:
	static void ScreenInit();
	static void ScreenFlipping();
	static void ScreenClear();
	static void ScreenRelease();
	static void ScreenPrint( int x, int y, char *string );
	static void SetColor( unsigned short color );

	static void InitScreen();
	static void ReadyScreen();
	static void BackScreen();
	static void GoalMessage( int nX, int nY );
	static void SuccessScreen();
	static void FailureScreen();
	static void ResultScreen();

	static void Render(GOAL_DAE g_sGoalDae, BALL g_sBall, PLAYER g_sPlayer);
	
	static int g_nScreenIndex;
	static HANDLE g_hScreen[2];

private:
	friend class Football_Game;

};

//蝶鷓す 滲熱 蟾晦��
int Screen::g_nScreenIndex = 0;
HANDLE Screen::g_hScreen[2] = {NULL,NULL};

#pragma region Screen.c 犒稱-> Screen class 薑曖

//#include <windows.h>

//static int g_nScreenIndex;
//static HANDLE g_hScreen[2];

void Screen::ScreenInit()
{
	CONSOLE_CURSOR_INFO cci;
	
	// 陛鼻曖 夔樂璽 2偃瑙 虜萇棻.
	g_hScreen[0] = CreateConsoleScreenBuffer( GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL );
	g_hScreen[1] = CreateConsoleScreenBuffer( GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL );

	// 醴憮 獗晦晦
	cci.dwSize = 1;
	cci.bVisible = FALSE;
	SetConsoleCursorInfo( g_hScreen[0], &cci );
	SetConsoleCursorInfo( g_hScreen[1], &cci );
}

void Screen::ScreenFlipping()
{		
	Sleep( 10 );
	SetConsoleActiveScreenBuffer( g_hScreen[g_nScreenIndex] );	
	g_nScreenIndex = !g_nScreenIndex;	
}

void Screen::ScreenClear()
{		
	COORD Coor = { 0, 0 };
	DWORD dw;
	FillConsoleOutputCharacter( g_hScreen[g_nScreenIndex], ' ', 80*25, Coor, &dw );
}

void Screen::ScreenRelease()
{
	CloseHandle( g_hScreen[0] );
	CloseHandle( g_hScreen[1] );
}


void Screen::ScreenPrint( int x, int y, char *string )
{
	DWORD dw;
	COORD CursorPosition = { x, y };
	SetConsoleCursorPosition( g_hScreen[g_nScreenIndex], CursorPosition );	
	WriteFile( g_hScreen[g_nScreenIndex], string, strlen( string ), &dw, NULL );
}

// 1 ~ 15 梱雖 儀鼻 撲薑 陛棟
void Screen::SetColor( unsigned short color )
{		
	SetConsoleTextAttribute( g_hScreen[g_nScreenIndex], color );
}

#pragma endregion


void Screen::InitScreen()
{
	Screen::ScreenPrint( 0, 0, "旨收收收收收收收收收收收收收收收收收收收收收旬");
	Screen::ScreenPrint( 0, 1, "早                                          早");
	Screen::ScreenPrint( 0, 2, "早             ﹤收收收﹤                   早");
	Screen::ScreenPrint( 0, 3, "早                                          早");
	Screen::ScreenPrint( 0, 4, "早                        ///.   螂~~~      早");  
	Screen::ScreenPrint( 0, 5, "早                       (^.^)              早");    
	Screen::ScreenPrint( 0, 6, "早                      曲朽 曳旬           早");
	Screen::ScreenPrint( 0, 7, "早                         旨旭             早");
	Screen::ScreenPrint( 0, 8, "早                     Ⅸ  旭′             早");
	Screen::ScreenPrint( 0, 9, "早                                          早");
	Screen::ScreenPrint( 0,10, "早                                          早");
	Screen::ScreenPrint( 0,11, "早       螂 埤檣 啪歜  Go! Go!              早");
	Screen::ScreenPrint( 0,12, "早                                          早");	
	Screen::ScreenPrint( 0,13, "早                                          早");
	Screen::ScreenPrint( 0,14, "早       j :豭薹 l : 螃艇薹 k :螂           早");
	Screen::ScreenPrint( 0,15, "早                                          早");	
	Screen::ScreenPrint( 0,16, "早                                          早");
	Screen::ScreenPrint( 0,17, "早                                          早");
	Screen::ScreenPrint( 0,18, "早        曲≒旭  space 酈蒂 揚楝輿撮蹂     早");
	Screen::ScreenPrint( 0,19, "早                                          早");
	Screen::ScreenPrint( 0,20, "早                                          早");
	Screen::ScreenPrint( 0,21, "早                                          早");
	Screen::ScreenPrint( 0,22, "曲收收收收收收收收收收收收收收收收收收收收收旭");
}

void Screen::ReadyScreen()
{	
	char string[100];

	Screen::ScreenPrint( 0, 0, "旨收收收收收收收收收收收收收收收收收收收收收旬");
	Screen::ScreenPrint( 0, 1, "早﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥早");
	Screen::ScreenPrint( 0, 2, "早﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥早");
	Screen::ScreenPrint( 0, 3, "早﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥早");
	Screen::ScreenPrint( 0, 4, "早﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥早");
	Screen::ScreenPrint( 0, 5, "早﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥早");
	Screen::ScreenPrint( 0, 6, "早﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥早");
	Screen::ScreenPrint( 0, 7, "早﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥早");
	Screen::ScreenPrint( 0, 8, "早﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥早");
	Screen::ScreenPrint( 0, 9, "早﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥早");
	Screen::ScreenPrint( 0,10, "早﹥﹥﹥﹥﹥                    ﹥﹥﹥﹥﹥﹥早");
	sprintf( string, "早﹥﹥﹥﹥﹥     %d   蝶纔檜雖   ﹥﹥﹥﹥﹥﹥早", g_Opt.g_nStage + 1);
	Screen::ScreenPrint( 0,11, string);
	Screen::ScreenPrint( 0,12, "早﹥﹥﹥﹥﹥                    ﹥﹥﹥﹥﹥﹥早");
	Screen::ScreenPrint( 0,13, "早﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥早");
	Screen::ScreenPrint( 0,14, "早﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥早");
	Screen::ScreenPrint( 0,15, "早﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥早");
	Screen::ScreenPrint( 0,16, "早﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥早");
	Screen::ScreenPrint( 0,17, "早﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥早");
	Screen::ScreenPrint( 0,18, "早﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥早");
	Screen::ScreenPrint( 0,19, "早﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥早");
	Screen::ScreenPrint( 0,20, "早﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥早");
	Screen::ScreenPrint( 0,21, "早﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥早");
	Screen::ScreenPrint( 0,22, "早﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥早");	
	Screen::ScreenPrint( 0,23, "曲收收收收收收收收收收收收收收收收收收收收收旭");
}

void Screen::BackScreen()
{	
	char string[100];

	Screen::ScreenPrint( 0, 0, "旨收收收收收收收收收收收收收收收收收收收收收旬");
	Screen::ScreenPrint( 0, 1, "早                                          早");
	Screen::ScreenPrint( 0, 2, "早                                          早");
	Screen::ScreenPrint( 0, 3, "早                                          早");
	sprintf( string,   "早                                          早蝶纔檜雖: %d", g_Opt.g_nStage + 1 );
	Screen::ScreenPrint( 0, 4, string );
	Screen::ScreenPrint( 0, 5, "早                                          早");
	sprintf( string,   "曳收收收收收收收收收收收收收收收收收收收收收朽薯и 衛除: %d", g_sStageInfo[g_Opt.g_nStage].LimitTime / 1000 );
	Screen::ScreenPrint( 0, 6, string );
	Screen::ScreenPrint( 0, 7, "早                                          早");
	sprintf( string,   "早                                          早⑷營 衛除: %d", ( clock() - g_Opt.g_GameStartTime ) / 1000 );
    Screen::ScreenPrint( 0, 8, string );
	Screen::ScreenPrint( 0, 9, "早                                          早");
	sprintf( string,   "早                                          早跡ル 埤檣: %d ", g_sStageInfo[g_Opt.g_nStage].nGoalBall );
	Screen::ScreenPrint( 0,10, string ); 
	Screen::ScreenPrint( 0,11, "早                                          早");
	sprintf( string,   "早                                          早埤檣 奢 偃熱: %d ", g_Opt.g_nBallCount );
	Screen::ScreenPrint( 0, 12, string );

	Screen::ScreenPrint( 0,13, "早                                          早");
	sprintf( string,   "早                                          早");
	Screen::ScreenPrint( 0, 14, string );
	Screen::ScreenPrint( 0,15, "早                                          早");
	sprintf( string,   "早                                          早");
	Screen::ScreenPrint( 0,16, string );
	Screen::ScreenPrint( 0,17, "早                                          早");
	Screen::ScreenPrint( 0,18, "早                                          早");
	Screen::ScreenPrint( 0,19, "早                                          早");
	Screen::ScreenPrint( 0,20, "早                                          早");
	Screen::ScreenPrint( 0,21, "早                                          早");
	Screen::ScreenPrint( 0,22, "早                                          早");
	Screen::ScreenPrint( 0,23, "曲收收收收收收收收收收收收收收收收收收收收收旭");
}

void Screen::GoalMessage( int nX, int nY )
{
     Screen::ScreenPrint( nX, nY,     "≧ )) 埤檣 (( ≠" );
     Screen::ScreenPrint( nX, nY + 1, "′(^^')/ ′(\"*')/" );
     Screen::ScreenPrint( nX, nY + 2, "   ﹥       ﹥");
     Screen::ScreenPrint( nX, nY + 3, "  戎忖    忙戌" );
}

void Screen::SuccessScreen()
{
	Screen::ScreenPrint( 0, 0, "旨收收收收收收收收收收收收收收收收收收收收收旬");
	Screen::ScreenPrint( 0, 1, "早                                          早");
	Screen::ScreenPrint( 0, 2, "早                                          早");
	Screen::ScreenPrint( 0, 3, "早                                          早");
	Screen::ScreenPrint( 0, 4, "早                                          早");
	Screen::ScreenPrint( 0, 5, "早                                          早");
	Screen::ScreenPrint( 0, 6, "早                ////′′                  早");
	Screen::ScreenPrint( 0, 7, "早               q ∥  ∥ p                 早");
	Screen::ScreenPrint( 0, 8, "早               (戌式式戎)                 早");
	Screen::ScreenPrint( 0, 9, "早             Ｏ 嘐暮 撩奢 Ｎ              早");
	Screen::ScreenPrint( 0,10, "早                                          早");
	Screen::ScreenPrint( 0,11, "早                                          早");
	Screen::ScreenPrint( 0,12, "早                                          早");
	Screen::ScreenPrint( 0,13, "早                                          早");
	Screen::ScreenPrint( 0,14, "早                                          早");
	Screen::ScreenPrint( 0,15, "早                                          早");
	Screen::ScreenPrint( 0,16, "早                                          早");
	Screen::ScreenPrint( 0,17, "早                                          早");
	Screen::ScreenPrint( 0,18, "早                                          早");
	Screen::ScreenPrint( 0,19, "早                                          早");
	Screen::ScreenPrint( 0,20, "早                                          早");
	Screen::ScreenPrint( 0,21, "早                                          早");
	Screen::ScreenPrint( 0,22, "早                                          早");
	Screen::ScreenPrint( 0,23, "曲收收收收收收收收收收收收收收收收收收收收收旭");		
}

void Screen::FailureScreen()
{	
	Screen::ScreenPrint( 0, 0, "旨收收收收收收收收收收收收收收收收收收收收收旬");
	Screen::ScreenPrint( 0, 1, "早                                          早");
	Screen::ScreenPrint( 0, 2, "早                                          早");
	Screen::ScreenPrint( 0, 3, "早                                          早");
	Screen::ScreenPrint( 0, 4, "早                                          早");
	Screen::ScreenPrint( 0, 5, "早                                          早");
	Screen::ScreenPrint( 0, 6, "早                                          早");
	Screen::ScreenPrint( 0, 7, "早                                          早");
	Screen::ScreenPrint( 0, 8, "早                                          早");
	Screen::ScreenPrint( 0, 9, "早                                          早");
	Screen::ScreenPrint( 0,10, "早                                          早");
	Screen::ScreenPrint( 0,11, "早                    嘐暮 褒ぬ !!!!        早");
	Screen::ScreenPrint( 0,12, "早                                          早");
	Screen::ScreenPrint( 0,13, "早                                          早");
	Screen::ScreenPrint( 0,14, "早                 ≒有收旬                 早");
	Screen::ScreenPrint( 0,15, "早                   旭  曲                 早");
	Screen::ScreenPrint( 0,16, "早                  ﹥﹥﹥﹥                早");
	Screen::ScreenPrint( 0,17, "早                                          早");
	Screen::ScreenPrint( 0,18, "早        棻衛 ж衛啊蝗棲梱? (y/n)          早");
	Screen::ScreenPrint( 0,19, "早                                          早");
	Screen::ScreenPrint( 0,20, "早                                          早");
	Screen::ScreenPrint( 0,21, "早                                          早");
	Screen::ScreenPrint( 0,22, "曲收收收收收收收收收收收收收收收收收收收收收旭");		
}

void Screen::ResultScreen()
{
	char string[100];
	Screen::ScreenPrint( 0, 0, "旨收收收收收收收收收收收收收收收收收收收收收旬");
	Screen::ScreenPrint( 0, 1, "早                                          早");
	Screen::ScreenPrint( 0, 2, "早                                          早");
	Screen::ScreenPrint( 0, 3, "早             ﹤收收收﹤                   早");
	Screen::ScreenPrint( 0, 4, "早                                          早");
	Screen::ScreenPrint( 0, 5, "早                                          早");
	Screen::ScreenPrint( 0, 6, "早                                          早");
	Screen::ScreenPrint( 0, 7, "早                                          早");
	sprintf( string,   "早      撩奢и 蝶纔檜雖 :  %2d               早", g_Opt.g_nStage + 1 );
	Screen::ScreenPrint( 0, 8, string );
	Screen::ScreenPrint( 0, 9, "早                                          早");
	Screen::ScreenPrint( 0,10, "早                                          早");
	Screen::ScreenPrint( 0,11, "早   ___〤〤〤___                           早");
	Screen::ScreenPrint( 0,12, "早     (*^  ^*)                             早");  
	Screen::ScreenPrint( 0,13, "早 =====∞==∞=====                         早");
	Screen::ScreenPrint( 0,14, "早                                          早");
	Screen::ScreenPrint( 0,15, "早                                          早");
	Screen::ScreenPrint( 0,16, "早                                          早");
	Screen::ScreenPrint( 0,17, "早                                          早");
	Screen::ScreenPrint( 0,18, "早                      曲≒旭              早");
	Screen::ScreenPrint( 0,19, "早                                          早");
	Screen::ScreenPrint( 0,20, "早                                          早");
	Screen::ScreenPrint( 0,21, "早                                          早");
	Screen::ScreenPrint( 0,22, "曲收收收收收收收收收收收收收收收收收收收收收旭");
}


void Screen::Render(GOAL_DAE g_sGoalDae, BALL g_sBall, PLAYER g_sPlayer)
{
	 char string[100] = { 0, };	 
	 int nLength, i;	

    Screen::ScreenClear();

	switch( g_sStageInfo->g_GameState )
	{
	case INIT:
			if( g_Opt.g_nStage == 0 )
				InitScreen();			
			break;
	case READY :
			ReadyScreen();			
			break;
	case RUNNING :
			 BackScreen();
			 Screen::ScreenPrint( g_sGoalDae.get_x(), g_sGoalDae.get_y(), "﹤" );
			 nLength = g_sGoalDae.nLength*2 + 1;

			 for( i = 0 ; i < nLength ; i++ )
				  Screen::ScreenPrint( g_sGoalDae.nLineX[i], g_sGoalDae.get_y(), "收");
			
			  Screen::ScreenPrint( g_sGoalDae.nLineX[nLength-1] + 2, g_sGoalDae.get_y(), "﹤"); 	

			 // Note: �膩� 轎溘  	
			 if( g_Opt.g_nIsGoal == 1 )
			 {
				GoalMessage( 10, 10 );
			 }	

			 // Note: 2 鏽歲噶 贗葬ё 
			 if( g_sPlayer.nX < 2 )  //  豭薹 贗葬ё 籀葬
				  Screen::ScreenPrint( 2, g_sPlayer.get_y(), &g_Opt.g_strPlayer[(g_sPlayer.nX-2)*-1]);	 // 謝ル蒂 寡翮 檣策蝶 
			 else if( g_sPlayer.get_x() + (g_Opt.g_nLength - g_sPlayer.nCenterX + 1) > 43 ) // 螃艇薹 贗葬ё 籀葬
			 {
				 strncat( string, g_Opt.g_strPlayer, g_Opt.g_nLength - (( g_sPlayer.get_x() + g_sPlayer.nCenterX + 1) - 43 ) );
				  Screen::ScreenPrint( g_sPlayer.nX, g_sPlayer.get_y(), string );		
			}else{ // 1 鏽歲噶 檜翕
				 Screen::ScreenPrint( g_sPlayer.nX, g_sPlayer.get_y(), g_Opt.g_strPlayer );
			}

			 Screen::ScreenPrint( g_sBall.get_x(), g_sBall.get_y(), "Ⅸ" );			
			break;
	case SUCCESS:
			SuccessScreen();
			break;
	case FAILED:
			FailureScreen();
			break;
	case RESULT:
			ResultScreen();
			break;
	}
	
	// Note: 溶渦葭 部 
	 Screen::ScreenFlipping();
}


#pragma endregion

#pragma region Football_Game 贗楚蝶 

class Football_Game
{
public:
	// л熱
	Football_Game();
	virtual void play();
	void Init();
	void Release();
	void Update();


private:             
	friend class Screen;
	//滲熱

	Screen Scr;
	EFFECT g_sEffect;

	GOAL_DAE g_sGoalDae;
	BALL g_sBall;
	PLAYER g_sPlayer;

};

Football_Game::Football_Game()
{
g_sStageInfo[0].Set_Info( 3, 1000*20, 1, 20, 3, 300, 1);
g_sStageInfo[1].Set_Info( 10, 1000*30, 2, 20, 5, 300, 1 );
                      
}

void Football_Game::play()
{
	int nKey, nRemain;
   	
  	Scr.ScreenInit();  
	Football_Game::Init();        // 蟾晦��

    while( 1 )
    { 
		if( _kbhit() )
		{	
			if( g_sStageInfo->g_GameState == RESULT )
				break;
			
			nKey = _getch();		

			switch( nKey )
			{
			case 'j' : 
				if( g_sPlayer.get_x() > 2 ) // 豭薹 醱給 唳啗 謝ル 羹觼
						 {
							 g_sPlayer.plus_x(-1);
							 nRemain = g_Opt.g_nLength - g_sPlayer.nCenterX + 1; // 瞪羹 望檜 - ( 醞褕 謝ル + 1 )擎 陴擎 望檜
							 // Note: 2鏽歲噶 檜翕ж晦 嬪и 睡碟 ( つ檜 勘耀 唳辦 ) 
							 if( g_sPlayer.get_x() - g_sPlayer.nCenterX < 2 || g_sPlayer.get_x() + nRemain > 43 )
								  g_sPlayer.plus_x(-1);

							 g_sPlayer.nX = g_sPlayer.get_x() - g_sPlayer.nCenterX; 
						 }
						 break;
			case 'l' :
						 if( g_sPlayer.get_x() + 1 < 43 ) // 螃艇薹 醱給 唳啗 謝ル 羹觼
						 {
							 g_sPlayer.plus_x(1);
							nRemain = g_Opt.g_nLength - g_sPlayer.nCenterX + 1; // 瞪羹 望檜 - ( 醞褕 謝ル + 1 )擎 陴擎 望檜
							// Note: 2鏽歲噶 檜翕ж晦 嬪и 睡碟 ( つ檜 勘耀 唳辦 )
							if( g_sPlayer.get_x() + nRemain > 43 || ( g_sPlayer.get_x() - g_sPlayer.nCenterX < 2 ) ) 
								 g_sPlayer.plus_x(1);
						 
							g_sPlayer.nX = g_sPlayer.get_x() - g_sPlayer.nCenterX;
						 }
						 break;
			case 'k' :
						if( g_sBall.nIsReady && g_sStageInfo->g_GameState == RUNNING )
						{
							g_sBall.set_x(g_sPlayer.get_x());
							g_sBall.set_y(g_sPlayer.get_y() - 1);
							g_sBall.OldTime = clock();
							g_sBall.nIsReady = 0;
							//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[5], 0, &g_Channel[5]); // 螂 翕濛 模葬 轎溘
						}
						break;

			case 'y' :
			case 'Y' :
						if( g_sStageInfo->g_GameState == FAILED ) 
						{													
							Init();
							g_sStageInfo->g_GameState = READY;	
							//FMOD_Channel_Stop( g_Channel[2] );  // 嘐暮 褒ぬ 餌遴萄 轎溘 醞雖 
							//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[3], 0, &g_Channel[3]);
						}							
						break;
			case 'n' :
			case 'N' :
						if( g_sStageInfo->g_GameState == FAILED )
						{							
							g_sStageInfo->g_GameState = RESULT;							
							//FMOD_Channel_Stop( g_Channel[2] );  // 嘐暮 褒ぬ 餌遴萄 轎溘 醞雖							
						}
						break;

			case ' ' :
						if( g_sStageInfo->g_GameState == INIT && g_Opt.g_nStage == 0 )
						{							
							g_sStageInfo->g_GameState = READY;
							//FMOD_Channel_Stop( g_Channel[0] ); // 寡唳擠 醞雖
							//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[3], 0, &g_Channel[3]); // ready 餌遴萄
							g_Opt.g_UpdateOldTime = clock();  // ready蒂 橾薑衛除 雖樓п 輿晦 嬪п 							
						}
						break;
			}
		}

 
		Football_Game::Update();// 等檜攪 偵褐
		Scr.Render(g_sGoalDae,g_sBall,g_sPlayer);    // �飛� 轎溘
		//FMOD_System_Update( g_System );		
	}
    
    Football_Game::Release();   // п薯
	Screen::ScreenRelease();
}


void Football_Game::Init()
{
	int nLength, i;

	if( g_Opt.g_nStage == -1 ) 
	{
		//SoundInit(); // 餌遴萄 蟾晦��
		g_Opt.g_nStage = 0;
		//FMOD_CHANNEL_FREE( g_System, FMOD_CHANNEL_FREE, g_Sound[0], 0, &g_Channel[0]); // 模偃 餌遴萄朝 瞪羹縑憮 и廓虜 褒чи棻.
	}

	g_Opt.g_LimitTime = g_sStageInfo[g_Opt.g_nStage].LimitTime;  // 薯и 衛除 撲薑
	g_Opt.g_nGoalBallCount = g_sStageInfo[g_Opt.g_nStage].nGoalBall; // 跡ル 埤檣 偃熱

	g_sPlayer.nCenterX = 4;
	g_sPlayer.nCenterY = 0;
	g_sPlayer.set_x(20);
	g_sPlayer.set_y(22);
	g_sPlayer.nX = g_sPlayer.get_x() - g_sPlayer.nCenterX;
	g_Opt.g_nLength = strlen( g_Opt.g_strPlayer );

	// 奢曖 蟾晦��
	g_sBall.nIsReady = 1;
	g_sBall.set_x(g_sPlayer.get_x());
	g_sBall.set_y(g_sPlayer.get_y() - 1);
	g_sBall.MoveTime = 100;

	// 埤渠 蟾晦��

	g_sGoalDae.set_x(g_sStageInfo[g_Opt.g_nStage].nGoalDaeX);
    g_sGoalDae.set_y(g_sStageInfo[g_Opt.g_nStage].nGoalDaeY);
    g_sGoalDae.nLength = g_sStageInfo[g_Opt.g_nStage].nGoalDaeLength;
    g_sGoalDae.MoveTime = g_sStageInfo[g_Opt.g_nStage].MoveTime;
    g_sGoalDae.OldTime = clock();
    g_sGoalDae.nDist = g_sStageInfo[g_Opt.g_nStage].nDist;
    nLength = g_sGoalDae.nLength*2 + 1; // Note: 寡翮曖 譆渠 望檜
		
    for( i = 0 ; i < nLength ; i++ )
    {
		 g_sGoalDae.nLineX[i] = g_sGoalDae.get_x() + 2*(i+1); 	
    }	

	// �膩� 
	g_sEffect.StayTime = 2000; // 2蟾 撲薑
	g_Opt.g_nGoal =  0;      // 蝶纔檜雖 諫猿 滲熱
	g_Opt.g_UpdateOldTime = clock();	
	g_Opt.g_nBallCount = 0;  // 埤檣и 奢曖 偃熱
}

void Football_Game::Release()
{
	//+int i;
	/*for( i = 0 ; i < 7 ; i++ )
		FMOD_Sound_Release( g_Sound[i] ); 

    FMOD_System_Close( g_System ); 
    FMOD_System_Release( g_System ); */
}

void Football_Game::Update()
{
	 clock_t CurTime = clock();
	 int nLength = g_sGoalDae.nLength*2 + 1; // Note: 寡翮曖 譆渠 望檜
	 int i;

	 	
	switch( g_sStageInfo->g_GameState )
	{
	case READY :				
				if( CurTime - g_Opt.g_UpdateOldTime > 2000 )  // 2蟾
				{					
					g_sStageInfo->g_GameState = RUNNING;
					g_Opt.g_GameStartTime = CurTime;

					//FMOD_Channel_Stop( g_Channel[3] );  // ready 餌遴萄 醞雖
					//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[1], 0, &g_Channel[1]); // running 寡唳擠
				}
				break;
	case RUNNING :					
				if( CurTime - g_Opt.g_GameStartTime > g_Opt.g_LimitTime ) // Note: 薯и 衛除
				{
					g_sStageInfo->g_GameState = STOP;
					return ;
				}else{
					 // Note: 埤渠
					 if( CurTime - g_sGoalDae.OldTime > g_sGoalDae.MoveTime )
					 {
						 g_sGoalDae.OldTime = CurTime;
						 if( g_sGoalDae.get_x() + g_sGoalDae.nDist >= 2 && ((g_sGoalDae.nLineX[nLength-1] + 3 ) + g_sGoalDae.nDist) <= 43 )
						 {
							g_sGoalDae.plus_x(g_sGoalDae.nDist);
							for( i = 0 ; i < nLength ; i++ )
							{
								 g_sGoalDae.nLineX[i] = g_sGoalDae.get_x() + 2*(i+1); 	
							}	
						 }else{
							  g_sGoalDae.nDist = g_sGoalDae.nDist * -1; // -1 檜 寞щ擊 夥紱橫 邀.
						 }
					 }	

					if( g_sBall.nIsReady == 0 ) // 檜翕 醞橾 陽 
					{	// 檜翕 衛除 除問縑 曖и 檜翕
						if( (CurTime - g_sBall.OldTime) > g_sBall.MoveTime )
						{
							if( g_sBall.get_y() - 1 > 0 )
							{
								g_sBall.plus_y(-1);
								g_sBall.OldTime = CurTime; // 棻擠 檜翕 衛陝婁 綠掖ж晦 嬪п ⑷營 衛除擊 檜瞪 衛除 滲熱縑 盪濰
					
								// 埤渠 塭檣 醱給
								if( g_sBall.get_x() >= g_sGoalDae.nLineX[0] && g_sBall.get_x() + 1 <= g_sGoalDae.nLineX[nLength-1] + 1 )
								{
									if( g_sBall.get_y() <= g_sGoalDae.get_y() )
									{   // 奢 蟾晦��
										g_sBall.nIsReady = 1;
										g_sBall.set_x(g_sPlayer.get_x());
										g_sBall.set_y(g_sPlayer.get_y() - 1);		
										g_Opt.g_nBallCount++;  // 埤檣и 奢曖 偃熱										

										if( g_Opt.g_nBallCount == g_Opt.g_nGoalBallCount ) // 奢婁 跡ル 奢婁曖 偃熱陛 偽戲賊 SUCCESS
										{
											g_sStageInfo->g_GameState = STOP;
											g_Opt.g_nGoal = 1;
											return ;
										}
								
										// �膩� 轎溘
										if( g_Opt.g_nIsGoal == 0 )
										{
											g_Opt.g_nIsGoal = 1;
											g_sEffect.StratTime = CurTime;
										}
									
									    // 埤檣 餌遴萄 轎溘
										//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[6], 0, &g_Channel[6]); // 埤檣 餌遴萄 諦辦~
									}  
									  // 埤渠 醱給 
								}else if( ( g_sBall.get_x() >= g_sGoalDae.nLineX[0] - 2 && g_sBall.get_x() <= g_sGoalDae.nLineX[0] - 1 ) ||
									      ( g_sBall.get_x() + 1 >= g_sGoalDae.nLineX[0] - 2 && g_sBall.get_x() + 1 <= g_sGoalDae.nLineX[0] - 1 ) ||
										  ( g_sBall.get_x() >= g_sGoalDae.nLineX[nLength-1] + 2 && g_sBall.get_x() <= g_sGoalDae.nLineX[nLength-1] + 3 ) ||
										  ( g_sBall.get_x() + 1 >= g_sGoalDae.nLineX[nLength-1] + 2 && g_sBall.get_x() + 1 <= g_sGoalDae.nLineX[nLength-1] + 3 ) )
								{
										if( g_sBall.get_y() <= g_sGoalDae.get_y() )
										{   // 奢 蟾晦��
											g_sBall.nIsReady = 1;
											g_sBall.set_x(g_sPlayer.get_x());
											g_sBall.set_y(g_sPlayer.get_y() - 1);
										}
								}
							}else{ // 奢 蟾晦��
								g_sBall.nIsReady = 1;
								g_sBall.set_x(g_sPlayer.get_x());
								g_sBall.set_y(g_sPlayer.get_y() - 1);
							}
						}
					}else{
						g_sBall.set_x(g_sPlayer.get_x());
					}	

					// �膩� 
					if( g_Opt.g_nIsGoal == 1 )
					{
						 if( CurTime - g_sEffect.StratTime > g_sEffect.StayTime )
							 g_Opt.g_nIsGoal = 0;
					}				
				}		
				break;
	case STOP :					
				if( g_Opt.g_nGoal == 1 )
				{
					g_sStageInfo->g_GameState = SUCCESS;
					g_Opt.g_UpdateOldTime = CurTime;
					//FMOD_Channel_Stop( g_Channel[1] );  // running 餌遴萄 醞雖
					//FMOD_Channel_Stop( g_Channel[1] );  // running 餌遴萄 醞雖

					//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[4], 0, &g_Channel[4]); // 嘐暮 撩奢 餌遴萄
				}else{
				    g_sStageInfo->g_GameState = FAILED;	
					//FMOD_Channel_Stop( g_Channel[1] );  // running 餌遴萄 醞雖
					//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[2], 0, &g_Channel[2]); // 嘐暮 褒ぬ 餌遴萄
				}
				break;
	case SUCCESS :				
				if( CurTime - g_Opt.g_UpdateOldTime > 3000 )
				{
					g_Opt.g_UpdateOldTime = CurTime;					
					++g_Opt.g_nStage;		
					Init();
					g_sStageInfo->g_GameState = READY;
					//FMOD_Channel_Stop( g_Channel[4] );  // 嘐暮 撩奢 餌遴萄 轎溘 醞雖					
					//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[3], 0, &g_Channel[3]); //READY 餌遴萄 
				}
				break;	
	}	
}

#pragma endregion

#pragma region 詭檣л熱

int main(void)
{
	Football_Game Game1;
	Game1.play();

	return 0;
}


#pragma endregion
