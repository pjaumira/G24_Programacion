
#include "Game.h"

Game::Game() {

    SDL_Window* _window = nullptr;
    SDL_Renderer* _renderer = nullptr;
    _input = InputData();
    //_gameState = GameState::MENU;
    timeDown = 70.0f;

    InitSDL();
    _input.SetScreenSize(Vec2(SCREEN_WIDTH, SCREEN_HEIGHT));
}

Game::~Game() {
        
    SDL_FreeSurface(surfTimer);
    TTF_CloseFont(font_timmer);
    DestroyAllTextures();
    CloseSDL();
}

// Handle Inputs
void Game::UpdateInput() {

    _input.SetFalseKeyDown();

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            _input.SetKeyValue(InputKeys::ESC, true);       
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE) _input.SetKeyValue(InputKeys::ESC, true);

            if (event.key.keysym.sym == SDLK_w) _input.SetKeyValue(InputKeys::W, true);
            if (event.key.keysym.sym == SDLK_s) _input.SetKeyValue(InputKeys::S, true);
            if (event.key.keysym.sym == SDLK_d) _input.SetKeyValue(InputKeys::D, true);
            if (event.key.keysym.sym == SDLK_a) _input.SetKeyValue(InputKeys::A, true);

            if (event.key.keysym.sym == SDLK_UP) _input.SetKeyValue(InputKeys::UP, true);
            if (event.key.keysym.sym == SDLK_DOWN) _input.SetKeyValue(InputKeys::DOWN, true);
            if (event.key.keysym.sym == SDLK_RIGHT) _input.SetKeyValue(InputKeys::RIGHT, true);
            if (event.key.keysym.sym == SDLK_LEFT) _input.SetKeyValue(InputKeys::LEFT, true);

            break;
        case SDL_KEYUP:
            if (event.key.keysym.sym == SDLK_ESCAPE) _input.SetKeyValue(InputKeys::ESC, false);

            if (event.key.keysym.sym == SDLK_w) _input.SetKeyValue(InputKeys::W, false);
            if (event.key.keysym.sym == SDLK_s) _input.SetKeyValue(InputKeys::S, false);
            if (event.key.keysym.sym == SDLK_d) _input.SetKeyValue(InputKeys::D, false);
            if (event.key.keysym.sym == SDLK_a) _input.SetKeyValue(InputKeys::A, false);

            if (event.key.keysym.sym == SDLK_UP) _input.SetKeyValue(InputKeys::UP, false);
            if (event.key.keysym.sym == SDLK_DOWN) _input.SetKeyValue(InputKeys::DOWN, false);
            if (event.key.keysym.sym == SDLK_RIGHT)_input.SetKeyValue(InputKeys::RIGHT, false);
            if (event.key.keysym.sym == SDLK_LEFT) _input.SetKeyValue(InputKeys::LEFT, false);
            break;
        case SDL_MOUSEMOTION:
            _input.SetMouseCoords(event.motion.x, event.motion.y);
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT) _input.SetKeyValue(InputKeys::MOUSE_LEFT, true);
            break;
        case SDL_MOUSEBUTTONUP:
            if (event.button.button == SDL_BUTTON_LEFT) _input.SetKeyValue(InputKeys::MOUSE_LEFT, false);
            break;
        default:;
        }
    }
}

void Game::InitSDL() {

    // --- INIT SDL ---
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        throw "No es pot inicialitzar SDL subsystems";

    // --- WINDOW ---       
    //SDL_Window* m_window { SDL_CreateWindow("SDL...", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN) };
    _window = SDL_CreateWindow("SDL...", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (_window == nullptr)
        throw "No es pot inicialitzar SDL_Window";

    // --- RENDERER ---
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (_renderer == nullptr)
        throw "No es pot inicialitzar SDL_Renderer";

    //Initialize renderer color
    SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);

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

void Game::InitMenu() {

}

void Game::CloseSDL() {

    TTF_Quit();
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    _renderer = nullptr;
    _window = nullptr;
    SDL_Quit();

}

void AddPlayer(int texWidht, int texHeight, Player::numPlayer pNum) {
    Player* p = new Player();
    p->setPlayerValues(texWidht, texHeight, 12, 8, pNum);
    
  //  _players.push_back(std::move(p));
};

void AddGoldBags() {
  /*  Vec2 rPos = Vec2::rVec2(150, SCREEN_WIDTH < SCREEN_HEIGHT ? SCREEN_WIDTH - 150 : SCREEN_HEIGHT - 150); // Necesitamos crear el método de este vector "rVec2" 
    GoldBag* g = new Goldbag({ rPos.x, rPos.y, 40, 40 });
    _goldBags.push_back(std::move(g));*/
}

void Game::Run() {

    // Carregar textures Backgrounds
    SDL_Texture* texMenuBg{ IMG_LoadTexture(_renderer, "../../res/img/bg.jpg") };
    if (texMenuBg == nullptr) throw "Error: bgTexture init";
    SDL_Rect rectMenuBg{ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

    SDL_Texture* texGameBg{ IMG_LoadTexture(_renderer, "../../res/img/bgCastle.jpg") };
    if (texGameBg == nullptr) throw "Error: bgTexture init";
    SDL_Rect rectGameBg{ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

    //Cursor
    SDL_Texture* cursorTexture{ IMG_LoadTexture(_renderer, "../../res/img/kintoun.png") };
    if (cursorTexture == nullptr) throw "No s'han pogut crear les textures";
    SDL_Rect cursorRect{ 0, 0, 100, 50 };

    // Spritesheet Personatje
    int texWidth, texHeight;
    SDL_Texture* texPlayers = IMG_LoadTexture(_renderer, "../../res/img/spCastle.png");
    SDL_QueryTexture(texPlayers, NULL, NULL, &texWidth, &texHeight);

    AddPlayer(texWidth, texHeight, Player::numPlayer::P1);
    AddPlayer(texWidth, texHeight, Player::numPlayer::P2);

    // Sprite Oro
    SDL_Texture* texGoldBag = IMG_LoadTexture(_renderer, "../../res/img/gold.png");

    for (int i = 0; i < 5; i++) AddGoldBags();

    // Text
    TTF_Font* font = TTF_OpenFont("../../res/ttf/saiyan.ttf", 80);
    if (!font) throw "No s'ha pogut crear la font.";

    // Butons Menu

    // Counter

    //Score
    TTF_Font* fontScore = TTF_OpenFont("../../res/ttf/KidG.ttf", 20);

    SDL_Surface* surfScore{ TTF_RenderText_Blended(fontScore, "P1 : ", SDL_Color {0,50, 220,255}) };
    SDL_Texture* texP1Score = SDL_CreateTextureFromSurface(_renderer, surfScore);
    SDL_Rect rectTextScore{ 10,10, surfScore->w, surfScore->h };

    surfScore = TTF_RenderText_Blended(fontScore, "P2 : ", SDL_Color{ 0,50,220,255 });
    SDL_Texture* texP2Score = SDL_CreateTextureFromSurface(_renderer, surfScore);

    // Game Loop
    while (_gameState != GameState::EXIT) {

        // Handle Events
        UpdateInput();

        // Update
        if (_input.IsPressed(InputKeys::ESC)) _gameState = GameState::EXIT;

        // Cursor
        cursorRect.x += (((_input.GetMouseCoord().x - (cursorRect.w / 2)) - cursorRect.x) / 10);
        cursorRect.y += (((_input.GetMouseCoord().y - (cursorRect.h / 2)) - cursorRect.y) / 10);

        // Buton logic

        // Play Button
        if (Collisions::ExistCollision(/*input.GetMouseCoords()*/SDL2My(cursorRect), SDL2My(Rect_PlayBtn))) {
            texPlay = texPlay_Hover;
            if (_input.JustPressed(InputKeys::MOUSE_LEFT)) { /*Play Logic*/ }
        }
        else texPlay = texPlay_Normal;

        //Sound Logic
        if (Collisions::ExistCollision(_input.GetMouseCoord(), SDL2My(Rect_SoundBtn))) {
            if (_input.JustPressed(InputKeys::MOUSE_LEFT)) {
                if (!Mix_PausedMusic()) Mix_PauseMusic();
                else Mix_PlayMusic(soundtrack, -1);
            }
            texSound = Mix_PausedMusic() ? texSoundOff_Hover : TexSoundOn_Hover;
        }
        else texSound = !Mix_PausedMusic() ? TexSoundOn_Normal : TexSoundOff_Normal;

        //Exit Logic
        if (Collisions::ExistCollision(_input.GetMouseCoord(), SDL2My(Rect_ExitBtn))) {
            texExit = texExit_Hover;
            if (input.JustPressed(InputKeys::MOUSE_LEFT)) { isRunning = 0; }
        }
        else texExit = texExit_Normal;

        // Update Players
        for (Player* p : _players) {
            p->Update(&_input, _goldBags);
        }

        // Update Timer
        if (_gameState == GameState::GAME) timeDown -= *_input.GetDeltaTime();
        if (timeDown <= 0.f) _gameState = GameState::EXIT;
        else {
            std::string s = textTime + F2StrFormat(trunc(timeDown / 60), 0);
            s += ":" + F2StrFormat(static_cast <int> (timeDown) % 60, 0);
            surfTimer = TTF_RenderText_Blended(font_timmer, s.c_str(), SDL_Color{ 0,50, 220, 255 });
            texTiimer = SDL_CreateTextureFromSurface(_renderer, surfTimer);
            Rect_Timmer = { SCREEN_WIDTH - 150, 10, surfTimer->w, surfTimer->h };
        }

        // DRAW
        SDL_RenderClear(_renderer);

        SDL_RenderCopy(_renderer, texGameBg, nullptr, &rectGameBg);

        SDL_RenderCopy(m_renderer, texTimer, nullptr, &Rect_Timer);

        SDL_RenderCopy(m_renderer, texP1Score, nullptr, &rectTextScore);
        SDL_RenderCopy(m_renderer, texP1Score, nullptr, My2SDL(&MyRect(rectTextScore.x, rectTextScore.y + (rectTextScore.h), rectTextScore));

        for (int i = 0; i < _players.size(); i++) {
            Player* p = _players.at(i);
            // falta acabar
            SDL_RenderCopy(m_renderer, texNum,
                &My2SDL(&MyRect(trunc(*(p->getScore()) * 0.1) * Rect_ScoreFrame.w, 0, Rect_ScoreFrame.w, Rect_ScoreFrame.h)),
                &My2SDL(&MyRect(Rect_ScoreNum.x, Rect_ScoreNum.y + (Rect_ScoreNum.h * i), Rect_ScoreNum.w, Rect_ScoreNum.h)));

            SDL_RenderCopy(m_renderer, texNum,
                &My2SDL(&MyRect((*(p->getScore()) % 10) * Rect_ScoreFrame.w, 0, Rect_ScoreFrame.w, Rect_ScoreFrame.h)),
                &My2SDL(&MyRect(Rect_ScoreNum.x + (Rect_ScoreNum.w * 1), Rect_ScoreNum.y + (Rect_ScoreNum.h * i) + Rect_ScoreNum.w, Rect_ScoreNum.h));

            std::cout << "P1" << std::to_string(i + 1).c_str() << ": " << *p->getScore() << std::endl;
        }

        for (const GoldBags* g : _goldBags)
            SDL_RenderCopy(m_renderer, texGoldBag, nullptr, &My2SDL(g->getPosition()));
    }

    for (const Player* p : _players)
        SDL_RenderCopy(_renderer, texPlayers, &My2SDL(p->getFrame()), &My2SDL(p->getPosition()));

    SDL_RenderPresent(_renderer);

    // Frame Control
    _input.UpdateDeltaTime();

    //DESTROY
    SDL_DestroyTexture(texP1Score);
    SDL_DestroyTexture(texP2Score);
    SDL_DestroyTexture(texPlayers);
    SDL_DestroyTexture(texMenuBg);
    SDL_DestroyTexture(cursorTexture);
    SDL_DestroyTexture(texPlay);
    SDL_DestroyTexture(texPlay_Hover);
    SDL_DestroyTexture(texPlay_Normal);
    SDL_DestroyTexture(texSound);
    SDL_DestroyTexture(texSoundOn_Normal);
    SDL_DestroyTexture(texSoundOn_Hover);
    SDL_DestroyTexture(texSoundff_Normal);
    SDL_DestroyTexture(texSoundff_Hover);
    SDL_DestroyTexture(texExit);
    SDL_DestroyTexture(texExit_Hover);
    SDL_DestroyTexture(texExit_Normal);
    SDL_DestroyTexture(texP1Score);

    SDL_FreeSurface(surfTimer);
    TTF_CloseFont(font_timmer);
}