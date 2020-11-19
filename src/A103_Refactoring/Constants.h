#pragma once

#include <string>

#include <unordered_map>

// Game general information
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

const int FPS = 60;

//typedef std::unordered_map<std::string, SDL_Texture*> MTextures;
//using Mrects = std::unordered_map<std::string, SDL_Rect>;

const std::string T_BG_MENU = "BackgroundMenu";
const std::string T_BG_INGAME = "BackgroundInGame";
const std::string T_CURSOR = "Cursor";
const std::string T_PLAYERS = "Players";
const std::string T_GOLD = "Gold";

//Menu
const std::string T_BTN_PLAY = "BtnPlay";
const std::string T_BTN_PLAY_N = "BtnPlayN";
const std::string T_BTN_PLAY_H = "BtnPlayH";
const std::string T_BTN_SOUND = "BtnSound";
const std::string T_BTN_SOUND_ON_H = "BtnSoundOnH";
const std::string T_BTN_SOUND_ON_N = "BtnSoundOnN";
const std::string T_BTN_SOUND_OFF_H = "BtnSoundffH";
const std::string T_BTN_SOUND_OFF_N = "BtnSoundffN";
const std::string T_BTN_EXIT = "BtnExit";
const std::string T_BTN_EXIT_N = "BtnExitN";
const std::string T_BTN_EXIT_H = "BtnExitH";
//InGame
const std::string T_TXT_TIME = "TxtTime";
const std::string T_TXT_SC_PL1 = "TxtScPl1";
const std::string T_TXT_SC_PL2 = "TxtScPl2";
const std::string T_SC_NUM = "TxtScNum";
const std::string RF_SC_NUM = "FrameScNum";

