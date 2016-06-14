/////////////////////////////////////////////////////////////
//Ç²º¼ °ÔÀÓ °´Ã¼ÁöÇâ ÇÁ·Î±×·¡¹Ö
//ÀÛ¼ºÀÚ : ÃÖ½ÂÈ¯
//1 ÀüÃ¼ÀûÀÎ °ÔÀÓ±¸Á¶ Å¬·¡½ºÈ­
//2 PointÅ¬·¡½º¸¦ ÀÌ¿ëÇÑ ¿ÀºêÁ§Æ®ÀÇ Å¬·¡½ºÈ­
//3 ½ºÅ×ÀÌÁö Á¤º¸¿Í °ÔÀÓ ¿É¼Ç °ü¸®ÇÏ´Â º¯¼öµéÀ» Å¬·¡½ºÈ­
/////////////////////////////////////////////////////////////

#pragma region Çì´õÆÄÀÏ

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#include <time.h>
//#include <fmod.h>
#include <windows.h>

#pragma endregion

#pragma region Å¸ÀÔ¸í ¼±¾ð ¹× Àü¿ª º¯¼ö

#define MAX_STAGE_ 2

//////

typedef enum _GAME_STATE { INIT, READY, RUNNING, STOP, SUCCESS, FAILED, RESULT } GAME_STATE;

class EFFECT
{
public:
	clock_t StratTime; // È¿°ú ¹ß»ý ½Ã°¢
	clock_t StayTime;  // È¿°ú Áö¼Ó ½Ã°£	
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
		strcpy(g_strPlayer,"¦±¦¬¡Ü¦¬¦°");
	}
};

#pragma region ½ºÅ×ÀÌÁö ÀÎÆ÷ Å¬·¡½º

class STAGE_INFO_CLASS
{
public:
	int nGoalBall;			// °ñÀÎÇØ¾ß ÇÒ º¼ÀÇ °³¼ö 
	clock_t LimitTime;      // Á¦ÇÑ ½Ã°£ 
	int nGoalDaeLength;		// °ñ´ë ±æÀÌ 
	int nGoalDaeX;			// °ñ´ë ÀÌµ¿ X ÁÂÇ¥
	int nGoalDaeY;			// °ñ´ë ÀÌµ¿ Y ÁÂÇ¥ 
	clock_t MoveTime;		// °ñ´ë ÀÌµ¿ ½Ã°£ °£°Ý
	int nDist;				// °ñ´ë ÀÌµ¿ °Å¸®

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

//FMOD_SYSTEM *g_System;  // FMOD system º¯¼ö¼±¾ð
//FMOD_SOUND  *g_Sound[7];          // ¹è°æ À½¾Ç                       È¿°ú À½¾Ç 
//char        *g_strFileName[7] = { "init.wav", "run.wav", "fail.wav", "ready.wav", "success.wav", "shoot.wav", "wow.wav" };
//FMOD_CHANNEL *g_Channel[7];

#pragma endregion

#pragma region ¿ÀºêÁ§Æ® °ü·Ã Å¬·¡½º

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
	int nIsReady;        // ÁØºñ »óÅÂ(1), ½¸»óÅÂ(0)
	//int nMoveX, nMoveY;  // ÀÌµ¿ ÁÂÇ¥
	clock_t MoveTime;    // ÀÌµ¿ ½Ã°£ °£°Ý
	clock_t OldTime;     // ÀÌÀü ÀÌµ¿ ½Ã°¢
};
	
class GOAL_DAE : public Point
{
public:
		//int nMoveX, nMoveY;     // ÀÌµ¿ ÁÂÇ¥ 
		int nLength;			// °ñ´ë ±æÀÌ	
		int nLineX[7];			// °ñÀÎ ¶óÀÎ x ÁÂÇ¥ (7°³)
		clock_t	MoveTime;		// ÀÌµ¿ ½Ã°£ °£°Ý
		clock_t	OldTime;	    // ÀÌÀü ÀÌµ¿ ½Ã°£
		int	nDist;				// ÀÌµ¿ °Å¸®
};

#pragma endregion

#pragma region Screen Å¬·¡½º

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

//½ºÅÂÆ½ º¯¼ö ÃÊ±âÈ­
int Screen::g_nScreenIndex = 0;
HANDLE Screen::g_hScreen[2] = {NULL,NULL};

#pragma region Screen.c º¹ºÙ-> Screen class Á¤ÀÇ

//#include <windows.h>

//static int g_nScreenIndex;
//static HANDLE g_hScreen[2];

void Screen::ScreenInit()
{
	CONSOLE_CURSOR_INFO cci;
	
	// °¡»óÀÇ ÄÜ¼ÖÃ¢ 2°³·ê ¸¸µç´Ù.
	g_hScreen[0] = CreateConsoleScreenBuffer( GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL );
	g_hScreen[1] = CreateConsoleScreenBuffer( GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL );

	// Ä¿¼­ ¼û±â±â
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

// 1 ~ 15 ±îÁö »ö»ó ¼³Á¤ °¡´É
void Screen::SetColor( unsigned short color )
{		
	SetConsoleTextAttribute( g_hScreen[g_nScreenIndex], color );
}

#pragma endregion


void Screen::InitScreen()
{
	Screen::ScreenPrint( 0, 0, "¦®¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¯");
	Screen::ScreenPrint( 0, 1, "¦­                                          ¦­");
	Screen::ScreenPrint( 0, 2, "¦­             ¡à¦¬¦¬¦¬¡à                   ¦­");
	Screen::ScreenPrint( 0, 3, "¦­                                          ¦­");
	Screen::ScreenPrint( 0, 4, "¦­                        ///.   ½¸~~~      ¦­");  
	Screen::ScreenPrint( 0, 5, "¦­                       (^.^)              ¦­");    
	Screen::ScreenPrint( 0, 6, "¦­                      ¦±¦´ ¦²¦¯           ¦­");
	Screen::ScreenPrint( 0, 7, "¦­                         ¦®¦°             ¦­");
	Screen::ScreenPrint( 0, 8, "¦­                     ¢Á  ¦°¡¬             ¦­");
	Screen::ScreenPrint( 0, 9, "¦­                                          ¦­");
	Screen::ScreenPrint( 0,10, "¦­                                          ¦­");
	Screen::ScreenPrint( 0,11, "¦­       ½¸ °ñÀÎ °ÔÀÓ  Go! Go!              ¦­");
	Screen::ScreenPrint( 0,12, "¦­                                          ¦­");	
	Screen::ScreenPrint( 0,13, "¦­                                          ¦­");
	Screen::ScreenPrint( 0,14, "¦­       j :¿ÞÂÊ l : ¿À¸¥ÂÊ k :½¸           ¦­");
	Screen::ScreenPrint( 0,15, "¦­                                          ¦­");	
	Screen::ScreenPrint( 0,16, "¦­                                          ¦­");
	Screen::ScreenPrint( 0,17, "¦­                                          ¦­");
	Screen::ScreenPrint( 0,18, "¦­        ¦±¡Ü¦°  space Å°¸¦ ´­·¯ÁÖ¼¼¿ä     ¦­");
	Screen::ScreenPrint( 0,19, "¦­                                          ¦­");
	Screen::ScreenPrint( 0,20, "¦­                                          ¦­");
	Screen::ScreenPrint( 0,21, "¦­                                          ¦­");
	Screen::ScreenPrint( 0,22, "¦±¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦°");
}

void Screen::ReadyScreen()
{	
	char string[100];

	Screen::ScreenPrint( 0, 0, "¦®¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¯");
	Screen::ScreenPrint( 0, 1, "¦­¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¦­");
	Screen::ScreenPrint( 0, 2, "¦­¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¦­");
	Screen::ScreenPrint( 0, 3, "¦­¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¦­");
	Screen::ScreenPrint( 0, 4, "¦­¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¦­");
	Screen::ScreenPrint( 0, 5, "¦­¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¦­");
	Screen::ScreenPrint( 0, 6, "¦­¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¦­");
	Screen::ScreenPrint( 0, 7, "¦­¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¦­");
	Screen::ScreenPrint( 0, 8, "¦­¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¦­");
	Screen::ScreenPrint( 0, 9, "¦­¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¦­");
	Screen::ScreenPrint( 0,10, "¦­¡á¡á¡á¡á¡á                    ¡á¡á¡á¡á¡á¡á¦­");
	sprintf( string, "¦­¡á¡á¡á¡á¡á     %d   ½ºÅ×ÀÌÁö   ¡á¡á¡á¡á¡á¡á¦­", g_Opt.g_nStage + 1);
	Screen::ScreenPrint( 0,11, string);
	Screen::ScreenPrint( 0,12, "¦­¡á¡á¡á¡á¡á                    ¡á¡á¡á¡á¡á¡á¦­");
	Screen::ScreenPrint( 0,13, "¦­¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¦­");
	Screen::ScreenPrint( 0,14, "¦­¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¦­");
	Screen::ScreenPrint( 0,15, "¦­¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¦­");
	Screen::ScreenPrint( 0,16, "¦­¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¦­");
	Screen::ScreenPrint( 0,17, "¦­¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¦­");
	Screen::ScreenPrint( 0,18, "¦­¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¦­");
	Screen::ScreenPrint( 0,19, "¦­¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¦­");
	Screen::ScreenPrint( 0,20, "¦­¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¦­");
	Screen::ScreenPrint( 0,21, "¦­¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¦­");
	Screen::ScreenPrint( 0,22, "¦­¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¦­");	
	Screen::ScreenPrint( 0,23, "¦±¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦°");
}

void Screen::BackScreen()
{	
	char string[100];

	Screen::ScreenPrint( 0, 0, "¦®¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¯");
	Screen::ScreenPrint( 0, 1, "¦­                                          ¦­");
	Screen::ScreenPrint( 0, 2, "¦­                                          ¦­");
	Screen::ScreenPrint( 0, 3, "¦­                                          ¦­");
	sprintf( string,   "¦­                                          ¦­½ºÅ×ÀÌÁö: %d", g_Opt.g_nStage + 1 );
	Screen::ScreenPrint( 0, 4, string );
	Screen::ScreenPrint( 0, 5, "¦­                                          ¦­");
	sprintf( string,   "¦²¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦´Á¦ÇÑ ½Ã°£: %d", g_sStageInfo[g_Opt.g_nStage].LimitTime / 1000 );
	Screen::ScreenPrint( 0, 6, string );
	Screen::ScreenPrint( 0, 7, "¦­                                          ¦­");
	sprintf( string,   "¦­                                          ¦­ÇöÀç ½Ã°£: %d", ( clock() - g_Opt.g_GameStartTime ) / 1000 );
    Screen::ScreenPrint( 0, 8, string );
	Screen::ScreenPrint( 0, 9, "¦­                                          ¦­");
	sprintf( string,   "¦­                                          ¦­¸ñÇ¥ °ñÀÎ: %d ", g_sStageInfo[g_Opt.g_nStage].nGoalBall );
	Screen::ScreenPrint( 0,10, string ); 
	Screen::ScreenPrint( 0,11, "¦­                                          ¦­");
	sprintf( string,   "¦­                                          ¦­°ñÀÎ °ø °³¼ö: %d ", g_Opt.g_nBallCount );
	Screen::ScreenPrint( 0, 12, string );

	Screen::ScreenPrint( 0,13, "¦­                                          ¦­");
	sprintf( string,   "¦­                                          ¦­");
	Screen::ScreenPrint( 0, 14, string );
	Screen::ScreenPrint( 0,15, "¦­                                          ¦­");
	sprintf( string,   "¦­                                          ¦­");
	Screen::ScreenPrint( 0,16, string );
	Screen::ScreenPrint( 0,17, "¦­                                          ¦­");
	Screen::ScreenPrint( 0,18, "¦­                                          ¦­");
	Screen::ScreenPrint( 0,19, "¦­                                          ¦­");
	Screen::ScreenPrint( 0,20, "¦­                                          ¦­");
	Screen::ScreenPrint( 0,21, "¦­                                          ¦­");
	Screen::ScreenPrint( 0,22, "¦­                                          ¦­");
	Screen::ScreenPrint( 0,23, "¦±¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦°");
}

void Screen::GoalMessage( int nX, int nY )
{
     Screen::ScreenPrint( nX, nY,     "¡Ù )) °ñÀÎ (( ¡Ú" );
     Screen::ScreenPrint( nX, nY + 1, "¡¬(^^')/ ¡¬(\"*')/" );
     Screen::ScreenPrint( nX, nY + 2, "   ¡á       ¡á");
     Screen::ScreenPrint( nX, nY + 3, "  ¦¥¦¤    ¦£¦¦" );
}

void Screen::SuccessScreen()
{
	Screen::ScreenPrint( 0, 0, "¦®¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¯");
	Screen::ScreenPrint( 0, 1, "¦­                                          ¦­");
	Screen::ScreenPrint( 0, 2, "¦­                                          ¦­");
	Screen::ScreenPrint( 0, 3, "¦­                                          ¦­");
	Screen::ScreenPrint( 0, 4, "¦­                                          ¦­");
	Screen::ScreenPrint( 0, 5, "¦­                                          ¦­");
	Screen::ScreenPrint( 0, 6, "¦­                ////¡¬¡¬                  ¦­");
	Screen::ScreenPrint( 0, 7, "¦­               q ¡ü  ¡ü p                 ¦­");
	Screen::ScreenPrint( 0, 8, "¦­               (¦¦¦¡¦¡¦¥)                 ¦­");
	Screen::ScreenPrint( 0, 9, "¦­             ¢Ý ¹Ì¼Ç ¼º°ø ¢Ü              ¦­");
	Screen::ScreenPrint( 0,10, "¦­                                          ¦­");
	Screen::ScreenPrint( 0,11, "¦­                                          ¦­");
	Screen::ScreenPrint( 0,12, "¦­                                          ¦­");
	Screen::ScreenPrint( 0,13, "¦­                                          ¦­");
	Screen::ScreenPrint( 0,14, "¦­                                          ¦­");
	Screen::ScreenPrint( 0,15, "¦­                                          ¦­");
	Screen::ScreenPrint( 0,16, "¦­                                          ¦­");
	Screen::ScreenPrint( 0,17, "¦­                                          ¦­");
	Screen::ScreenPrint( 0,18, "¦­                                          ¦­");
	Screen::ScreenPrint( 0,19, "¦­                                          ¦­");
	Screen::ScreenPrint( 0,20, "¦­                                          ¦­");
	Screen::ScreenPrint( 0,21, "¦­                                          ¦­");
	Screen::ScreenPrint( 0,22, "¦­                                          ¦­");
	Screen::ScreenPrint( 0,23, "¦±¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦°");		
}

void Screen::FailureScreen()
{	
	Screen::ScreenPrint( 0, 0, "¦®¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¯");
	Screen::ScreenPrint( 0, 1, "¦­                                          ¦­");
	Screen::ScreenPrint( 0, 2, "¦­                                          ¦­");
	Screen::ScreenPrint( 0, 3, "¦­                                          ¦­");
	Screen::ScreenPrint( 0, 4, "¦­                                          ¦­");
	Screen::ScreenPrint( 0, 5, "¦­                                          ¦­");
	Screen::ScreenPrint( 0, 6, "¦­                                          ¦­");
	Screen::ScreenPrint( 0, 7, "¦­                                          ¦­");
	Screen::ScreenPrint( 0, 8, "¦­                                          ¦­");
	Screen::ScreenPrint( 0, 9, "¦­                                          ¦­");
	Screen::ScreenPrint( 0,10, "¦­                                          ¦­");
	Screen::ScreenPrint( 0,11, "¦­                    ¹Ì¼Ç ½ÇÆÐ !!!!        ¦­");
	Screen::ScreenPrint( 0,12, "¦­                                          ¦­");
	Screen::ScreenPrint( 0,13, "¦­                                          ¦­");
	Screen::ScreenPrint( 0,14, "¦­                 ¡Ü¦³¦¬¦¯                 ¦­");
	Screen::ScreenPrint( 0,15, "¦­                   ¦°  ¦±                 ¦­");
	Screen::ScreenPrint( 0,16, "¦­                  ¡á¡á¡á¡á                ¦­");
	Screen::ScreenPrint( 0,17, "¦­                                          ¦­");
	Screen::ScreenPrint( 0,18, "¦­        ´Ù½Ã ÇÏ½Ã°Ú½À´Ï±î? (y/n)          ¦­");
	Screen::ScreenPrint( 0,19, "¦­                                          ¦­");
	Screen::ScreenPrint( 0,20, "¦­                                          ¦­");
	Screen::ScreenPrint( 0,21, "¦­                                          ¦­");
	Screen::ScreenPrint( 0,22, "¦±¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦°");		
}

void Screen::ResultScreen()
{
	char string[100];
	Screen::ScreenPrint( 0, 0, "¦®¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¯");
	Screen::ScreenPrint( 0, 1, "¦­                                          ¦­");
	Screen::ScreenPrint( 0, 2, "¦­                                          ¦­");
	Screen::ScreenPrint( 0, 3, "¦­             ¡à¦¬¦¬¦¬¡à                   ¦­");
	Screen::ScreenPrint( 0, 4, "¦­                                          ¦­");
	Screen::ScreenPrint( 0, 5, "¦­                                          ¦­");
	Screen::ScreenPrint( 0, 6, "¦­                                          ¦­");
	Screen::ScreenPrint( 0, 7, "¦­                                          ¦­");
	sprintf( string,   "¦­      ¼º°øÇÑ ½ºÅ×ÀÌÁö :  %2d               ¦­", g_Opt.g_nStage + 1 );
	Screen::ScreenPrint( 0, 8, string );
	Screen::ScreenPrint( 0, 9, "¦­                                          ¦­");
	Screen::ScreenPrint( 0,10, "¦­                                          ¦­");
	Screen::ScreenPrint( 0,11, "¦­   ___¢Æ¢Æ¢Æ___                           ¦­");
	Screen::ScreenPrint( 0,12, "¦­     (*^  ^*)                             ¦­");  
	Screen::ScreenPrint( 0,13, "¦­ =====¡Û==¡Û=====                         ¦­");
	Screen::ScreenPrint( 0,14, "¦­                                          ¦­");
	Screen::ScreenPrint( 0,15, "¦­                                          ¦­");
	Screen::ScreenPrint( 0,16, "¦­                                          ¦­");
	Screen::ScreenPrint( 0,17, "¦­                                          ¦­");
	Screen::ScreenPrint( 0,18, "¦­                      ¦±¡Ü¦°              ¦­");
	Screen::ScreenPrint( 0,19, "¦­                                          ¦­");
	Screen::ScreenPrint( 0,20, "¦­                                          ¦­");
	Screen::ScreenPrint( 0,21, "¦­                                          ¦­");
	Screen::ScreenPrint( 0,22, "¦±¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦°");
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
			 Screen::ScreenPrint( g_sGoalDae.get_x(), g_sGoalDae.get_y(), "¡à" );
			 nLength = g_sGoalDae.nLength*2 + 1;

			 for( i = 0 ; i < nLength ; i++ )
				  Screen::ScreenPrint( g_sGoalDae.nLineX[i], g_sGoalDae.get_y(), "¦¬");
			
			  Screen::ScreenPrint( g_sGoalDae.nLineX[nLength-1] + 2, g_sGoalDae.get_y(), "¡à"); 	

			 // Note: È¿°ú Ãâ·Â  	
			 if( g_Opt.g_nIsGoal == 1 )
			 {
				GoalMessage( 10, 10 );
			 }	

			 // Note: 2 ÄÃ·³¾¿ Å¬¸®ÇÎ 
			 if( g_sPlayer.nX < 2 )  //  ¿ÞÂÊ Å¬¸®ÇÎ Ã³¸®
				  Screen::ScreenPrint( 2, g_sPlayer.get_y(), &g_Opt.g_strPlayer[(g_sPlayer.nX-2)*-1]);	 // ÁÂÇ¥¸¦ ¹è¿­ ÀÎµ¦½º 
			 else if( g_sPlayer.get_x() + (g_Opt.g_nLength - g_sPlayer.nCenterX + 1) > 43 ) // ¿À¸¥ÂÊ Å¬¸®ÇÎ Ã³¸®
			 {
				 strncat( string, g_Opt.g_strPlayer, g_Opt.g_nLength - (( g_sPlayer.get_x() + g_sPlayer.nCenterX + 1) - 43 ) );
				  Screen::ScreenPrint( g_sPlayer.nX, g_sPlayer.get_y(), string );		
			}else{ // 1 ÄÃ·³¾¿ ÀÌµ¿
				 Screen::ScreenPrint( g_sPlayer.nX, g_sPlayer.get_y(), g_Opt.g_strPlayer );
			}

			 Screen::ScreenPrint( g_sBall.get_x(), g_sBall.get_y(), "¢Á" );			
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
	
	// Note: ·»´õ¸µ ³¡ 
	 Screen::ScreenFlipping();
}


#pragma endregion

#pragma region Football_Game Å¬·¡½º 

class Football_Game
{
public:
	// ÇÔ¼ö
	Football_Game();
	virtual void play();
	void Init();
	void Release();
	void Update();


private:             
	friend class Screen;
	//º¯¼ö

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
	Football_Game::Init();        // ÃÊ±âÈ­

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
				if( g_sPlayer.get_x() > 2 ) // ¿ÞÂÊ Ãæµ¹ °æ°è ÁÂÇ¥ Ã¼Å©
						 {
							 g_sPlayer.plus_x(-1);
							 nRemain = g_Opt.g_nLength - g_sPlayer.nCenterX + 1; // ÀüÃ¼ ±æÀÌ - ( Áß½É ÁÂÇ¥ + 1 )Àº ³²Àº ±æÀÌ
							 // Note: 2ÄÃ·³¾¿ ÀÌµ¿ÇÏ±â À§ÇÑ ºÎºÐ ( ÆÈÀÌ °ÉÄ£ °æ¿ì ) 
							 if( g_sPlayer.get_x() - g_sPlayer.nCenterX < 2 || g_sPlayer.get_x() + nRemain > 43 )
								  g_sPlayer.plus_x(-1);

							 g_sPlayer.nX = g_sPlayer.get_x() - g_sPlayer.nCenterX; 
						 }
						 break;
			case 'l' :
						 if( g_sPlayer.get_x() + 1 < 43 ) // ¿À¸¥ÂÊ Ãæµ¹ °æ°è ÁÂÇ¥ Ã¼Å©
						 {
							 g_sPlayer.plus_x(1);
							nRemain = g_Opt.g_nLength - g_sPlayer.nCenterX + 1; // ÀüÃ¼ ±æÀÌ - ( Áß½É ÁÂÇ¥ + 1 )Àº ³²Àº ±æÀÌ
							// Note: 2ÄÃ·³¾¿ ÀÌµ¿ÇÏ±â À§ÇÑ ºÎºÐ ( ÆÈÀÌ °ÉÄ£ °æ¿ì )
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
							//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[5], 0, &g_Channel[5]); // ½¸ µ¿ÀÛ ¼Ò¸® Ãâ·Â
						}
						break;

			case 'y' :
			case 'Y' :
						if( g_sStageInfo->g_GameState == FAILED ) 
						{													
							Init();
							g_sStageInfo->g_GameState = READY;	
							//FMOD_Channel_Stop( g_Channel[2] );  // ¹Ì¼Ç ½ÇÆÐ »ç¿îµå Ãâ·Â ÁßÁö 
							//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[3], 0, &g_Channel[3]);
						}							
						break;
			case 'n' :
			case 'N' :
						if( g_sStageInfo->g_GameState == FAILED )
						{							
							g_sStageInfo->g_GameState = RESULT;							
							//FMOD_Channel_Stop( g_Channel[2] );  // ¹Ì¼Ç ½ÇÆÐ »ç¿îµå Ãâ·Â ÁßÁö							
						}
						break;

			case ' ' :
						if( g_sStageInfo->g_GameState == INIT && g_Opt.g_nStage == 0 )
						{							
							g_sStageInfo->g_GameState = READY;
							//FMOD_Channel_Stop( g_Channel[0] ); // ¹è°æÀ½ ÁßÁö
							//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[3], 0, &g_Channel[3]); // ready »ç¿îµå
							g_Opt.g_UpdateOldTime = clock();  // ready¸¦ ÀÏÁ¤½Ã°£ Áö¼ÓÇØ ÁÖ±â À§ÇØ 							
						}
						break;
			}
		}

 
		Football_Game::Update();// µ¥ÀÌÅÍ °»½Å
		Scr.Render(g_sGoalDae,g_sBall,g_sPlayer);    // È­¸é Ãâ·Â
		//FMOD_System_Update( g_System );		
	}
    
    Football_Game::Release();   // ÇØÁ¦
	Screen::ScreenRelease();
}


void Football_Game::Init()
{
	int nLength, i;

	if( g_Opt.g_nStage == -1 ) 
	{
		//SoundInit(); // »ç¿îµå ÃÊ±âÈ­
		g_Opt.g_nStage = 0;
		//FMOD_CHANNEL_FREE( g_System, FMOD_CHANNEL_FREE, g_Sound[0], 0, &g_Channel[0]); // ¼Ò°³ »ç¿îµå´Â ÀüÃ¼¿¡¼­ ÇÑ¹ø¸¸ ½ÇÇàÇÑ´Ù.
	}

	g_Opt.g_LimitTime = g_sStageInfo[g_Opt.g_nStage].LimitTime;  // Á¦ÇÑ ½Ã°£ ¼³Á¤
	g_Opt.g_nGoalBallCount = g_sStageInfo[g_Opt.g_nStage].nGoalBall; // ¸ñÇ¥ °ñÀÎ °³¼ö

	g_sPlayer.nCenterX = 4;
	g_sPlayer.nCenterY = 0;
	g_sPlayer.set_x(20);
	g_sPlayer.set_y(22);
	g_sPlayer.nX = g_sPlayer.get_x() - g_sPlayer.nCenterX;
	g_Opt.g_nLength = strlen( g_Opt.g_strPlayer );

	// °øÀÇ ÃÊ±âÈ­
	g_sBall.nIsReady = 1;
	g_sBall.set_x(g_sPlayer.get_x());
	g_sBall.set_y(g_sPlayer.get_y() - 1);
	g_sBall.MoveTime = 100;

	// °ñ´ë ÃÊ±âÈ­

	g_sGoalDae.set_x(g_sStageInfo[g_Opt.g_nStage].nGoalDaeX);
    g_sGoalDae.set_y(g_sStageInfo[g_Opt.g_nStage].nGoalDaeY);
    g_sGoalDae.nLength = g_sStageInfo[g_Opt.g_nStage].nGoalDaeLength;
    g_sGoalDae.MoveTime = g_sStageInfo[g_Opt.g_nStage].MoveTime;
    g_sGoalDae.OldTime = clock();
    g_sGoalDae.nDist = g_sStageInfo[g_Opt.g_nStage].nDist;
    nLength = g_sGoalDae.nLength*2 + 1; // Note: ¹è¿­ÀÇ ÃÖ´ë ±æÀÌ
		
    for( i = 0 ; i < nLength ; i++ )
    {
		 g_sGoalDae.nLineX[i] = g_sGoalDae.get_x() + 2*(i+1); 	
    }	

	// È¿°ú 
	g_sEffect.StayTime = 2000; // 2ÃÊ ¼³Á¤
	g_Opt.g_nGoal =  0;      // ½ºÅ×ÀÌÁö ¿Ï·á º¯¼ö
	g_Opt.g_UpdateOldTime = clock();	
	g_Opt.g_nBallCount = 0;  // °ñÀÎÇÑ °øÀÇ °³¼ö
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
	 int nLength = g_sGoalDae.nLength*2 + 1; // Note: ¹è¿­ÀÇ ÃÖ´ë ±æÀÌ
	 int i;

	 	
	switch( g_sStageInfo->g_GameState )
	{
	case READY :				
				if( CurTime - g_Opt.g_UpdateOldTime > 2000 )  // 2ÃÊ
				{					
					g_sStageInfo->g_GameState = RUNNING;
					g_Opt.g_GameStartTime = CurTime;

					//FMOD_Channel_Stop( g_Channel[3] );  // ready »ç¿îµå ÁßÁö
					//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[1], 0, &g_Channel[1]); // running ¹è°æÀ½
				}
				break;
	case RUNNING :					
				if( CurTime - g_Opt.g_GameStartTime > g_Opt.g_LimitTime ) // Note: Á¦ÇÑ ½Ã°£
				{
					g_sStageInfo->g_GameState = STOP;
					return ;
				}else{
					 // Note: °ñ´ë
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
							  g_sGoalDae.nDist = g_sGoalDae.nDist * -1; // -1 ÀÌ ¹æÇâÀ» ¹Ù²Ù¾î ÁÜ.
						 }
					 }	

					if( g_sBall.nIsReady == 0 ) // ÀÌµ¿ ÁßÀÏ ¶§ 
					{	// ÀÌµ¿ ½Ã°£ °£°Ý¿¡ ÀÇÇÑ ÀÌµ¿
						if( (CurTime - g_sBall.OldTime) > g_sBall.MoveTime )
						{
							if( g_sBall.get_y() - 1 > 0 )
							{
								g_sBall.plus_y(-1);
								g_sBall.OldTime = CurTime; // ´ÙÀ½ ÀÌµ¿ ½Ã°¢°ú ºñ±³ÇÏ±â À§ÇØ ÇöÀç ½Ã°£À» ÀÌÀü ½Ã°£ º¯¼ö¿¡ ÀúÀå
					
								// °ñ´ë ¶óÀÎ Ãæµ¹
								if( g_sBall.get_x() >= g_sGoalDae.nLineX[0] && g_sBall.get_x() + 1 <= g_sGoalDae.nLineX[nLength-1] + 1 )
								{
									if( g_sBall.get_y() <= g_sGoalDae.get_y() )
									{   // °ø ÃÊ±âÈ­
										g_sBall.nIsReady = 1;
										g_sBall.set_x(g_sPlayer.get_x());
										g_sBall.set_y(g_sPlayer.get_y() - 1);		
										g_Opt.g_nBallCount++;  // °ñÀÎÇÑ °øÀÇ °³¼ö										

										if( g_Opt.g_nBallCount == g_Opt.g_nGoalBallCount ) // °ø°ú ¸ñÇ¥ °ø°úÀÇ °³¼ö°¡ °°À¸¸é SUCCESS
										{
											g_sStageInfo->g_GameState = STOP;
											g_Opt.g_nGoal = 1;
											return ;
										}
								
										// È¿°ú Ãâ·Â
										if( g_Opt.g_nIsGoal == 0 )
										{
											g_Opt.g_nIsGoal = 1;
											g_sEffect.StratTime = CurTime;
										}
									
									    // °ñÀÎ »ç¿îµå Ãâ·Â
										//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[6], 0, &g_Channel[6]); // °ñÀÎ »ç¿îµå ¿Í¿ì~
									}  
									  // °ñ´ë Ãæµ¹ 
								}else if( ( g_sBall.get_x() >= g_sGoalDae.nLineX[0] - 2 && g_sBall.get_x() <= g_sGoalDae.nLineX[0] - 1 ) ||
									      ( g_sBall.get_x() + 1 >= g_sGoalDae.nLineX[0] - 2 && g_sBall.get_x() + 1 <= g_sGoalDae.nLineX[0] - 1 ) ||
										  ( g_sBall.get_x() >= g_sGoalDae.nLineX[nLength-1] + 2 && g_sBall.get_x() <= g_sGoalDae.nLineX[nLength-1] + 3 ) ||
										  ( g_sBall.get_x() + 1 >= g_sGoalDae.nLineX[nLength-1] + 2 && g_sBall.get_x() + 1 <= g_sGoalDae.nLineX[nLength-1] + 3 ) )
								{
										if( g_sBall.get_y() <= g_sGoalDae.get_y() )
										{   // °ø ÃÊ±âÈ­
											g_sBall.nIsReady = 1;
											g_sBall.set_x(g_sPlayer.get_x());
											g_sBall.set_y(g_sPlayer.get_y() - 1);
										}
								}
							}else{ // °ø ÃÊ±âÈ­
								g_sBall.nIsReady = 1;
								g_sBall.set_x(g_sPlayer.get_x());
								g_sBall.set_y(g_sPlayer.get_y() - 1);
							}
						}
					}else{
						g_sBall.set_x(g_sPlayer.get_x());
					}	

					// È¿°ú 
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
					//FMOD_Channel_Stop( g_Channel[1] );  // running »ç¿îµå ÁßÁö
					//FMOD_Channel_Stop( g_Channel[1] );  // running »ç¿îµå ÁßÁö

					//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[4], 0, &g_Channel[4]); // ¹Ì¼Ç ¼º°ø »ç¿îµå
				}else{
				    g_sStageInfo->g_GameState = FAILED;	
					//FMOD_Channel_Stop( g_Channel[1] );  // running »ç¿îµå ÁßÁö
					//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[2], 0, &g_Channel[2]); // ¹Ì¼Ç ½ÇÆÐ »ç¿îµå
				}
				break;
	case SUCCESS :				
				if( CurTime - g_Opt.g_UpdateOldTime > 3000 )
				{
					g_Opt.g_UpdateOldTime = CurTime;					
					++g_Opt.g_nStage;		
					Init();
					g_sStageInfo->g_GameState = READY;
					//FMOD_Channel_Stop( g_Channel[4] );  // ¹Ì¼Ç ¼º°ø »ç¿îµå Ãâ·Â ÁßÁö					
					//FMOD_System_PlaySound( g_System, FMOD_CHANNEL_FREE, g_Sound[3], 0, &g_Channel[3]); //READY »ç¿îµå 
				}
				break;	
	}	
}

#pragma endregion

#pragma region ¸ÞÀÎÇÔ¼ö

int main(void)
{
	Football_Game Game1;
	Game1.play();

	return 0;
}


#pragma endregion
