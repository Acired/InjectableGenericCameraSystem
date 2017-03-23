//////////////////////////	//////////////////////////////////////////////////////////////////////////////
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
#pragma once

namespace IGCS::GameSpecific
{
	// Mandatory constants to define for a game
	#define GAME_NAME									"Lords of the Fallen, latest"
	#define CAMERA_VERSION								"1.0.0"
	#define CAMERA_CREDITS								"Otis_Inf, Petroski. Special thanks to Jim2point0."
	#define GAME_WINDOW_TITLE							"Lords of the Fallen"
	#define INITIAL_PITCH_RADIANS						0.0f	// World has X right, Y up, Z out of the screen.
	#define INITIAL_YAW_RADIANS							0.0f	// around Y axis	(out of the screen)
	#define INITIAL_ROLL_RADIANS						0.0f	// around Z axis	(up)
	#define CONTROLLER_Y_INVERT							false
	#define FASTER_MULTIPLIER							10.0f
	#define SLOWER_MULTIPLIER							0.1f
	#define MOUSE_SPEED_CORRECTION						0.2f	// to correct for the mouse-deltas related to normal rotation.
	#define DEFAULT_MOVEMENT_SPEED						1.2f
	#define DEFAULT_ROTATION_SPEED						0.015f
	#define DEFAULT_FOV_DEGREES							54.54f
	#define DEFAULT_FOV_SPEED							0.1f
	#define DEFAULT_UP_MOVEMENT_MULTIPLIER				0.7f
	#define DEFAULT_GAME_SPEED							1.0f
	#define DEFAULT_MIN_GAME_SPEED						0.0f
	#define DEFAULT_MAX_GAME_SPEED						1.0f
	// End Mandatory constants

	// AOB Keys for interceptor's AOB scanner
	#define CAMERA_WRITE_INTERCEPT1_KEY					"AOB_CAMERA_WRITE_INTERCEPT1"
	#define CAMERA_WRITE_INTERCEPT2_KEY					"AOB_CAMERA_WRITE_INTERCEPT2"



	// Indices in the structures read by interceptors 
	#define CAMERA_STRUCT_OFFSET_IN_IMAGE				0x5D3DDE0
	#define CAMERA_COORDS_IN_CAMERA_STRUCT_OFFSET		0x0
	#define LOOK_DATA_IN_CAMERA_STRUCT_OFFSET			0xC		
	#define GAMESPEED_IN_IMAGE_OFFSET					0xCFC5870
	#define GAMESPEED_BOSS_IN_IMAGE_OFFSET				0x5F47038
	#define GAMESPEED_ENEMIES_IN_IMAGE_OFFSET			0x5D06688
}