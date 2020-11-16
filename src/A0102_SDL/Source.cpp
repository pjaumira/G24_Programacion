//SDL includes
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

//Generic includes
#include <exception>
#include <iostream>
#include <string>
#include <vector>

//Include de extra variables        
#include "Player.h"
#include "Types.h"
#include "Utilities.h"

void InitSDL(SDL_Window*& w, SDL_Renderer*& r) {
    // --- INIT SDL ---
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        throw "No es pot inicialitzar SDL subsystems";

    // --- WINDOW ---       
    //SDL_Window* m_window { SDL_CreateWindow("SDL...", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN) };
    w = SDL_CreateWindow("SDL...", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (w == nullptr)
        throw "No es pot inicialitzar SDL_Window";

    // --- RENDERER ---
    r = SDL_CreateRenderer(w, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (r == nullptr)
        throw "No es pot inicialitzar SDL_Renderer";

    //Initialize renderer color
    SDL_SetRenderDrawColor(r, 255, 255, 255, 255);

    //-->SDL_Image
    const Uint8 imgFlags{ IMG_INIT_PNG | IMG_INIT_JPG };
    if (!(IMG_Init(imgFlags) & imgFlags))
        throw "Error: SDL_image init";

    //-->SDL_TTF
    if (TTF_Init()) throw "No es pot inicialitzar SDL_ttf";
    //-->SDL_Mix
    const Uint8 mixFlags{ MIX_INIT_MP3 | MIX_INIT_OGG };
    if (!(Mix_Init(mixFlags) & mixFlags)) throw "Error: SDL:MixerInit";
}

void CloseSDL(SDL_Window*& w, SDL_Renderer*& r) {
    TTF_Quit();
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    SDL_DestroyRenderer(r);
    SDL_DestroyWindow(w);
    r = nullptr;
    w = nullptr;
    SDL_Quit();
}

int main(int, char* [])
{
    SDL_Window* m_window = nullptr;
    SDL_Renderer* m_renderer = nullptr;

    InitSDL(m_window, m_renderer);

    // --- SPRITES ---
#pragma region Textures
  //Background
    SDL_Texture* texMenuBg{ IMG_LoadTexture(m_renderer, "../../res/img/bg.jpg") };
    if (texMenuBg == nullptr) throw "Error: bgTexture init";
    SDL_Rect rectMenuBg{ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

    SDL_Texture* texGameBg{ IMG_LoadTexture(m_renderer, "../../res/img/bgCastle.jpg") };
    if (texGameBg == nullptr) throw "Error: bgTexture init";
    SDL_Rect rectGameBg{ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

    //Cursor
    SDL_Texture* cursorTexture{ IMG_LoadTexture(m_renderer, "../../res/img/kintoun.png") };
    if (cursorTexture == nullptr) throw "No s'han pogut crear les textures";
    SDL_Rect cursorRect{ 0, 0, 100, 50 };

    //-->Animated Sprite ---
#pragma region Sprites

#pragma region Players
    SDL_Texture* texPlayers = IMG_LoadTexture(m_renderer, "../../res/img/spCastle.png");
    int textPlWidth, textPlHeight;
    SDL_QueryTexture(texPlayers, NULL, NULL, &textPlWidth, &textPlHeight);
    std::vector<Player*> players;

    //Player 1
    Player* p = new Player();
    p->setPlayerValues(textPlWidth, textPlHeight, 12, 8, Player::numPlayer::P1);
    players.push_back(std::move(p));

    // Player 2
    p = new Player();
    p->setPlayerValues(textPlWidth, textPlHeight, 12, 8, Player::numPlayer::P2);
    players.push_back(std::move(p));

#pragma endregion

#pragma endregion

#pragma endregion

    // --- TEXT ---
#pragma region Text

  //Generate font textures 
    TTF_Font* font = TTF_OpenFont("../../res/ttf/saiyan.ttf", 80);
    if (!font) throw "No s'ha pogut crear la font.";

#pragma region Buttons
    //Play
    SDL_Surface* tmpSurf{ TTF_RenderText_Blended(font, "Play", SDL_Color{0,200,0,255}) };
    if (!tmpSurf) throw "No s'ha pogut crear la surface.";
    SDL_Texture* Tex_PlayNormal = SDL_CreateTextureFromSurface(m_renderer, tmpSurf);

    tmpSurf = TTF_RenderText_Blended(font, "Play", SDL_Color{ 200,100,0,255 });
    SDL_Texture* Tex_PlayHover = SDL_CreateTextureFromSurface(m_renderer, tmpSurf);

    SDL_Texture* Tex_Play = Tex_PlayNormal;
    SDL_Rect Rect_PlayBtn{ SCREEN_WIDTH / 2 - tmpSurf->w / 2, 100, tmpSurf->w, tmpSurf->h };

    //Sound On/off
    tmpSurf = TTF_RenderText_Blended(font, "Sound On", SDL_Color{ 0,200,0,255 });
    SDL_Texture* Tex_SoundOnNormal = SDL_CreateTextureFromSurface(m_renderer, tmpSurf);

    tmpSurf = TTF_RenderText_Blended(font, "Sound On", SDL_Color{ 200,100,0,255 });
    SDL_Texture* Tex_SoundOnHover = SDL_CreateTextureFromSurface(m_renderer, tmpSurf);

    tmpSurf = TTF_RenderText_Blended(font, "Sound Off", SDL_Color{ 0,200,0,255 });
    SDL_Texture* Tex_SoundOffNormal = SDL_CreateTextureFromSurface(m_renderer, tmpSurf);

    tmpSurf = TTF_RenderText_Blended(font, "Sound Off", SDL_Color{ 200,100,0,255 });
    SDL_Texture* Tex_SoundOffHover = SDL_CreateTextureFromSurface(m_renderer, tmpSurf);

    SDL_Texture* Tex_Sound = Tex_SoundOnNormal;
    SDL_Rect Rect_SoundBtn{ SCREEN_WIDTH / 2 - tmpSurf->w / 2, 200, tmpSurf->w, tmpSurf->h };

    //Exit
    tmpSurf = TTF_RenderText_Blended(font, "Exit", SDL_Color{ 0,200,0,255 });
    SDL_Texture* Tex_ExitNormal = SDL_CreateTextureFromSurface(m_renderer, tmpSurf);

    tmpSurf = TTF_RenderText_Blended(font, "Exit", SDL_Color{ 200,100,0,255 });
    SDL_Texture* Tex_ExitHover = SDL_CreateTextureFromSurface(m_renderer, tmpSurf);

    SDL_Texture* Tex_Exit = Tex_PlayNormal;
    SDL_Rect Rect_ExitBtn{ SCREEN_WIDTH / 2 - tmpSurf->w / 2, 300, tmpSurf->w, tmpSurf->h };

    //Delete Surfaces and close Fonts
    SDL_FreeSurface(tmpSurf);
    TTF_CloseFont(font);
#pragma endregion

#pragma region TextInGame
    TTF_Font* font_timmer = TTF_OpenFont("../../res/ttf/arial.ttf", 25);
    std::string textTime = "Time: ";
    SDL_Surface* surfTimer{ TTF_RenderText_Blended(font_timmer, textTime.c_str(), SDL_Color{0,50,220,255}) };
    SDL_Texture* Tex_timer = SDL_CreateTextureFromSurface(m_renderer, surfTimer);
    SDL_Rect Rect_Timmer{ SCREEN_WIDTH - 150, 10, surfTimer->w, surfTimer->h };
#pragma endregion

#pragma endregion

    // --- AUDIO ---
#pragma region Audio
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
        throw "No s'ha pogut inicialitzar SDL_Mixer";
    }
    Mix_Music* soundtrack{ Mix_LoadMUS("../../res/au/mainTheme.mp3") };
    if (!soundtrack) throw "No s'ha pogut carregar l'audio";

    Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
    //Mix_PlayMusic(soundtrack, -1);

#pragma endregion

  // --- GAME VARIABLES ---
    InputData input;
    input.SetScreenSize(Vec2(SCREEN_WIDTH, SCREEN_HEIGHT));
    SDL_Event event;
    bool isRunning = true;

    float timeDown = 10.f;

    // --- GAME LOOP ---
    while (isRunning)
    {
        //---HANDLE EVENTS---
        input.SetFalseKeyDown();
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                isRunning = false;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) input.SetKeyValue(InputKeys::ESC, true);

                if (event.key.keysym.sym == SDLK_w) input.SetKeyValue(InputKeys::W, true);
                if (event.key.keysym.sym == SDLK_s) input.SetKeyValue(InputKeys::S, true);
                if (event.key.keysym.sym == SDLK_d) input.SetKeyValue(InputKeys::D, true);
                if (event.key.keysym.sym == SDLK_a) input.SetKeyValue(InputKeys::A, true);

                if (event.key.keysym.sym == SDLK_UP)    input.SetKeyValue(InputKeys::UP, true);
                if (event.key.keysym.sym == SDLK_DOWN)  input.SetKeyValue(InputKeys::DOWN, true);
                if (event.key.keysym.sym == SDLK_RIGHT) input.SetKeyValue(InputKeys::RIGHT, true);
                if (event.key.keysym.sym == SDLK_LEFT)  input.SetKeyValue(InputKeys::LEFT, true);

                break;
            case SDL_KEYUP:
                if (event.key.keysym.sym == SDLK_ESCAPE) input.SetKeyValue(InputKeys::ESC, false);

                if (event.key.keysym.sym == SDLK_w) input.SetKeyValue(InputKeys::W, false);
                if (event.key.keysym.sym == SDLK_s) input.SetKeyValue(InputKeys::S, false);
                if (event.key.keysym.sym == SDLK_d) input.SetKeyValue(InputKeys::D, false);
                if (event.key.keysym.sym == SDLK_a) input.SetKeyValue(InputKeys::A, false);

                if (event.key.keysym.sym == SDLK_UP)    input.SetKeyValue(InputKeys::UP, false);
                if (event.key.keysym.sym == SDLK_DOWN)  input.SetKeyValue(InputKeys::DOWN, false);
                if (event.key.keysym.sym == SDLK_RIGHT) input.SetKeyValue(InputKeys::RIGHT, false);
                if (event.key.keysym.sym == SDLK_LEFT)  input.SetKeyValue(InputKeys::LEFT, false);
                break;
            case SDL_MOUSEMOTION:
                input.SetMouseCoords(event.motion.x, event.motion.y);
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) input.SetKeyValue(InputKeys::MOUSE_LEFT, true);
                break;
            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT) input.SetKeyValue(InputKeys::MOUSE_LEFT, false);
                break;
            default:;
            }
        }

        //---UPDATE---
        if (input.IsPressed(InputKeys::ESC)) isRunning = false;

        //Cursor
        cursorRect.x += (((input.GetMouseCoord().x - (cursorRect.w / 2)) - cursorRect.x) / 10);
        cursorRect.y += (((input.GetMouseCoord().y - (cursorRect.h / 2)) - cursorRect.y) / 10);

#pragma region BUTTONS
        //Play Logic
        if (Collisions::ExistCollision(/*input.GetMouseCoords()*/SDL2My(cursorRect), SDL2My(Rect_PlayBtn))) {
            Tex_Play = Tex_PlayHover;
            if (input.JustPressed(InputKeys::MOUSE_LEFT)) { /*Play Logic*/ }
        }
        else Tex_Play = Tex_PlayNormal;

        //Sound Logic
        if (Collisions::ExistCollision(input.GetMouseCoord(), SDL2My(Rect_SoundBtn))) {
            if (input.JustPressed(InputKeys::MOUSE_LEFT)) {
                if (!Mix_PausedMusic()) Mix_PauseMusic();
                else Mix_PlayMusic(soundtrack, -1);
            }
            Tex_Sound = Mix_PausedMusic() ? Tex_SoundOffHover : Tex_SoundOnHover;
        }
        else Tex_Sound = !Mix_PausedMusic() ? Tex_SoundOnNormal : Tex_SoundOffNormal;

        //Exit Logic
        if (Collisions::ExistCollision(input.GetMouseCoord(), SDL2My(Rect_ExitBtn))) {
            Tex_Exit = Tex_ExitHover;
            if (input.JustPressed(InputKeys::MOUSE_LEFT)) { isRunning = 0; }
        }
        else Tex_Exit = Tex_ExitNormal;

#pragma endregion

        //Update players
        for (Player* p : players)
            p->Update(input);

        //Update Timer
        std::string s = textTime + F2StrFormat(timeDown, 2);
        surfTimer = TTF_RenderText_Blended(font_timmer, s.c_str(), SDL_Color{ 0,50,220,255 });
        Tex_timer = SDL_CreateTextureFromSurface(m_renderer, surfTimer);
        Rect_Timmer = { SCREEN_WIDTH - 150, 10, surfTimer->w, surfTimer->h };

        //---DRAW---
        SDL_RenderClear(m_renderer);
        //Background
        //SDL_RenderCopy(m_renderer, texMenuBg, nullptr, &rectMenuBg);
        SDL_RenderCopy(m_renderer, texGameBg, nullptr, &rectGameBg);
        // Buttons
        /*
        SDL_RenderCopy(m_renderer, Tex_Play, nullptr, &Rect_PlayBtn);
        SDL_RenderCopy(m_renderer, Tex_Sound, nullptr, &Rect_SoundBtn);
        SDL_RenderCopy(m_renderer, Tex_Exit, nullptr, &Rect_ExitBtn);
        */

        SDL_RenderCopy(m_renderer, Tex_timer, nullptr, &Rect_Timmer);
        //Cursor
        //SDL_RenderCopy(m_renderer, cursorTexture, nullptr, &cursorRect);

        //Player
        //SDL_RenderCopy(m_renderer, texGirl, &rectGirl, &girlPos);
        for (Player* p : players)
            SDL_RenderCopy(m_renderer, texPlayers, &My2SDL(p->getFrame()), &My2SDL(p->getPosition()));

        SDL_RenderPresent(m_renderer);

        //---FRAME CONTROL---
        input.UpdateDeltaTime()     ;
        timeDown -= *input.GetDeltaTime();
        std::cout << timeDown << std::endl;

    }

    // --- DESTROY ---
    SDL_DestroyTexture(texPlayers);
    SDL_DestroyTexture(texMenuBg);
    SDL_DestroyTexture(cursorTexture);
    SDL_DestroyTexture(Tex_Play);
    SDL_DestroyTexture(Tex_PlayNormal);
    SDL_DestroyTexture(Tex_PlayHover);
    SDL_DestroyTexture(Tex_Sound);
    SDL_DestroyTexture(Tex_SoundOnNormal);
    SDL_DestroyTexture(Tex_SoundOnHover);
    SDL_DestroyTexture(Tex_SoundOffNormal);
    SDL_DestroyTexture(Tex_SoundOffHover);
    SDL_DestroyTexture(Tex_Exit);
    SDL_DestroyTexture(Tex_ExitNormal);
    SDL_DestroyTexture(Tex_ExitHover);

    SDL_FreeSurface(surfTimer);
    TTF_CloseFont(font_timmer);

    // --- QUIT ---
    CloseSDL(m_window, m_renderer);

    return 0;
}