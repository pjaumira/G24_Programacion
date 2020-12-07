#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string.h>
#include <SDL_mixer.h> 	
#include <unordered_map>
#include "Types.h"
#include "Constants.h"


//SDL
class Renderer {

private:
	SDL_Renderer* m_renderer = nullptr;
	SDL_Window* m_window = nullptr;
	std::unordered_map<std::string, SDL_Texture*> m_textureData;
	std::unordered_map<std::string, TTF_Font*> m_fontData;
	std::unordered_map<std::string, SDL_Rect*> m_rects;
	static Renderer *renderer;

public:

	Renderer();
	~Renderer();

	static Renderer* Instance() {
		if (renderer == nullptr) { renderer = new Renderer; }
		return renderer;
	};

	void Clear();
	void Render();
	void LoadFont(const Font& font);
	void LoadTexture(const std::string& id, const std::string& path);
	void LoadRect(const std::string& idRect, const MyRect& rect);

	//sobrecargar ... para que devuelva
	Vec2 LoadTextureText(const std::string& fontId, Text text);
	Vec2 GetTextureSize(const std::string& id);

	void PushImage(const std::string& id, const std::string& idRect);
	void PushSprite(const std::string& id, const std::string& idRectSprite, const std::string& idRectPos);
	void PushRotatedSprite(const std::string& id, const std::string& idRectSprite, const std::string& idRectPos, float angle);
	void SetRenderDrawColor(int r, int g, int b);
	void SetRenderDrawColor(const Color& c);

	// Eventos
	SDL_Event event;

	// Player Sprite
	SDL_Rect spritesheetPlayers;
	SDL_Rect player1Rect;
	SDL_Rect player2Rect;

	// GoldBag Sprite
	SDL_Rect goldBagRect;

	// Hud
	SDL_Rect timerRect;
	SDL_Rect hudP1Rect;
	SDL_Rect hudP2_Rect;
	SDL_Rect scoreP1Rect;
	SDL_Rect scoreP2Rect;

};