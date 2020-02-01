/**
* \file UIHandler.h
* \author Matthias Birnthaler
* \date 19 May 2019
* \brief Implementation UI logic for shop interface mod
*
*/


#ifndef UIHANDLER_H
#define UIHANDLER_H


/* =================================================[includes]================================================= */
#include "API/ARK/Ark.h"

/**< \brief declare of AShooterPlayerState_AddToTribe Hook */
DECLARE_HOOK(AShooterGameState_HTTPPostRequest, void, AShooterGameState*, FString, FString);


namespace UIHandler
{
	/* ================================================[declaration of public functions]========================= */
	extern void UIHandler_InitHooks(void);
	extern void UIHandler_RemoveHooks(void);

} /* namespace UIHandler */ 


#endif /* UIHANDLER_H */

/* =================================================[end of file]================================================= */