/**
* \file UIHandler.cpp
* \author Matthias Birnthaler
* \date 19 May 2019
* \brief Implementation UI logic for shop interface mod 
*
*/


/* =================================================[includes]================================================= */
#include "UIHandler.h"
#include "json.hpp"
#include "Store.h"


namespace UIHandler
{
	/* ===================================== [prototype of local functions] ======================================= */
	static void  Hook_AShooterGameState_HTTPPostRequest(AShooterGameState* _this, FString InURL, FString Content);


	/* ===================================== [definition of local functions] ====================================== */

	/**
	* \brief Hooks AShooterGameState_HTTPPostRequest 
	*
	* This function counts all slots of a tribe that are not expired
	*
	* \param[in] AShooterGameState; not used 
	* \param[in] InURL target url 
	* \param[in] Content content
	* \return void 
	*/
	static void  Hook_AShooterGameState_HTTPPostRequest(AShooterGameState* _this, FString InURL, FString Content)
	{
		/*{ "SteamID" : 76561198253555660 , "ItemID" : "Crate1" } */

		uint64 steam_id = 0 ;
		FString ItemID;

		/*   { "SteamID" : 76561198253555660 , "ItemID" : "Crate1" }    */
		/*    ^         ^ ^                 ^ ^        ^ ^        ^     */
		/*   0    1      2        3          4    5     6     7     8   */


		TArray<FString> parsed;
		Content.ParseIntoArray(parsed, L" ", true);

		if ((true == parsed.IsValidIndex(0)) &&
			(true == parsed.IsValidIndex(1)) &&
			(true == parsed.IsValidIndex(2)) &&
			(true == parsed.IsValidIndex(3)) &&
			(true == parsed.IsValidIndex(4)) &&
			(true == parsed.IsValidIndex(5)) &&
			(true == parsed.IsValidIndex(6)) &&
			(true == parsed.IsValidIndex(7)) &&
			(true == parsed.IsValidIndex(8))   )
		{
			try
			{
				 steam_id = std::stoull(parsed[3].ToString().c_str());
			}
			catch (const std::exception& exception)
			{
				Log::GetLog()->error("Shop UI: can not determine steamid: {}", parsed[3].ToString());
			}

			TArray<FString> parsed1;
			parsed[7].ParseIntoArray(parsed1, L"\"", true);
		
			if (true == parsed1.IsValidIndex(0))
			{
				ItemID = parsed1[0];
			}


		}

		AShooterPlayerController* player_controller = ArkApi::GetApiUtils().FindPlayerFromSteamId(steam_id);

		if (nullptr != player_controller)
		{
			ArkShop::Store::Buy(player_controller, ItemID, 1 );
		
		}
		else
		{
			Log::GetLog()->error("PostRequest SteamId wrong steam64 {}", steam_id);
		}

		AShooterGameState_HTTPPostRequest_original(_this, InURL, Content);
	}


	/* ===================================== [definition of global functions] ===================================== */

	/**
	* \brief Initialisation of the needed hooks for the ui interface 
	*
	* This function intialisze all hooks for the interface logic
	*
	* \return void
	*/
	void UIHandler_InitHooks(void)
	{
		ArkApi::GetHooks().SetHook("AShooterGameState.HTTPPostRequest",
			&Hook_AShooterGameState_HTTPPostRequest,
			&AShooterGameState_HTTPPostRequest_original);
	}


	/**
	* \brief Remove of the needed hooks for the ui interface
	*
	* This function removes all hooks for the interface logic
	*
	* \return void
	*/
	void UIHandler_RemoveHooks(void)
	{
		ArkApi::GetHooks().DisableHook("AShooterGameState.HTTPPostRequest",
			&Hook_AShooterGameState_HTTPPostRequest);

	}

} /* namespace UIHandler */