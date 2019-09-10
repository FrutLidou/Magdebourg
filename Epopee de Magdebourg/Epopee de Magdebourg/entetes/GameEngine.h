#pragma once

#include "WndMain.h"
#include "WinApp.h"

//---------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

//-----------------------------------------------------------------
// Game Engine : Prototypes des autres fonctions
//-----------------------------------------------------------------
BOOL GameInitialize(HINSTANCE hInstance);
void GameStart(HWND hWindow);
void GameEnd();
void GameActivate(HWND hWindow);
void GameDeactivate(HWND hWindow);
void GamePaint(HDC hDC);
void GameCycle();
void HandleKeys();
// Nouvelles fonctionnalit�s
void MouseButtonDown(int x, int y, BOOL bLeft);
void MouseButtonUp(int x, int y, BOOL bLeft);
void MouseMove(int x, int y);

class GameEngine
{// D�claration des variables membres
protected:
	static GameEngine* m_pGameEngine;	// pointeur sur moteur pour permettre l�acc�s de 
										// l�ext�rieur par une fonction du jeu	
	HINSTANCE	m_hInstance;			// Instance de l�application et de la fen�tre du jeu
	HWND		m_hWindow;
	TCHAR	    m_szWindowClass[32];	// Nom de la classe et titre de la fen�tre du jeu
	TCHAR	    m_szTitle[32];
	WORD		m_wIcon, m_wSmallIcon, m_wCursor;		//ID num�rique des ic�nes du jeu
	int		    m_iWidth, m_iHeight;	//largeur et hauteur �cran aire de jeu
	int		    m_iFrameDelay; 			//laps de temps entre deux cycles de jeu
	BOOL		m_bSleep;				//sp�cifie si le jeu est en pause
	UINT		m_uiMIDIPlayerID;		//joue les midis

	//Prototypes : Constructeur Destructeur
public:
	//sylvie
	HWND hTextQuitter;

	GameEngine(HINSTANCE hInstance, LPTSTR szWindowClass, LPTSTR szTitle,
				WORD wIcon, WORD wSmallIcon, WORD wCursor,
				int iWidth = 640, int iHeight = 480);

	virtual ~GameEngine();  			//on ajoutera du code pour nettoyage

	//----------------- M�thodes g�n�rales du moteur de jeu -------------------------//

	//Acc�der au pointeur du moteur
	static GameEngine*  GetEngine()
	{
		return m_pGameEngine;
	};

	//Initialisera le moteur � sa cr�ation
	BOOL      Initialize(int iCmdShow);

	//G�rer les �v�nements Windows au sein du jeu
	LRESULT   HandleEvent(HWND hWindow, UINT msg,
		                  WPARAM wParam, LPARAM lParam);

	//M�thodes accesseurs  (acc�der ou ajuster des variables membres)
	HINSTANCE GetInstance()		{ return m_hInstance; };
	HWND      GetWindow() 		{ return m_hWindow; };
	void      SetWindow(HWND hWindow) {	m_hWindow = hWindow; };
	LPTSTR    GetTitle() 		{ return m_szTitle; };
	WORD      GetIcon() 		{ return m_wIcon; };
	int       GetWidth() 		{ return m_iWidth; };
	int       GetHeight() 		{ return m_iHeight; };
	int       GetFrameDelay() 	{ return m_iFrameDelay; };

	//Ajuste fr�quence de d�filement des images(millisec)
	void      SetFrameRate(int iFrameRate)
								{ m_iFrameDelay = 1000 / iFrameRate; };
	BOOL      GetSleep() 		{ return m_bSleep; };
	void      SetSleep(BOOL bSleep)	{ m_bSleep = bSleep; };

	//Gestion de la musique
	int musique = 0;
	void PlayMIDISong(LPTSTR szMIDIFileName, BOOL bRestart = TRUE);
	void PauseMIDISong();
	void CloseMIDIPlayer();
};
