////////////////////////////////////////////////////////////////////////////////////////////////////////
// Part of Injectable Generic Camera System
// Copyright(c) 2017, Frans Bouma
// All rights reserved.
// https://github.com/FransBouma/InjectableGenericCameraSystem
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met :
//
//  * Redistributions of source code must retain the above copyright notice, this
//	  list of conditions and the following disclaimer.
//
//  * Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and / or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED.IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "InterceptorHelper.h"
#include "GameConstants.h"
#include "GameImageHooker.h"
#include <map>
#include "MessageHandler.h"
#include "CameraManipulator.h"
#include "Globals.h"

using namespace std;

//--------------------------------------------------------------------------------------------------------------------------------
// external asm functions
extern "C" {
	void pmStructAddressInterceptor();
	void activeCamAddressInterceptor();
	void activeCamWrite1Interceptor();
	void resolutionStructAddressInterceptor();
}

// external addresses used in asm.
extern "C" {
	LPBYTE _pmStructAddressInterceptionContinue = nullptr;
	LPBYTE _activeCamAddressInterceptionContinue = nullptr;
	LPBYTE _activeCamWrite1InterceptionContinue = nullptr;
	LPBYTE _resolutionStructAddressInterceptionContinue = nullptr;
}


namespace IGCS::GameSpecific::InterceptorHelper
{
	void initializeAOBBlocks(LPBYTE hostImageAddress, DWORD hostImageSize, map<string, AOBBlock*> &aobBlocks)
	{
		aobBlocks[ACTIVECAM_ADDRESS_INTERCEPT_KEY] = new AOBBlock(ACTIVECAM_ADDRESS_INTERCEPT_KEY, "0F 11 42 10 48 8B 03 | FF 90 58 02 00 00 F3 0F 11 46 20 48 8D 54 24 20 48 8B 03 48 8B CB", 1);
		aobBlocks[ACTIVECAM_CAMERA_WRITE1_INTERCEPT_KEY] = new AOBBlock(ACTIVECAM_CAMERA_WRITE1_INTERCEPT_KEY, "F2 0F 11 83 E0 00 00 00 0F 28 44 24 30 89 8B E8 00 00 00 0F 11 83 F0 00 00 00", 2);	// 2 entries, we need the second one
		aobBlocks[PMSTRUCT_ADDRESS_INTERCEPT_KEY] = new AOBBlock(PMSTRUCT_ADDRESS_INTERCEPT_KEY, "0F 11 BE C0 01 00 00 F3 44 0F11 9E D0 01 00 00 F3 44 0F 11 96 D4 01 00 00", 1);
		aobBlocks[COORD_FACTOR_ADDRESS_KEY] = new AOBBlock(COORD_FACTOR_ADDRESS_KEY, "F3 44 0F 10 1D | ?? ?? ?? ?? 48 85 C0 74 38", 1);
		aobBlocks[RESOLUTION_STRUCT_ADDRESS_INTERCEPT_KEY] = new AOBBlock(RESOLUTION_STRUCT_ADDRESS_INTERCEPT_KEY, "8B 81 84 00 00 00 89 41 44 8B 81 88 00 00 00 89 41 40", 1);

		map<string, AOBBlock*>::iterator it;
		bool result = true;
		for (it = aobBlocks.begin(); it != aobBlocks.end(); it++)
		{
			result &= it->second->scan(hostImageAddress, hostImageSize);
		}
		
		if (result)
		{
			MessageHandler::logLine("All interception offsets found.");
		}
		else
		{
			MessageHandler::logError("One or more interception offsets weren't found: tools aren't compatible with this game's version.");
		}
	}


	void setCameraStructInterceptorHook(map<string, AOBBlock*>& aobBlocks)
	{
		GameImageHooker::setHook(aobBlocks[ACTIVECAM_ADDRESS_INTERCEPT_KEY], 0x10, &_activeCamAddressInterceptionContinue, &activeCamAddressInterceptor);
	}

	
	void setPostCameraStructHooks(map<string, AOBBlock*>& aobBlocks)
	{
		GameImageHooker::setHook(aobBlocks[ACTIVECAM_CAMERA_WRITE1_INTERCEPT_KEY], 0x1A, &_activeCamWrite1InterceptionContinue, &activeCamWrite1Interceptor);
		GameImageHooker::setHook(aobBlocks[PMSTRUCT_ADDRESS_INTERCEPT_KEY], 0x10, &_pmStructAddressInterceptionContinue, &pmStructAddressInterceptor);
		GameImageHooker::setHook(aobBlocks[RESOLUTION_STRUCT_ADDRESS_INTERCEPT_KEY], 0x12, &_resolutionStructAddressInterceptionContinue, &resolutionStructAddressInterceptor);

		// Grab the factor from static memory.
		LPBYTE factorAddress = Utils::calculateAbsoluteAddress(aobBlocks[COORD_FACTOR_ADDRESS_KEY], 4);
		CameraManipulator::setCoordMultiplierFactor(*reinterpret_cast<float*>(factorAddress));
	}
}
