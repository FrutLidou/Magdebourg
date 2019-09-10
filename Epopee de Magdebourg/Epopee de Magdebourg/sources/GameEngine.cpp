//-----------------------------------------------------------------
// Code source Moteur de jeu/Procédure principale et de fenêtre
// C++ Source - GameEngine.cpp
//-----------------------------------------------------------------
// Include
//-----------------------------------------------------------------
#include "GameEngine.h"
#include <string>
#include <stdlib.h>
#include <time.h>
//-----------------------------------------------------------------
// Initialisation pointeur statique du moteur du jeu
//-----------------------------------------------------------------
GameEngine *GameEngine::m_pGameEngine = NULL;
//-----------------------------------------------------------------
// Point d'entrée de l'application Windows
//-----------------------------------------------------------------
int  WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	                PSTR szCmdLine, int iCmdShow)
{
	MSG         msg;
	static int  iTickTrigger = 0;
	int         iTickCount;

	if (GameInitialize(hInstance))   //fonctions d’initialisation du jeu (événement du jeu)
	{
		// Initialiser le moteur de jeu
		if (!GameEngine::GetEngine()->Initialize(iCmdShow))
			return FALSE;

		// Boucle de messages
		while (TRUE)
		{
			//PeekMessage permet d'exécuter un code en l'absence de message
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				// traiter les messages
				if (msg.message == WM_QUIT)
					break;
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				// Vérifier si le jeu est en veille
				if (!GameEngine::GetEngine()->GetSleep())
				{
					// Vérifier si un nouveau cycle doit commencer
					iTickCount = GetTickCount();
					if (iTickCount > iTickTrigger)
					{
						iTickTrigger = iTickCount + GameEngine::GetEngine()->GetFrameDelay();
						HandleKeys();
						GameCycle();
					}
				}
			}
		}
		return (int)msg.wParam;
	}
	// FIN du jeu
	GameEnd();
	return TRUE;
}


//-----------------------------------------------------------------
// Fonction fenêtre qui fait une PASSE au moteur de jeu
//-----------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWindow, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// Achemine les messages vers le moteur de jeu
	return GameEngine::GetEngine()->HandleEvent(hWindow, msg, wParam, lParam);
}

//-----------------------------------------------------------------
// GameEngine Constructeur/Destructeur
//-----------------------------------------------------------------
GameEngine::GameEngine(HINSTANCE hInstance, LPTSTR szWindowClass, LPTSTR szTitle, 
						WORD wIcon, WORD wSmallIcon, WORD wCursor, 
						int iWidth, int iHeight)
{
	// Initialise les variables du moteur 
	m_pGameEngine  = this;
	m_hInstance    = hInstance;
	m_hWindow      = NULL;
	if (lstrlen(szWindowClass) > 0)
		lstrcpy(m_szWindowClass, szWindowClass);
	if (lstrlen(szTitle) > 0)
		lstrcpy(m_szTitle, szTitle);
	m_wIcon       = wIcon;
	m_wSmallIcon  = wSmallIcon;
	m_wCursor     = wCursor ;
	m_iWidth      = iWidth;
	m_iHeight     = iHeight;
	m_iFrameDelay = 50;   // par défaut 20 FPS  (1000/50)
	m_bSleep      = TRUE;
	m_uiMIDIPlayerID = 0;	//MIDI
}

GameEngine::~GameEngine()
{
}



//-----------------------------------------------------------------
// Game Engine : Méthodes générales
//-----------------------------------------------------------------
// Initialize : Dissimule le code Windows générique dans le moteur du jeu
//
BOOL GameEngine::Initialize(int iCmdShow)
{
	//WNDCLASSEX    wndclassEx;
	//Créer l'instance de l'application Windows
	WApplication WJeu(m_hInstance, m_szWindowClass, WndProc, NULL, m_wIcon, m_wSmallIcon, m_wCursor );

	// Crée instance de l’objet fenêtre
	if (!WJeu.Register())
		return FALSE;

	// Calcule dimensions de la fenêtre et la position en fonction de la fenêtre de jeu
	int iWindowWidth  = m_iWidth + GetSystemMetrics(SM_CXFIXEDFRAME) * 2;
	int iWindowHeight = m_iHeight + GetSystemMetrics(SM_CYFIXEDFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION);

	if (WJeu.GetMenuName() != NULL)
		iWindowHeight += GetSystemMetrics(SM_CYMENU);

	int iXWindowPos = (GetSystemMetrics(SM_CXSCREEN) - iWindowWidth) / 2;
	int iYWindowPos = (GetSystemMetrics(SM_CYSCREEN) - iWindowHeight) / 2;

	// Créer la fenêtre
	WWindow  m_hWindow;
	m_hWindow.Create(m_hInstance, m_szWindowClass, m_szTitle, 
		             NULL, WS_POPUPWINDOW | WS_CAPTION | WS_MINIMIZEBOX, 0L,
					 iXWindowPos, iYWindowPos, iWindowWidth, iWindowHeight);

	if (!m_hWindow.GetHWND())
		return FALSE;		//création de fenêtre impossible le jeu s'arrête

	// Affichage et mise à jour de la fenêtre
	m_hWindow.Show();


	
	return TRUE;
}
//-----------------------------------------------------------------
// HandleEvent : Reçoit les messages habituellement gérer dans la fonction WndProc
//-----------------------------------------------------------------
LRESULT GameEngine::HandleEvent(HWND hWindow, UINT msg, WPARAM wParam, LPARAM lParam)
{  // Acheminer les messages Windows vers les FONCTIONS membres du moteur de jeu
	//Variables pour les midis
	std::string seek;
	std::string play;
	switch (msg)
	{
	case WM_CREATE:			// Actualiser fenêtre de jeu et démarrer le jeu
		SetWindow(hWindow);
		GameStart(hWindow);
		
		
		//sylvie

		hTextQuitter = CreateWindowEx(NULL, "EDIT", "Quitter",
			WS_CHILD | WS_VISIBLE,0, 0, 100, 400, NULL, 0, 0, 0);

		//MIDI
		srand(time(NULL));
		mciSendString("open 0.mid type sequencer alias 0", NULL, 0, NULL);
		mciSendString("open 1.mid type sequencer alias 1", NULL, 0, NULL);
		mciSendString("open 2.mid type sequencer alias 2", NULL, 0, NULL);
		mciSendString("open 3.mid type sequencer alias 3", NULL, 0, NULL);
		mciSendString("open 4.mid type sequencer alias 4", NULL, 0, NULL);
		mciSendString("open 5.mid type sequencer alias 5", NULL, 0, NULL);
		mciSendString("open 6.mid type sequencer alias 6", NULL, 0, NULL);
		mciSendString("open 7.mid type sequencer alias 7", NULL, 0, NULL);
		mciSendString("open 8.mid type sequencer alias 8", NULL, 0, NULL);
		mciSendString("open 9.mid type sequencer alias 9", NULL, 0, NULL);
		mciSendString("open bakamitai.mid type sequencer alias bakamitai", NULL, 0, NULL);
		return 0;

	case MM_MCINOTIFY:
		if (musique != -1)
		{
			musique = rand() % 10;
			seek = "seek " + std::to_string(musique) + " to start";
			play = "play " + std::to_string(musique) + " notify";
			mciSendString(seek.c_str(), NULL, 0, NULL);
			mciSendString(play.c_str(), NULL, 0, hWindow);
		}
		break;

	case WM_ACTIVATE:		// Activer/désactiver le jeu  
		if (wParam != WA_INACTIVE)
		{
			GameActivate(hWindow);	//jeu réveillé
			SetSleep(FALSE);
		}
		else
		{
			GameDeactivate(hWindow);	//jeu en veille
			SetSleep(TRUE);
		}
		return 0;

	case WM_PAINT:
		HDC         hDC;
		PAINTSTRUCT ps;
		hDC = BeginPaint(hWindow, &ps);

		GamePaint(hDC);		// Tracé du jeu


		EndPaint(hWindow, &ps);
		return 0;

		//Nouveaux messages Windows
	case WM_LBUTTONDOWN:
		// Appuyer bouton gauche
		MouseButtonDown(LOWORD(lParam), HIWORD(lParam), TRUE);
		return 0;

	case WM_LBUTTONUP:
		// Relâcher bouton gauche
		MouseButtonUp(LOWORD(lParam), HIWORD(lParam), TRUE);
		return 0;

	case WM_RBUTTONDOWN:
		// Appuyer bouton droit
		MouseButtonDown(LOWORD(lParam), HIWORD(lParam), FALSE);
		return 0;

	case WM_RBUTTONUP:
		// Relâcher bouton gauche
		MouseButtonUp(LOWORD(lParam), HIWORD(lParam), FALSE);
		return 0;

	case WM_MOUSEMOVE:
		// Déplacement souris
		MouseMove(LOWORD(lParam), HIWORD(lParam));
		return 0;

	case WM_DESTROY:
		GameEnd();			// Fin du jeu et fermeture de l’application
		PostQuitMessage(0);
		return 0;
	}
	// windows prend la relève si je n'ai pas détermine quoi faire 
	return DefWindowProc(hWindow, msg, wParam, lParam);
}

//Gestion des MIDIs
void GameEngine::PlayMIDISong(LPTSTR szMIDIFileName, BOOL bRestart)
{
	// Vérifier si le périphérique MIDI est ouvert
	if (m_uiMIDIPlayerID == 0)
	{
		MCI_OPEN_PARMS mciOpenParms;
		mciOpenParms.lpstrDeviceType = "sequencer";
		mciOpenParms.lpstrElementName = szMIDIFileName;
		// Ouvrir le périphérique en spécifiant l’unité et le nom de fichier en utilisant
		// le transmetteur de message mciSendCommand
		if (mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT,
			(DWORD_PTR)&mciOpenParms) == 0)
			// retenir l’ID du périphérique
			m_uiMIDIPlayerID = mciOpenParms.wDeviceID;
		else
			// Problème à l’ouverture fin de la procédure
			return;
	}

	// Redémarrer le morceau si nécessaire
	if (bRestart)
	{
		MCI_SEEK_PARMS mciSeekParms;
		if (mciSendCommand(m_uiMIDIPlayerID, MCI_SEEK, MCI_SEEK_TO_START,
			(DWORD_PTR)&mciSeekParms) != 0)
			// Problème rencontré fermer le périphérique
			CloseMIDIPlayer();
	}

	// Jouer le son MIDI
	MCI_PLAY_PARMS mciPlayParms;
	if (mciSendCommand(m_uiMIDIPlayerID, MCI_PLAY, 0,
		(DWORD_PTR)&mciPlayParms) != 0)
		// Problème rencontré fermer le périphérique
		CloseMIDIPlayer();
}

void GameEngine::PauseMIDISong()
{
	// Mettre en pause le morceau si possible
	if (m_uiMIDIPlayerID != 0)
		mciSendCommand(m_uiMIDIPlayerID, MCI_PAUSE, 0, NULL);
}

void GameEngine::CloseMIDIPlayer()
{
	// Fermer le périphérique si possible
	if (m_uiMIDIPlayerID != 0)
	{
		mciSendCommand(m_uiMIDIPlayerID, MCI_CLOSE, 0, NULL);
		m_uiMIDIPlayerID = 0;
	}
}
