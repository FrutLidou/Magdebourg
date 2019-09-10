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
// Nouvelles fonctionnalités
void MouseButtonDown(int x, int y, BOOL bLeft);
void MouseButtonUp(int x, int y, BOOL bLeft);
void MouseMove(int x, int y);

class GameEngine
{// Déclaration des variables membres
protected:
	static GameEngine* m_pGameEngine;	// pointeur sur moteur pour permettre l’accès de 
										// l’extérieur par une fonction du jeu	
	HINSTANCE	m_hInstance;			// Instance de l’application et de la fenêtre du jeu
	HWND		m_hWindow;
	TCHAR	    m_szWindowClass[32];	// Nom de la classe et titre de la fenêtre du jeu
	TCHAR	    m_szTitle[32];
	WORD		m_wIcon, m_wSmallIcon, m_wCursor;		//ID numérique des icônes du jeu
	int		    m_iWidth, m_iHeight;	//largeur et hauteur écran aire de jeu
	int		    m_iFrameDelay; 			//laps de temps entre deux cycles de jeu
	BOOL		m_bSleep;				//spécifie si le jeu est en pause
	UINT		m_uiMIDIPlayerID;		//joue les midis

	//Prototypes : Constructeur Destructeur
public:
	//sylvie
	HWND hTextQuitter;

	GameEngine(HINSTANCE hInstance, LPTSTR szWindowClass, LPTSTR szTitle,
				WORD wIcon, WORD wSmallIcon, WORD wCursor,
				int iWidth = 640, int iHeight = 480);

	virtual ~GameEngine();  			//on ajoutera du code pour nettoyage

	//----------------- Méthodes générales du moteur de jeu -------------------------//

	//Accéder au pointeur du moteur
	static GameEngine*  GetEngine()
	{
		return m_pGameEngine;
	};

	//Initialisera le moteur à sa création
	BOOL      Initialize(int iCmdShow);

	//Gérer les événements Windows au sein du jeu
	LRESULT   HandleEvent(HWND hWindow, UINT msg,
		                  WPARAM wParam, LPARAM lParam);

	//Méthodes accesseurs  (accéder ou ajuster des variables membres)
	HINSTANCE GetInstance()		{ return m_hInstance; };
	HWND      GetWindow() 		{ return m_hWindow; };
	void      SetWindow(HWND hWindow) {	m_hWindow = hWindow; };
	LPTSTR    GetTitle() 		{ return m_szTitle; };
	WORD      GetIcon() 		{ return m_wIcon; };
	int       GetWidth() 		{ return m_iWidth; };
	int       GetHeight() 		{ return m_iHeight; };
	int       GetFrameDelay() 	{ return m_iFrameDelay; };

	//Ajuste fréquence de défilement des images(millisec)
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
