//-----------------------------------------------------------------
// UFO Application
// C++ Source - 
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Jeu.h"
#include <fstream>
#include <iostream>
#include <iomanip>

//-----------------------------------------------------------------
// Fonctions du moteur de jeu
//-----------------------------------------------------------------
BOOL GameInitialize(HINSTANCE hInstance)
{
	// Créer l'instance du moteur de jeu

	_pGame = new GameEngine(hInstance, _ClasseFenetre, _TitreFenetre,
		IDI_MAGDEBOURG, IDI_MAGDEBOURG,
		IDC_EPEE, _iLargeur, _iHauteur);

	if (_pGame == NULL)
		return FALSE;

	// Changer le taux de rafraichissement
	_pGame->SetFrameRate(30);

	// Garder le handle de l'application
	_hInstance = hInstance;

	return TRUE;
}

void GameStart(HWND hWindow)
{
	// Créer une surface de dessin (périphérique hors écran)
	// et le bitmap hors écran pour éviter le papillotement
	_hOffscreenDC = CreateCompatibleDC(GetDC(hWindow));
	_hOffscreenBitmap = CreateCompatibleBitmap(GetDC(hWindow),
		_pGame->GetWidth(), _pGame->GetHeight());
	SelectObject(_hOffscreenDC, _hOffscreenBitmap);

	// Créer et charger les bitmaps
	HDC hDC = GetDC(hWindow);
	_pTitreJeu = new Bitmap(hDC, IDB_TITRE_JEU, _hInstance);
	_pDemarrer = new Bitmap(hDC, IDB_DEMARRER, _hInstance);
	_pHistoire = new Bitmap(hDC, IDB_HISTOIRE, _hInstance);
	_pInstructions = new Bitmap(hDC, IDB_INSTRUCTIONS, _hInstance);
	_pOptions = new Bitmap(hDC, IDB_OPTIONS, _hInstance);
	_pQuitter = new Bitmap(hDC, IDB_QUITTER, _hInstance);
	_pMagdebourg = new Bitmap(hDC, IDB_MAGDEBOURG, _hInstance);
	_pTHistoire = new Bitmap(hDC, IDB_T_HISTOIRE, _hInstance);
	_pTInstructions = new Bitmap(hDC, IDB_T_INSTRUCTIONS, _hInstance);
	_pTOptions = new Bitmap(hDC, IDB_T_OPTIONS, _hInstance);
	_pRetour = new Bitmap(hDC, IDB_RETOUR, _hInstance);
	_pFondJeu = new Bitmap(hDC, IDB_FOND_JEU, _hInstance);
	_pTillyBmp = new Bitmap(hDC, IDB_TILLY, _hInstance);
	_pMenuHist1 = new Bitmap(hDC, IDB_MENU_HIST1, _hInstance);
	_pMenuHist2 = new Bitmap(hDC, IDB_MENU_HIST2, _hInstance);
	_pNext = new Bitmap(hDC, IDB_NEXT, _hInstance);
	_pPrecedent = new Bitmap(hDC, IDB_PRECEDENT, _hInstance);
	_pRien = new Bitmap(hDC, IDB_RIEN, _hInstance);
	_pCaseB = new Bitmap(hDC, IDB_CASE_DISPO, _hInstance);
	_pUArquebuse = new Bitmap(hDC, IDB_ARQUEBUSE, _hInstance);
	_pUCanon = new Bitmap(hDC, IDB_CANON, _hInstance);
	_pCaseR = new Bitmap(hDC, IDB_CASE_ATTAQUE, _hInstance);
	_pUCavalerie = new Bitmap(hDC, IDB_CAVALERIE, _hInstance);
	_pUInfanterie = new Bitmap(hDC, IDB_INFANTERIE, _hInstance);
	_pUVelours = new Bitmap(hDC, IDB_VELOURS, _hInstance);
	_pMarkVert = new Bitmap(hDC, IDB_MARK_VERT, _hInstance);
	_pMarkJaune = new Bitmap(hDC, IDB_MARK_JAUNE, _hInstance);
	_pMarkRouge = new Bitmap(hDC, IDB_MARK_ROUGE, _hInstance);
	_pSideBar = new Bitmap(hDC, IDB_SIDE_BAR, _hInstance);
	_pMenuBg = new Bitmap(hDC, IDB_MENU_BG, _hInstance);
	_pBtnFinTour = new Bitmap(hDC, IDB_FIN_TOUR, _hInstance);
	_pHpDecile = new Bitmap(hDC, IDB_HP_DECILE, _hInstance);
	_pHpBar = new Bitmap(hDC, IDB_HP_BAR, _hInstance);
	_pMiniHpBar = new Bitmap(hDC, IDB_MINI_HP_BAR, _hInstance);
	_pMiniHpDecile = new Bitmap(hDC, IDB_MINI_HP_DECILE, _hInstance);
	_pChoixPerso = new Bitmap(hDC, IDB_CHOIX_PERSO, _hInstance);
	_pChoisir = new Bitmap(hDC, IDB_CHOISIR, _hInstance);
	_pAmirBmp = new Bitmap(hDC, IDB_AMIR, _hInstance);
	_pAnfrayBmp = new Bitmap(hDC, IDB_ANFRAY, _hInstance);
	_pKonradBmp = new Bitmap(hDC, IDB_KONRAD, _hInstance);
	_pLuigiBmp = new Bitmap(hDC, IDB_LUIGI, _hInstance);
	_pBtnActif = new Bitmap(hDC, IDB_BTN_ACTIF, _hInstance);
	_pCaseV = new Bitmap(hDC, IDB_CASE_SOIN, _hInstance);
	_pBtnNextUnit = new Bitmap(hDC, IDB_BTN_NEXT_UNIT, _hInstance);
	_pBtnAttaquer = new Bitmap(hDC, IDB_BTN_ATTAQUER, _hInstance);
	_pBtnDeplacer = new Bitmap(hDC, IDB_BTN_DEPLACER, _hInstance);
	_pMnuRecords = new Bitmap(hDC, IDB_MNU_RECORDS, _hInstance);
	_pMnuCredits = new Bitmap(hDC, IDB_MNU_CREDITS, _hInstance);
	_pBtnCredits = new Bitmap(hDC, IDB_CREDITS, _hInstance);
	_p1Titre = new Bitmap(hDC, IDB_1_TITRE, _hInstance);
	_p2Titre = new Bitmap(hDC, IDB_2_TITRE, _hInstance);
	_pInstructions1 = new Bitmap(hDC, IDB_INSTRUCTIONS1, _hInstance);
	_pInstructions2 = new Bitmap(hDC, IDB_INSTRUCTIONS2, _hInstance);
	_pInstructions3 = new Bitmap(hDC, IDB_INSTRUCTIONS3, _hInstance);
	_pModeDemo = new Bitmap(hDC, IDB_MODE_DEMO, _hInstance);
	_pSwitchOff = new Bitmap(hDC, IDB_SWITCH_OFF, _hInstance);
	_pSwitchOn = new Bitmap(hDC, IDB_SWITCH_ON, _hInstance);

	tabLogo.push_back(new Bitmap(hDC, IDB_INFANTERIE_LOGO, _hInstance));
	tabLogo.push_back(new Bitmap(hDC, IDB_ARQUEBUSE_LOGO, _hInstance));
	tabLogo.push_back(new Bitmap(hDC, IDB_CAVALERIE_LOGO, _hInstance));
	tabLogo.push_back(new Bitmap(hDC, IDB_CANON_LOGO, _hInstance));
	tabLogo.push_back(new Bitmap(hDC, IDB_COMMANDANT_LOGO, _hInstance));
	tabPersonnages.push_back(new Bitmap(hDC, IDB_T_AMIR, _hInstance));
	tabPersonnages.push_back(new Bitmap(hDC, IDB_C_AMIR, _hInstance));
	tabPersonnages.push_back(new Bitmap(hDC, IDB_T_ANFRAY, _hInstance));
	tabPersonnages.push_back(new Bitmap(hDC, IDB_C_ANFRAY, _hInstance));
	tabPersonnages.push_back(new Bitmap(hDC, IDB_T_KONRAD, _hInstance));
	tabPersonnages.push_back(new Bitmap(hDC, IDB_C_KONRAD, _hInstance));
	tabPersonnages.push_back(new Bitmap(hDC, IDB_T_LUIGI, _hInstance));
	tabPersonnages.push_back(new Bitmap(hDC, IDB_C_LUIGI, _hInstance));
	tabPersonnages.push_back(new Bitmap(hDC, IDB_T_RODRICH, _hInstance));
	tabPersonnages.push_back(new Bitmap(hDC, IDB_C_RODRICH, _hInstance));
	tabDescActif.push_back(new Bitmap(hDC, IDB_DESC_ACTIF_AMIR, _hInstance));
	tabDescActif.push_back(new Bitmap(hDC, IDB_DESC_ACTIF_ANFRAY, _hInstance));
	tabDescActif.push_back(nullptr); //Konrad n'a pas d'actif
	tabDescActif.push_back(new Bitmap(hDC, IDB_DESC_ACTIF_LUIGI, _hInstance));
	tabDescActif.push_back(new Bitmap(hDC, IDB_DESC_ACTIF_RODRICH, _hInstance));

	_pRodrich = new Sprite(_pTillyBmp);
	_pArquebuse = new Sprite(_pUArquebuse);
	_pCanon = new Sprite(_pUCanon);
	_pCavalerie = new Sprite(_pUCavalerie);
	_pInfanterie = new Sprite(_pUInfanterie);
	_pVelours = new Sprite(_pUVelours);
	_pFondMap = new Sprite(_pFondJeu);
	_pFondMap->SetPosition(0, 0);
	_pCaseDispo = new Sprite(_pCaseB);
	_pCaseAttaque = new Sprite(_pCaseR);
	_pCaseSoin = new Sprite(_pCaseV);
	_pAmir = new Sprite(_pAmirBmp);
	_pAnfray = new Sprite(_pAnfrayBmp);
	_pKonrad = new Sprite(_pKonradBmp);
	_pLuigi = new Sprite(_pLuigiBmp);

	//Ajouter les généraux au vecteur
	tabGeneraux = fillGeneraux();
	//Définir les cases difficiles
	fillCases(typeCase);
	//Lire les stats
	lireStats();
}

void GameEnd()
{
	// Nettoyage du moteur de jeu
	// Détruire les pointeurs et objets utilisés dans le jeu
	// Détruire les objets bitmaps
	delete _pTitreJeu;
	delete _pDemarrer;
	delete _pHistoire;
	delete _pInstructions;
	delete _pOptions;
	delete _pQuitter;
	delete _pMagdebourg;
	delete _pTHistoire;
	delete _pTInstructions;
	delete _pTOptions;
	delete _pRetour;
	delete _pFondJeu;
	delete _pTillyBmp;
	delete _pMenuHist1;
	delete _pMenuHist2;
	delete _pNext;
	delete _pPrecedent;
	delete _pRien;
	delete _pCaseB;
	delete _pUArquebuse;
	delete _pUCanon;
	delete _pCaseR;
	delete _pUCavalerie;
	delete _pUInfanterie;
	delete _pUVelours;
	delete _pMarkVert;
	delete _pMarkJaune;
	delete _pMarkRouge;
	delete _pSideBar;
	delete _pMenuBg;
	delete _pBtnFinTour;
	delete _pHpDecile;
	delete _pHpBar;
	delete _pMiniHpBar;
	delete _pMiniHpDecile;
	delete _pChoixPerso;
	delete _pChoisir;
	delete _pAmirBmp;
	delete _pAnfrayBmp;
	delete _pKonradBmp;
	delete _pLuigiBmp;
	delete _pBtnActif;
	delete _pCaseV;
	delete _pBtnNextUnit;
	delete _pBtnAttaquer;
	delete _pBtnDeplacer;
	delete _pMnuRecords;
	delete _pBtnCredits;
	delete _pMnuCredits;
	delete _p1Titre;
	delete _p2Titre;
	delete _pInstructions1;
	delete _pInstructions2;
	delete _pInstructions3;
	delete _pModeDemo;
	delete _pSwitchOff;
	delete _pSwitchOn;

	tabLogo.clear();
	tabPersonnages.clear();
	tabDescActif.clear();
	tabUnites.clear();

	delete _pRodrich;
	delete _pArquebuse;
	delete _pCanon;
	delete _pCavalerie;
	delete _pInfanterie;
	delete _pVelours;
	delete _pFondMap;
	delete _pCaseDispo;
	delete _pCaseAttaque;
	delete _pCaseSoin;
	delete _pAmir;
	delete _pAnfray;
	delete _pKonrad;
	delete _pLuigi;

	// Nettoyage du contexte de périphérique et du bitmap hors écran
	// utilisé pendant le jeu (libère la mémoire)
	DeleteObject(_hOffscreenBitmap);
	DeleteDC(_hOffscreenDC);

	// Détruire le pointeur vers le moteur
	delete _pGame;
}

void GameActivate(HWND hWindow)
{
	/*
	if (_pGame->musique != -1)
	{
		//_pGame->pause = false;
		std::string seek = "seek " + std::to_string(_pGame->musique);
		std::string resume = "play " + std::to_string(_pGame->musique) + " notify";
		mciSendString(seek.c_str(), NULL, 0, NULL);
		mciSendString(resume.c_str(), NULL, 0, hWindow);
	}
*/
}

void GameDeactivate(HWND hWindow)
{
	/*
	if (_pGame->musique != -1)
	{
		//_pGame->pause = true;
		std::string pause = "pause " + std::to_string(_pGame->musique);
		mciSendString(pause.c_str(), NULL, 0, hWindow);
	}
	*/
}

void GameCycle()
{
	// Selon l'état du jeu ....


  // pour dessiner le jeu hors écran on passe le périphérique hors écran
  // à la procédure GamePaint alors tout s'affiche en une fois
	GamePaint(_hOffscreenDC);
	// Obtenir le contexte de périphérique de l’application
	HWND hWindow = _pGame->GetWindow();
	HDC hDC = GetDC(hWindow);
	// Commander de dessiner le bitmap hors écran sur l'écran de jeu
	BitBlt(hDC, 0, 0, _pGame->GetWidth(), _pGame->GetHeight(),
		_hOffscreenDC, 0, 0, SRCCOPY);
	// Nettoyage
	ReleaseDC(hWindow, hDC);
}

void GamePaint(HDC hDC)
{
	// Selon l'état du jeu ....
	_pDemarrer->ResetPosition0();
	_pHistoire->ResetPosition0();
	_pInstructions->ResetPosition0();
	_pOptions->ResetPosition0();
	_pQuitter->ResetPosition0();
	_pRetour->ResetPosition0();
	_pPrecedent->ResetPosition0();
	_pNext->ResetPosition0();
	_pChoisir->ResetPosition0();
	_pBtnAttaquer->ResetPosition0();
	_pBtnDeplacer->ResetPosition0();
	_pBtnCredits->ResetPosition0();
	_pSwitchOff->ResetPosition0();
	_pSwitchOn->ResetPosition0();
	std::string strRecord;
	LPCSTR affichageRecord;

	switch (_EtatDuJeu)
	{
	case _EtatDemarrer:
		_pFondMap->Draw(hDC);
		afficherUnites(hDC, tabUnites, _pMiniHpBar, _pMiniHpDecile);
		_pSideBar->Draw(hDC, 1000, 0);
		_pBtnFinTour->Draw(hDC, 1015, 700);
		_pBtnNextUnit->Draw(hDC, 1015, 460);
		if (selectedUnit >= 0 && selectedUnit < tabUnites.size())
		{
			tabLogo.at(tabUnites.at(selectedUnit)->getUType() - 1)->Draw(hDC, 1160, 10, TRUE, RGB(11, 11, 11));
			_pHpBar->Draw(hDC, 1014, 174);
			tabUnites.at(selectedUnit)->drawHp(hDC, _pHpDecile);
			if (etatAttaquer)
			{
				if (!tabUnites.at(selectedUnit)->hasMoved())
					_pBtnDeplacer->Draw(hDC, 1015, 590);
			}
			else
				_pBtnAttaquer->Draw(hDC, 1015, 590);
		}
		if (selectedGeneral[nbTours % 2] != 2)
		{
			if (actifDelay[nbTours % 2] == 0 && !generalMort[nbTours % 2])
			{
				_pBtnActif->Draw(hDC, 1015, 240);
				tabDescActif.at(selectedGeneral[nbTours % 2])->Draw(hDC, 1015, 300);
			}
		}
		break;
	case _EtatDebutJeu:
		_pMenuBg->Draw(hDC, 0, 0);
		_pTitreJeu->Draw(hDC, 0, 0);
		_pMagdebourg->Draw(hDC, 300, 85, TRUE, RGB(255, 255, 255));
		_pDemarrer->Draw(hDC, 50, 170, TRUE, RGB(158, 97, 25));
		_pHistoire->Draw(hDC, 50, 258, TRUE, RGB(158, 97, 25));
		_pInstructions->Draw(hDC, 50, 346, TRUE, RGB(158, 97, 25));
		_pOptions->Draw(hDC, 50, 434, TRUE, RGB(158, 97, 25));
		_pQuitter->Draw(hDC, 50, 522, TRUE, RGB(158, 97, 25));
		_pBtnCredits->Draw(hDC, 50, 700, TRUE, RGB(158, 97, 25));
		_pModeDemo->Draw(hDC, 1037, -5, TRUE, RGB(0, 0, 0));
		if (jeuDemo)
			_pSwitchOn->Draw(hDC, 1150, -10, TRUE, RGB(0, 0, 0));
		else
			_pSwitchOff->Draw(hDC, 1150, -10, TRUE, RGB(0, 0, 0));
		break;
	case _EtatHistoire:
		_pMenuBg->Draw(hDC, 0, 0);
		_pMenuHist1->Draw(hDC, 0, 0);
		_pRetour->Draw(hDC, 50, 522, TRUE, RGB(158, 97, 25));
		_pNext->Draw(hDC, 549, 522, TRUE, RGB(124, 54, 8));

		break;
	case _EtatHistoire2:
		_pMenuBg->Draw(hDC, 0, 0);
		_pMenuHist2->Draw(hDC, 0, 0);
		_pRetour->Draw(hDC, 50, 522, TRUE, RGB(158, 97, 25));
		_pPrecedent->Draw(hDC, 270, 522, TRUE, RGB(124, 54, 8));

		break;
	case _EtatInstructions1:
		_pInstructions1->Draw(hDC, 0, 0);
		_pPrecedent->Draw(hDC, 50, 700, TRUE, RGB(124, 54, 8));
		_pNext->Draw(hDC, 1100, 700, TRUE, RGB(124, 54, 8));
		break;
	case _EtatInstructions2:
		_pInstructions2->Draw(hDC, 0, 0);
		_pPrecedent->Draw(hDC, 50, 700, TRUE, RGB(124, 54, 8));
		_pNext->Draw(hDC, 390, 700, TRUE, RGB(124, 54, 8));
		break;
	case _EtatInstructions3:
		_pInstructions3->Draw(hDC, 0, 0);
		_pPrecedent->Draw(hDC, 50, 700, TRUE, RGB(124, 54, 8));
		_pNext->Draw(hDC, 1100, 700, TRUE, RGB(124, 54, 8));
		break;
	case _EtatOptions:
		_pMenuBg->Draw(hDC, 0, 0);
		SetBkMode(hDC, TRANSPARENT);
		SetTextColor(hDC, RGB(255, 255, 255));
		_pMnuRecords->Draw(hDC, 0, 0);
		strRecord = std::to_string(plusBasNbTours) + " tours";
		affichageRecord = strRecord.c_str();
		TextOut(hDC, 400, 180, affichageRecord, strRecord.length());
		strRecord = std::to_string(plusGrandNbUnites) + " unités";
		affichageRecord = strRecord.c_str();
		TextOut(hDC, 475, 285, affichageRecord, strRecord.length());
		switch (typeUnitePlusDeKills)
		{
		case 1:
			_pUInfanterie->Draw(hDC, 550, 360, TRUE, RGB(219, 255, 0));
			break;
		case 2:
			_pUArquebuse->Draw(hDC, 550, 360, TRUE, RGB(219, 255, 0));
			break;
		case 3:
			_pUCavalerie->Draw(hDC, 550, 360, TRUE, RGB(219, 255, 0));
			break;
		case 4:
			_pUCanon->Draw(hDC, 550, 360, TRUE, RGB(219, 255, 0));
			break;
		case 5:
			_pTillyBmp->Draw(hDC, 550, 360, TRUE, RGB(219, 255, 0));
			break;
		}
		strRecord = "(" + std::to_string(plusGrandNbKillsUnit) + ")";
		affichageRecord = strRecord.c_str();
		TextOut(hDC, 650, 400, affichageRecord, strRecord.length());

		_pRetour->Draw(hDC, 50, 522, TRUE, RGB(158, 97, 25));
		break;
	case _EtatQuitter:
		break;
	case _EtatChoixGeneral1:
		_pMenuBg->Draw(hDC, 0, 0);
		_pTitreJeu->Draw(hDC, 0, 0);
		_pChoixPerso->Draw(hDC, 50, 85, TRUE, RGB(255, 255, 255));
		_p1Titre->Draw(hDC, 666, 85, TRUE, RGB(255, 255, 255));
		tabPersonnages.at(selectedGeneral[0] * 2)->Draw(hDC, 50, 160);
		tabPersonnages.at(selectedGeneral[0] * 2 + 1)->Draw(hDC, 50, 240);
		_pChoisir->Draw(hDC, 50, 532, TRUE, RGB(158, 97, 25));
		_pPrecedent->Draw(hDC, 270, 532, TRUE, RGB(124, 54, 8));
		_pNext->Draw(hDC, 549, 532, TRUE, RGB(124, 54, 8));
		break;
	case _EtatChoixGeneral2:
		_pMenuBg->Draw(hDC, 0, 0);
		_pTitreJeu->Draw(hDC, 0, 0);
		_pChoixPerso->Draw(hDC, 50, 85, TRUE, RGB(255, 255, 255));
		_p2Titre->Draw(hDC, 666, 85, TRUE, RGB(255, 255, 255));
		tabPersonnages.at(selectedGeneral[1] * 2)->Draw(hDC, 50, 160);
		tabPersonnages.at(selectedGeneral[1] * 2 + 1)->Draw(hDC, 50, 240);
		_pChoisir->Draw(hDC, 50, 532, TRUE, RGB(158, 97, 25));
		_pPrecedent->Draw(hDC, 270, 532, TRUE, RGB(124, 54, 8));
		_pNext->Draw(hDC, 549, 532, TRUE, RGB(124, 54, 8));
		break;
	case _EtatCredits:
		_pMenuBg->Draw(hDC, 0, 0);
		_pMnuCredits->Draw(hDC, 0, 0);
		_pRetour->Draw(hDC, 50, 522, TRUE, RGB(158, 97, 25));
		break;
	}
}

void HandleKeys()
{
	//deplacer la carte
	int x = 0;
	int y = 0;
	const int STEP = 100;
	if (GetAsyncKeyState(VK_LEFT) < 0) {
		if (_pFondMap->GetPosition().left + STEP <= 0)
		{
			x += STEP;
			positionEcran.x--;
		}
	}
	else if (GetAsyncKeyState(VK_RIGHT) < 0) {
		if (_pFondMap->GetPosition().right - STEP > _iLargeur)
		{
			x -= STEP;
			positionEcran.x++;
		}
	}
	if (GetAsyncKeyState(VK_UP) < 0) {
		if (_pFondMap->GetPosition().top + STEP <= 0)
		{
			y += STEP;
			positionEcran.y--;
		}
	}
	else if (GetAsyncKeyState(VK_DOWN) < 0) {
		if (_pFondMap->GetPosition().bottom - STEP > _iHauteur)
		{
			y -= STEP;
			positionEcran.y++;
		}
	}
	if (GetAsyncKeyState(VK_SPACE) < 0) {
		if (_EtatDuJeu == _EtatDemarrer)
		{
			selectedUnit = findNextUnit(tabUnites, selectedUnit);
			pressedShift = false;
			focusUnite(tabUnites.at(selectedUnit), _pFondMap);
			clearUnites(tabUnites);
		}
	}
	if (GetAsyncKeyState(VK_SHIFT) < 0) {
		if (_EtatDuJeu == _EtatDemarrer && selectedUnit > -1)
			pressedShift = true;
	}
	else if (pressedShift) {
		if (_EtatDuJeu == _EtatDemarrer && selectedUnit > -1 && !tabUnites[selectedUnit]->hasMoved())
		{
			if (!etatAttaquer)
			{
				clearUnites(tabUnites);
				etatAttaquer = true;
				tabUnites.at(selectedUnit)->attaquer(_pCaseAttaque, tabUnites, tabUnites.at(selectedUnit)->GetPosition(), tabGeneraux);
			}
			else
			{
				clearUnites(tabUnites);
				etatAttaquer = false;
				tabUnites.at(selectedUnit)->deplacer(_pCaseDispo, tabUnites, 0, tabUnites.at(selectedUnit)->GetPosition(), casesParcourues, selectedGeneral[nbTours % 2], typeCase);
			}
			pressedShift = false;
		}
	}
	if (GetAsyncKeyState(VK_ESCAPE) < 0) {
		//Voulez-vous vraiment quitter?
		if (_EtatDuJeu == _EtatDemarrer || _EtatDuJeu == _EtatChoixGeneral1 || _EtatDuJeu == _EtatChoixGeneral2)
		{
			int msgBoxQter = MessageBox(NULL, "Voulez-vous VRAIMENT retourner au menu principal?", "Attention!",
				MB_ICONWARNING | MB_YESNO);
			if (msgBoxQter == IDYES)
			{
				tabUnites.clear();
				_pFondMap->SetPosition(0, 0);
				selectedGeneral[0] = 0;
				selectedGeneral[1] = 0;
				selectedUnit = -1;
				actifDelay[0] = 0;
				actifDelay[1] = 0;
				etatActif = -1;
				nbTours = 0;
				positionEcran = { 0,0 };
				generalMort[0] = false;
				generalMort[1] = false;
				pressedShift = false;
				std::string stop = "stop " + std::to_string(_pGame->musique);
				_pGame->musique = -1;
				mciSendString(stop.c_str(), NULL, 0, _pGame->GetWindow());
				_EtatDuJeu = _EtatDebutJeu;
			}
		}
	}

	_pFondMap->OffsetPosition(x, y);
}

void MouseButtonDown(int x, int y, BOOL bLeft)
{
	if (bLeft)
	{

	}
	else
	{

	}

}

void MouseButtonUp(int x, int y, BOOL bLeft)
{
	if (bLeft)
	{
		//Changer de menu
		if (_pDemarrer->IsPointInside(x, y))
		{
			tabUnites = fillTableau();
			_EtatDuJeu = _EtatChoixGeneral1;
		}
		else if (_pHistoire->IsPointInside(x, y))
		{
			_EtatDuJeu = _EtatHistoire;
		}
		else if (_pInstructions->IsPointInside(x, y))
		{
			_EtatDuJeu = _EtatInstructions1;
		}
		else if (_pOptions->IsPointInside(x, y))
		{
			_EtatDuJeu = _EtatOptions;
		}
		else if (_pQuitter->IsPointInside(x, y))
		{
			_EtatDuJeu = _EtatQuitter;
			GameEnd();
			PostQuitMessage(0);
		}
		else if (_pSwitchOff->IsPointInside(x, y))
			jeuDemo = true;
		else if (_pSwitchOn->IsPointInside(x, y))
			jeuDemo = false;
		else if (_pRetour->IsPointInside(x, y))
		{
			_EtatDuJeu = _EtatDebutJeu;
		}
		else if (_pBtnCredits->IsPointInside(x, y))
		{
			_EtatDuJeu = _EtatCredits;
		}
		else if (_pNext->IsPointInside(x, y))
		{
			if (_EtatDuJeu == _EtatChoixGeneral1)
			{
				if (selectedGeneral[0] == 4)
					selectedGeneral[0] = 0;
				else
					selectedGeneral[0]++;
			}
			else if (_EtatDuJeu == _EtatChoixGeneral2)
			{
				if (selectedGeneral[1] == 4)
					selectedGeneral[1] = 0;
				else
					selectedGeneral[1]++;
				if (selectedGeneral[0] == selectedGeneral[1])
				{
					if (selectedGeneral[1] == 4)
						selectedGeneral[1] = 0;
					else
						selectedGeneral[1]++;
				}
			}
			else if (_EtatDuJeu == _EtatInstructions1)
				_EtatDuJeu = _EtatInstructions2;
			else if (_EtatDuJeu == _EtatInstructions2)
				_EtatDuJeu = _EtatInstructions3;
			else if (_EtatDuJeu == _EtatInstructions3)
				_EtatDuJeu = _EtatDebutJeu;
			else
				_EtatDuJeu = _EtatHistoire2;
		}
		else if (_pChoisir->IsPointInside(x, y))
		{
			//Sélection des généraux
			POINT spawnGeneral;
			if (_EtatDuJeu == _EtatChoixGeneral1)
			{
				//Mode standard ou mode démo
				if (jeuDemo)
				{
					spawnGeneral.x = 17;
					spawnGeneral.y = 8;
				}
				else
				{
					spawnGeneral.x = 17;
					spawnGeneral.y = 2;
				}
				_EtatDuJeu = _EtatChoixGeneral2;
				Unite* general1 = tabGeneraux.at(selectedGeneral[0])->clone();
				general1->SetPosition(spawnGeneral);
				tabUnites.push_back(general1);
				if (selectedGeneral[0] == 0)
					selectedGeneral[1] = 1;
			}
			else if (_EtatDuJeu == _EtatChoixGeneral2)
			{
				//Mode standard ou mode démo
				if (jeuDemo)
				{
					spawnGeneral.x = 15;
					spawnGeneral.y = 15;
				}
				else
				{
					spawnGeneral.x = 23;
					spawnGeneral.y = 26;
				}
				_EtatDuJeu = _EtatDemarrer;
				_pGame->musique = rand() % 10;
				mciSendString("stop bakamitai", NULL, 0, _pGame->GetWindow());
				std::string seek = "seek " + std::to_string(_pGame->musique) + " to start";
				std::string play = "play " + std::to_string(_pGame->musique) + " notify";
				mciSendString(seek.c_str(), NULL, 0, NULL);
				mciSendString(play.c_str(), NULL, 0, _pGame->GetWindow());
				Unite* general2 = tabGeneraux.at(selectedGeneral[1])->clone();
				general2->SetPosition(spawnGeneral);
				general2->switchSide();
				tabUnites.push_back(general2);
				//Unité bonus de Konrad de Velours
				ajouterVelours(tabUnites, selectedGeneral, tabGeneraux[5]);
			}
		}
		else if (_pPrecedent->IsPointInside(x, y))
		{
			if (_EtatDuJeu == _EtatChoixGeneral1)
			{
				if (selectedGeneral[0] == 0)
					selectedGeneral[0] = 4;
				else
					selectedGeneral[0]--;
			}
			else if (_EtatDuJeu == _EtatChoixGeneral2)
			{
				if (selectedGeneral[1] == 0)
					selectedGeneral[1] = 4;
				else
					selectedGeneral[1]--;
				if (selectedGeneral[0] == selectedGeneral[1])
				{
					if (selectedGeneral[1] == 0)
						selectedGeneral[1] = 4;
					else
						selectedGeneral[1]--;
				}
			}
			else if (_EtatDuJeu == _EtatInstructions1)
				_EtatDuJeu = _EtatDebutJeu;
			else if (_EtatDuJeu == _EtatInstructions2)
				_EtatDuJeu = _EtatInstructions1;
			else if (_EtatDuJeu == _EtatInstructions3)
				_EtatDuJeu = _EtatInstructions2;
			else
				_EtatDuJeu = _EtatHistoire;
		}
		else if (_pBtnNextUnit->IsPointInside(x, y))
		{
		selectedUnit = findNextUnit(tabUnites, selectedUnit);
		focusUnite(tabUnites.at(selectedUnit), _pFondMap);
		clearUnites(tabUnites);
		}
		else if (_pBtnFinTour->IsPointInside(x, y))
		{
			clearUnites(tabUnites);
			casesParcourues.clear();
			selectedUnit = -1;
			pressedShift = false;
			etatActif = -1;
			if(actifDelay[nbTours % 2] > 0)
				actifDelay[nbTours % 2]--;
			switchPlayer(tabUnites, nbTours);
		}
		else if (_pBtnActif->IsPointInside(x, y))
		{
			//Actif
			clearUnites(tabUnites);
			selectedUnit = -1;
			pressedShift = false;
			useActif(tabUnites, selectedGeneral[nbTours % 2]);
		}
		else if (_pBtnAttaquer->IsPointInside(x,y))
		{
		clearUnites(tabUnites);
		etatAttaquer = true;
		tabUnites.at(selectedUnit)->attaquer(_pCaseAttaque, tabUnites, tabUnites.at(selectedUnit)->GetPosition(), tabGeneraux);
		}
		else if (_pBtnDeplacer->IsPointInside(x, y))
		{
		clearUnites(tabUnites);
		etatAttaquer = false;
		tabUnites.at(selectedUnit)->deplacer(_pCaseDispo, tabUnites, 0, tabUnites.at(selectedUnit)->GetPosition(), casesParcourues, selectedGeneral[nbTours % 2], typeCase);
		}
		else if (_pSideBar->IsPointInside(x, y))
		{
			//Empêcher les actions sous la barre latérale
		}
		else if (etatActif != -1)
		{
			//Actif
			if (Unite::IsCaseInside(positionEcran, tabUnites, x, y) != -1)
			{
				int indice = Unite::IsCaseInside(positionEcran, tabUnites, x, y);
				switch (etatActif)
				{
				case 0:
					soutienDuLoliFanberg(tabUnites.at(indice));
					clearUnites(tabUnites);
					etatActif = -1;
					actifDelay[nbTours % 2] = generalActifDelai[selectedGeneral[nbTours % 2]];
					break;
				case 1:
					infirmiereDuCouvent(tabUnites.at(indice));
					clearUnites(tabUnites);
					etatActif = -1;
					actifDelay[nbTours % 2] = generalActifDelai[selectedGeneral[nbTours % 2]];
					break;
				case 3:
					assassin(tabUnites.at(indice));
					clearUnites(tabUnites);
					etatActif = -1;
					actifDelay[nbTours % 2] = generalActifDelai[selectedGeneral[nbTours % 2]];
					break;
				case 4:
					if (selectedUnit == -1)
						selectedUnit = stalkerChoisirDest(tabUnites.at(indice),typeCase);
					else
					{
						stalker(tabUnites.at(selectedUnit),tabUnites.at(indice));
						clearUnites(tabUnites);
						etatActif = -1;
						actifDelay[nbTours % 2] = generalActifDelai[selectedGeneral[nbTours % 2]];
					}
					break;
				}
			}
		}
		else if (Unite::IsCaseInside(positionEcran, tabUnites, x, y) != -1)
		{
			int indice = Unite::IsCaseInside(positionEcran, tabUnites, x, y);
			if (etatAttaquer)
			{
				//attaquer
				Unite* cible = Unite::getUnitAtPos(tabUnites, tabUnites.at(indice)->GetPosition());
				if (cible != nullptr)
				{
					tabUnites.at(selectedUnit)->attack();
					PlaySound((LPCSTR)tabUnites.at(selectedUnit)->getSon(), _hInstance, SND_RESOURCE | SND_ASYNC);
					//Si tu attaques, tu ne peux plus te déplacer
					tabUnites.at(selectedUnit)->move();
					if (cible->damage(tabUnites.at(selectedUnit)->getDegats(), tabUnites.at(selectedUnit)->getUType(), selectedGeneral[nbTours % 2], generalMort, nbTours))
					{
						nbKillsParType[tabUnites.at(selectedUnit)->getUType() - 1]++;
						indice = Unite::IsUnitInside(positionEcran, tabUnites, x, y);
						tabUnites.erase(tabUnites.begin() + indice);
						if (hasWon(tabUnites))
						{
							win();
						}
					}
				}
			}
			else
			{
				//deplacer
				tabUnites.at(selectedUnit)->SetPosition(tabUnites.at(indice)->GetPosition());
				tabUnites.at(selectedUnit)->move();
				//Si c'est un canon, il ne pourra pas attaquer ce tour-ci
				if (tabUnites.at(selectedUnit)->getUType() == 4)
					tabUnites.at(selectedUnit)->attack();
			}
			clearUnites(tabUnites);
			casesParcourues.clear();
			selectedUnit = -1;
			pressedShift = false;
		}
		else if (Unite::IsUnitInside(positionEcran, tabUnites, x, y) != -1)
		{
			int indice = Unite::IsUnitInside(positionEcran, tabUnites, x, y);
			if (tabUnites.at(indice)->getUType() != 0)
			{
				etatAttaquer = false;
				clearUnites(tabUnites);
				casesParcourues.clear();
				//Enlever toutes les cases
				if (selectedUnit != indice && tabUnites.at(indice)->isAllie())
				{
					if (tabUnites.at(indice)->isAllie())
					{
						if (tabUnites.at(indice)->hasMoved())
							etatAttaquer = true;
						if (!tabUnites.at(indice)->hasAttacked() && etatAttaquer)
						{
								selectedUnit = indice;
								tabUnites.at(indice)->attaquer(_pCaseAttaque, tabUnites, tabUnites.at(indice)->GetPosition(), tabGeneraux);
						}
						else if (!tabUnites.at(indice)->hasMoved())
						{
							etatAttaquer = false;
							selectedUnit = indice;
							tabUnites.at(indice)->deplacer(_pCaseDispo, tabUnites, 0, tabUnites.at(indice)->GetPosition(), casesParcourues, selectedGeneral[nbTours % 2], typeCase);
						}
					}
				}
				else
					selectedUnit = -1;
				pressedShift = false;
			}
		}
	}
}

void MouseMove(int x, int y)
{

}

std::vector<Unite*> fillTableau()
{
	std::vector<Unite*> tab;
	POINT pos;
//Mode standard ou mode démo
	if (jeuDemo)
	{
		//Infanterie
		pos.x = 16;
		pos.y = 9;
		tab.push_back(new Unite(_pInfanterie, pos, 1, true));
		pos.y = 14;
		tab.push_back(new Unite(_pInfanterie, pos, 1, false));
		//Arquebusiers
		pos.x = 15;
		pos.y = 9;
		tab.push_back(new Unite(_pArquebuse, pos, 2, true));
		pos.x = 17;
		pos.y = 14;
		tab.push_back(new Unite(_pArquebuse, pos, 2, false));
		//Cavalerie
		pos.x = 18;
		pos.y = 8;
		tab.push_back(new Unite(_pCavalerie, pos, 3, true));
		pos.x = 14;
		pos.y = 15;
		tab.push_back(new Unite(_pCavalerie, pos, 3, false));
		//Canon
		pos.x = 16;
		pos.y = 8;
		tab.push_back(new Unite(_pCanon, pos, 4, true));
		pos.y = 15;
		tab.push_back(new Unite(_pCanon, pos, 4, false));
	}
	else
	{
		//Joueur 1
	//Infanterie
		for (pos.x = 13; pos.x < 15; pos.x++)
			for (pos.y = 5; pos.y < 8; pos.y++)
				tab.push_back(new Unite(_pInfanterie, pos, 1, true));
		for (pos.x = 20; pos.x < 22; pos.x++)
			for (pos.y = 5; pos.y < 8; pos.y++)
				tab.push_back(new Unite(_pInfanterie, pos, 1, true));
		for (pos.x = 30; pos.x < 32; pos.x++)
			for (pos.y = 4; pos.y < 6; pos.y++)
				tab.push_back(new Unite(_pInfanterie, pos, 1, true));
		//Arquebusiers
		for (pos.y = 3; pos.y < 5; pos.y++)
		{
			for (pos.x = 15; pos.x < 17; pos.x++)
				tab.push_back(new Unite(_pArquebuse, pos, 2, true));
			for (pos.x = 18; pos.x < 20; pos.x++)
				tab.push_back(new Unite(_pArquebuse, pos, 2, true));
		}
		pos.y = 3;
		for (pos.x = 30; pos.x < 32; pos.x++)
			tab.push_back(new Unite(_pArquebuse, pos, 2, true));
		//Cavalerie
		pos.y = 5;
		for (pos.x = 10; pos.x < 13; pos.x++)
			tab.push_back(new Unite(_pCavalerie, pos, 3, true));
		for (pos.x = 22; pos.x < 25; pos.x++)
			tab.push_back(new Unite(_pCavalerie, pos, 3, true));
		//Canon
		pos.x = 17;
		pos.y = 1;
		tab.push_back(new Unite(_pCanon, pos, 4, true));
		pos.y++;
		for (pos.x = 15; pos.x < 20; pos.x += 4)
			tab.push_back(new Unite(_pCanon, pos, 4, true));

		//Joueur 2
			//Infanterie
		for (pos.y = 22; pos.y < 25; pos.y++)
		{
			for (pos.x = 19; pos.x < 21; pos.x++)
				tab.push_back(new Unite(_pInfanterie, pos, 1, false));
			for (pos.x = 26; pos.x < 28; pos.x++)
				tab.push_back(new Unite(_pInfanterie, pos, 1, false));
		}
		for (pos.y = 23; pos.y < 25; pos.y++)
			for (pos.x = 33; pos.x < 35; pos.x++)
				tab.push_back(new Unite(_pInfanterie, pos, 1, false));
		//Arquebusiers
		for (pos.y = 23; pos.y < 26; pos.y++)
		{
			for (pos.x = 21; pos.x < 23; pos.x++)
				tab.push_back(new Unite(_pArquebuse, pos, 2, false));
			for (pos.x = 24; pos.x < 26; pos.x++)
				tab.push_back(new Unite(_pArquebuse, pos, 2, false));
		}
		pos.y = 25;
		for (pos.x = 33; pos.x < 35; pos.x++)
			tab.push_back(new Unite(_pArquebuse, pos, 2, false));
		//Cavalerie
		pos.y = 25;
		for (pos.x = 19; pos.x < 21; pos.x++)
			tab.push_back(new Unite(_pCavalerie, pos, 3, false));
		for (pos.x = 26; pos.x < 28; pos.x++)
			tab.push_back(new Unite(_pCavalerie, pos, 3, false));
		pos.y++;
		for (pos.x = 20; pos.x < 27; pos.x += 6)
			tab.push_back(new Unite(_pCavalerie, pos, 3, false));
		//Canon
		for (pos.x = 21; pos.x < 26; pos.x += 4)
			tab.push_back(new Unite(_pCanon, pos, 4, false));
		pos.y++;
		pos.x = 23;
		tab.push_back(new Unite(_pCanon, pos, 4, false));
	}

	return tab;
}

std::vector<Unite*> fillGeneraux()
{
	std::vector<Unite*> tab;
	//Position de départ du général du joueur 1
	POINT pos;
	pos.x = 19;
	pos.y = 1;
	//Généraux à ajouter
	Unite* amir = new Unite(_pAmir, pos, 5, true);
	amir->setPortee(4);
	Unite* anfray = new Unite(_pAnfray, pos, 5, true);
	anfray->setDeplacement(6);
	Unite* konrad = new Unite(_pKonrad, pos, 5, true);
	konrad->setMaxHp(500);
	Unite* luigi = new Unite(_pLuigi, pos, 5, true);
	luigi->setDeplacement(3);
	luigi->setDegats(80);
	luigi->setPortee(2);
	Unite* rodrich = new Unite(_pRodrich, pos, 5, true);
	rodrich->setDegats(90);
	Unite* velours = new Unite(_pVelours, pos, 5, true);
	tab.push_back(amir);
	tab.push_back(anfray);
	tab.push_back(konrad);
	tab.push_back(luigi);
	tab.push_back(rodrich);
	tab.push_back(velours);
	return tab;
}

void fillCases(short typeCases[][29])
{
	//Attention, c'est pas beau à voir
//Setter les cases à 0
	for (int x = 0; x < 38; x++)
	{
		for (int y = 0; y < 29; y++)
			typeCases[x][y] = 0;
	}
	//0 = libre, 1 = difficile, 2 = inaccessible
//Obstacles nord
	int y = 0, x = 7;
	typeCases[x][y] = 2;
	x += 4;
	typeCases[x][y] = 2;
	for (int y = 2; y < 4; y++)
	{
		typeCases[7][y] = 2;
	}
	typeCases[8][3] = 1;
	typeCases[9][1] = 2;
	typeCases[9][2] = 1;
	for (int x = 9; x < 11; x++)
	{
		for (int y = 2; y < 4; y++)
		{
			typeCases[x][y] = 2;
		}
	}
	for (int y = 5; y < 7; y++)
	{
		for (int x = 2; x < 4; x++)
		{
			typeCases[x][y] = 1;
		}
		for (int x = 7; x < 9; x++)
		{
			typeCases[x][y] = 1;
		}
	}
	for (int x = 10; x < 13; x++)
	{
		for (int y = 6; y < 9; y++)
		{
			typeCases[x][y] = 1;
		}
	}
	typeCases[19][1] = 1;
	for (int y = 3; y < 5; y++)
	{
		for (int x = 13; x < 15; x++)
		{
			typeCases[x][y] = 1;
		}
		for (int x = 21; x < 23; x++)
		{
			typeCases[x][y] = 1;
		}
	}
	for (int x = 27; x < 30; x++)
	{
		for (int y = 2; y < 5; y++)
		{
			typeCases[x][y] = 1;
		}
	}
	for (int y = 6; y < 8; y++)
	{
		typeCases[22][y] = 2;
		for (int x = 29; x < 31; x++)
		{
			typeCases[x][y] = 1;
		}
	}
//Rivière
	for (int x = 0; x < 2; x++)
		typeCases[x][11] = 2;
	for (int x = 2; x < 12; x++)
		typeCases[x][12] = 2;
	for (int x = 12; x < 16; x++)
		typeCases[x][11] = 2;
	for (int x = 17; x < 22; x++)
		typeCases[x][10] = 2;
	for (int x = 22; x < 32; x++)
		typeCases[x][11] = 2;
	for (int x = 0; x < 3; x++)
		typeCases[x][14] = 2;
	for (int x = 3; x < 11; x++)
		typeCases[x][15] = 2;
	for (int x = 11; x < 15; x++)
		typeCases[x][14] = 2;
	for (int y = 12; y < 14; y++)
		typeCases[15][y] = 2;
	for (int y = 11; y < 13; y++)
		typeCases[17][y] = 2;
	for (int x = 17; x < 32; x++)
		typeCases[x][13] = 2;
	for (int x = 32; x < 34; x++)
	{
		typeCases[x][10] = 2;
		typeCases[x][14] = 2;
	}
	for (int y = 11; y < 14; y++)
		typeCases[34][y] = 2;
	for (int x = 36; x < 38; x++)
		typeCases[x][10] = 2;
	for (int y = 11; y < 13; y++)
		typeCases[36][y] = 2;
	typeCases[37][12] = 2;
//Obstacles sud
	for (int x = 3; x < 5; x++)
		for (int y = 17; y < 19; y++)
			typeCases[x][y] = 1;
	for (int y = 23; y < 25; y++)
		typeCases[5][y] = 1;
	for (int x = 12; x < 14; x++)
		for (int y = 19; y < 21; y++)
			typeCases[x][y] = 1;
	for (int x = 13; x < 16; x++)
		for (int y = 22; y < 25; y++)
			typeCases[x][y] = 1;
	for (int x = 13; x < 15; x++)
		for (int y = 26; y < 28; y++)
			typeCases[x][y] = 1;
	for (int x = 20; x < 22; x++)
		for (int y = 18; y < 20; y++)
			typeCases[x][y] = 1;
	for (int x = 24; x < 26; x++)
		for (int y = 16; y < 18; y++)
			typeCases[x][y] = 1;
	for (int x = 28; x < 30; x++)
		for (int y = 24; y < 26; y++)
			typeCases[x][y] = 1;
	typeCases[30][17] = 2;
	for (int x = 29; x < 33; x++)
		typeCases[x][18] = 2;
	for (int x = 32; x < 34; x++)
		typeCases[x][19] = 2;
	for (int y = 20; y < 22; y++)
		typeCases[33][y] = 2;
//Falaises
	//Chute nord
	for (int x = 36; x < 38; x++)
		for (int y = 0; y < 6; y++)
			typeCases[x][y] = 1;
	for (int x = 35; x < 37; x++)
		for (int y = 4; y < 9; y++)
			typeCases[x][y] = 1;
	for (int y = 5; y < 11; y++)
		typeCases[34][y] = 1;
	typeCases[33][8] = 1;
	for (int x = 32; x < 36; x++)
		typeCases[x][9] = 1;
	typeCases[31][10] = 1;
	//Chute sud
	typeCases[31][14] = 1;
	typeCases[34][14] = 1;
	for (int x = 31; x < 35; x++)
		typeCases[x][15] = 1;
	for (int x = 32; x < 36; x++)
		typeCases[x][16] = 1;
	for (int x = 34; x < 37; x++)
		for (int y = 17; y < 19; y++)
			typeCases[x][y] = 1;
	for (int x = 35; x < 38; x++)
		for (int y = 19; y < 26; y++)
			typeCases[x][y] = 1;
	for (int x = 36; x < 38; x++)
		for (int y = 26; y < 29; y++)
			typeCases[x][y] = 1;
	//Colline sud-ouest
	for (int x = 4; x < 8; x++)
		typeCases[x][20] = 1;
	for (int x = 3; x < 5; x++)
		for (int y = 21; y < 29; y++)
			typeCases[x][y] = 1;
	for (int x = 5; x < 9; x++)
		for (int y = 21; y < 23; y++)
			typeCases[x][y] = 1;
	typeCases[7][23] = 1;
	for (int x = 8; x < 10; x++)
		for (int y = 23; y < 29; y++)
			typeCases[x][y] = 1;
	for (int y = 27; y < 29; y++)
		typeCases[10][y] = 1;
}

void ajouterVelours(std::vector<Unite*>& tab, int selectedGeneral[], Unite* velours)
{
	POINT pos;
	if (selectedGeneral[0] == 2)
	{
		pos.x = 18;
		pos.y = 2;
		Unite* veloursP1 = velours->clone();
		veloursP1->SetPosition(pos);
		tab.push_back(veloursP1);
	}
	else if (selectedGeneral[1] == 2)
	{
		pos.x = 22;
		pos.y = 26;
		Unite* veloursP2 = velours->clone();
		veloursP2->SetPosition(pos);
		veloursP2->switchSide();
		tab.push_back(veloursP2);
	}
}



void afficherUnites(HDC hDC, std::vector<Unite*> tab, Bitmap* hpBar, Bitmap* hpDecile)
{
	int taille = tab.size();
	for (int i = 0; i < taille; i++)
	{
		int x = tab.at(i)->GetPosition().x - positionEcran.x;
		int y = tab.at(i)->GetPosition().y - positionEcran.y;
		if (x < 10 && y < 8)
		{
			tab.at(i)->getSprite()->SetPosition(x * 100, y * 100);
			tab.at(i)->getSprite()->Draw(hDC, TRUE, RGB(219, 255, 0));
			if (tab.at(i)->getUType() != 0)
			{
				hpBar->Draw(hDC, x * 100 + 6, y * 100 + 87);
				tab.at(i)->drawMiniHp(hDC, hpDecile, x, y);
			}
			if (tab.at(i)->isAllie())
			{
				//Afficher l'état de l'unité
				if (tab.at(i)->hasAttacked())
					_pMarkRouge->Draw(hDC, x * 100 + 85, y * 100 + 5, TRUE, RGB(255, 255, 255));
				else if (tab.at(i)->hasMoved())
					_pMarkJaune->Draw(hDC, x * 100 + 85, y * 100 + 5, TRUE, RGB(255, 255, 255));
				else
					_pMarkVert->Draw(hDC, x * 100 + 85, y * 100 + 5, TRUE, RGB(255, 255, 255));
			}
		}
	}
}

void clearUnites(std::vector<Unite*>& tab)
{
	for (int i = tab.size() - 1; i >= 0; i--)
	{
		//Retirer toutes les cases du vecteur
		if (tab.at(i)->getUType() == 0)
		{
			tab.erase(tab.begin() + i);
		}
	}
}

void switchPlayer(std::vector<Unite*> tab, int &nbTours)
{
	nbTours++;
	for (int i = tab.size() - 1; i >= 0; i--)
	{
		//Réinitialiser les actions des unités
		tab.at(i)->reset();
		tab.at(i)->switchSide();
		//Capacité passive d'Anfray
		if (selectedGeneral[nbTours % 2] == 1 && tab.at(i)->isAllie())
			tab.at(i)->heal(20);
	}
}

bool hasWon(std::vector<Unite*> tab)
{
	bool victoire = true;
	for (int i = 0; i < tab.size(); i++)
	{
		if (!tab.at(i)->isAllie() && tab.at(i)->getUType() != 0)
		{
			victoire = false;
			i = tab.size();
		}
	}
	return victoire;
}

void useActif(std::vector<Unite*>& tabUnites, int selectedGeneral)
{
	if (etatActif == -1)
	{
		switch (selectedGeneral)
		{
		case 0:
			//Amir Fanberg
			POINT pos;
			for (int i = 0; i < 38; i++)
			{
				pos.x = i;
				for (int j = 0; j < 40; j++)
				{
					pos.y = j;
					Unite* caseAttaque = new Unite(_pCaseAttaque, pos, 0, false);
					tabUnites.push_back(caseAttaque);
				}
			}
			break;
		case 1:
			//Anfray Brunissende
			for (int i = 0; i < tabUnites.size(); i++)
			{
				if (tabUnites.at(i)->isAllie())
				{
					Unite* caseSoin = new Unite(_pCaseSoin, tabUnites.at(i)->GetPosition(), 0, false);
					tabUnites.push_back(caseSoin);
				}
			}
			break;
		case 3:
			//Luigi Dumoulin
			for (int i = 0; i < tabUnites.size(); i++)
			{
				if (tabUnites.at(i)->getUType() == 5 && tabUnites.at(i)->isAllie())
				{
					Unite* caseAttaque = new Unite(_pCaseAttaque, tabUnites.at(i)->GetPosition(), 0, false);
					tabUnites.push_back(caseAttaque);
				}
			}
			break;
		case 4:
			//Rodrich Judas
			for (int i = 0; i < tabUnites.size(); i++)
			{
				if (tabUnites.at(i)->isAllie())
				{
					Unite* caseSelection = new Unite(_pCaseDispo, tabUnites.at(i)->GetPosition(), 0, false);
					tabUnites.push_back(caseSelection);
				}
			}
			break;
		}
		etatActif = selectedGeneral;
	}
	else
		etatActif = -1;
}

void soutienDuLoliFanberg(Unite* caseSelectionnee)
{
	PlaySound((LPCSTR)IDW_LOLI_FANBERG, _hInstance, SND_RESOURCE | SND_ASYNC);
	for (int x = -2; x <= 2; x++)
	{
		for (int y = -2; y <= 2; y++)
		{
			int disTotal = abs(x) + abs(y);
			if (disTotal <= 2)
			{
				POINT posAttaque = caseSelectionnee->GetPosition();
				posAttaque.x += x;
				posAttaque.y += y;
				if (Unite::getUnitAtPos(tabUnites,posAttaque) != nullptr)
				{
					Unite * cible = Unite::getUnitAtPos(tabUnites, posAttaque);
					if (cible->damage(40, 0, -1, generalMort, nbTours))
					{
						nbKillsParType[5]++;
						int indice = Unite::getIndex(tabUnites, cible);
						tabUnites.erase(tabUnites.begin() + indice);
						if (hasWon(tabUnites))
						{
							win();
						}
					}
				}
			}
		}
	}
}

void infirmiereDuCouvent(Unite* caseSelectionnee)
{
	PlaySound((LPCSTR)IDW_SOIN, _hInstance, SND_RESOURCE | SND_ASYNC);
	Unite* cible = Unite::getUnitAtPos(tabUnites, caseSelectionnee->GetPosition());
	cible->heal(9999);
}

void assassin(Unite* caseSelectionnee)
{
	PlaySound((LPCSTR)IDW_ASSASSIN, _hInstance, SND_RESOURCE | SND_ASYNC);
	POINT pos = caseSelectionnee->GetPosition();
	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			if ((abs(i) + abs(j) == 1))
			{
				POINT newPos = pos;
				newPos.x += i;
				newPos.y += j;
				if (Unite::getUnitAtPos(tabUnites, newPos) != nullptr)
				{
					Unite* cible = Unite::getUnitAtPos(tabUnites, newPos);
					if (!cible->isAllie())
					{
						if (cible->damage(100, 0, -1, generalMort, nbTours))
						{
							nbKillsParType[5]++;
							int indice = Unite::getIndex(tabUnites, cible);
							tabUnites.erase(tabUnites.begin() + indice);
							if (hasWon(tabUnites))
							{
								win();
							}
						}
					}
				}
			}
		}
	}
}

int stalkerChoisirDest(Unite* caseSelectionnee, short typeCase[][29])
{
	int index = -1;
	Unite* source = Unite::getUnitAtPos(tabUnites, caseSelectionnee->GetPosition());
	if (source != nullptr)
	{
		index = Unite::getIndex(tabUnites, source);
		clearUnites(tabUnites);
		for (int i = tabUnites.size() - 1; i >= 0; i--)
		{
			if (i != index)
			{
				POINT pos = tabUnites.at(i)->GetPosition();
				pos.y--;
				if (pos.y >= 0 && !Unite::isOccupe(pos,tabUnites) && (typeCase[pos.x][pos.y] == 0 || (typeCase[pos.x][pos.y] == 1 && (source->getUType() == 1 || source->getUType() == 2))))
				{
					Unite* caseDest = new Unite(_pCaseDispo, pos, 0, false);
					tabUnites.push_back(caseDest);
				}
				pos.y += 2;
				if (pos.y < 40 && !Unite::isOccupe(pos, tabUnites) && (typeCase[pos.x][pos.y] == 0 || (typeCase[pos.x][pos.y] == 1 && (source->getUType() == 1 || source->getUType() == 2))))
				{
					Unite* caseDest = new Unite(_pCaseDispo, pos, 0, false);
					tabUnites.push_back(caseDest);
				}
				pos.y--;
				pos.x--;
				if (pos.x >= 0 && !Unite::isOccupe(pos, tabUnites) && (typeCase[pos.x][pos.y] == 0 || (typeCase[pos.x][pos.y] == 1 && (source->getUType() == 1 || source->getUType() == 2))))
				{
					Unite* caseDest = new Unite(_pCaseDispo, pos, 0, false);
					tabUnites.push_back(caseDest);
				}
				pos.x += 2;
				if (pos.y < 38 && !Unite::isOccupe(pos, tabUnites) && (typeCase[pos.x][pos.y] == 0 || (typeCase[pos.x][pos.y] == 1 && (source->getUType() == 1 || source->getUType() == 2))))
				{
					Unite* caseDest = new Unite(_pCaseDispo, pos, 0, false);
					tabUnites.push_back(caseDest);
				}
			}
		}
	}
	return index;
}

void stalker(Unite* source, Unite* dest)
{
	PlaySound((LPCSTR)IDW_STALKER, _hInstance, SND_RESOURCE | SND_ASYNC);
	source->SetPosition(dest->GetPosition());
}

int findNextUnit(std::vector<Unite*> tab, int indice)
{
	do
	{
		if (indice == tab.size() - 1)
			indice = 0;
		else
			indice++;

	} while (!tab.at(indice)->isAllie());
	return indice;
}

void focusUnite(Unite* selection, Sprite* fond)
{
	positionEcran = selection->GetPosition();
	POINT fondPos;
	fondPos.y = positionEcran.y * -100;
	fondPos.x = positionEcran.x * -100;
	fond->SetPosition(fondPos);
	int x = 0;
	int y = 0;
	const int STEP = 100;
	while (positionEcran.x > 28)
	{
		x += STEP;
		positionEcran.x--;
	}
	while (positionEcran.y > 21)
	{
		y += STEP;
		positionEcran.y--;
	}
	fond->OffsetPosition(x, y);
}

void win()
{
	//Mettre à jour les records
	plusBasNbTours = nbTours / 2 < plusBasNbTours / 2 ? nbTours / 2 : plusBasNbTours;
	int nbUnitesRestantes = Unite::compterUnites(tabUnites);
	plusGrandNbUnites = nbUnitesRestantes > plusGrandNbUnites ? nbUnitesRestantes : plusGrandNbUnites;
	for (int i = 0; i < 5; i++)
	{
		if (nbKillsParType[i] > plusGrandNbKillsUnit)
		{
			plusGrandNbKillsUnit = nbKillsParType[i];
			typeUnitePlusDeKills = i + 1;
		}
	}
	clearUnites(tabUnites);
	int nbUnites = 0;
	for (int i = 0; i < tabUnites.size(); i++)
		if (tabUnites.at(i)->isAllie())
			nbUnites++;
	_pFondMap->SetPosition(0, 0);
	tabUnites.clear();
	selectedGeneral[0] = 0;
	selectedGeneral[1] = 0;
	actifDelay[0] = 0;
	actifDelay[1] = 0;
	etatActif = -1;
	selectedUnit = -1;
	pressedShift = false;
	nbTours = 0;
	positionEcran = { 0,0 };
	generalMort[0] = false;
	generalMort[1] = false;
	//Gérer les records
	ecrireStats();
	std::string stop = "stop " + std::to_string(_pGame->musique);
	_pGame->musique = -1;
	mciSendString(stop.c_str(), NULL, 0, _pGame->GetWindow());
	mciSendString("seek bakamitai to start", NULL, 0, NULL);
	mciSendString("play bakamitai notify", NULL, 0, _pGame->GetWindow());
	_EtatDuJeu = _EtatOptions;
}

void lireStats()
{
	std::ifstream fichierRecords;
	fichierRecords.open("records.txt", std::ios::in);
	fichierRecords >> plusBasNbTours >> plusGrandNbUnites >> typeUnitePlusDeKills >> plusGrandNbKillsUnit;
	fichierRecords.close();
}

void ecrireStats()
{
	std::ofstream fichierRecords;
	fichierRecords.open("records.txt", std::ios::out | std::ios::trunc);
	fichierRecords << plusBasNbTours << std::endl;
	fichierRecords << plusGrandNbUnites << std::endl;
	fichierRecords << typeUnitePlusDeKills << std::endl;
	fichierRecords << plusGrandNbKillsUnit << std::endl;
	fichierRecords.close();
}