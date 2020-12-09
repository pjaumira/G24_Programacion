#include "SceneMenu.h"
#include "Renderer.h"

Menu::Menu() {

	Inputs::Check()->mousePressed = false;

	//Load Fonts
	Renderer::Instance()->LoadFont ({ "Saiyan_Font", "../../res/ttf/saiyan.ttf", 80 });
	Renderer::Instance()->LoadFont ({ "Arial_Font", "../../res/ttf/arial.ttf", 20 });

	// Background
	Renderer::Instance()->LoadTexture ( "MenuBachground", "../../res/img/bg.jpg");

	//Cursor
	Renderer::Instance()->LoadTexture("mouseCursor", "../../res/img/kintoun.png");

	// Menu Buttons
		//Play
	Renderer::Instance()->LoadTextureText("Saiyan_Font", { "TEXT_BUTTON_PLAY", "PLAY",{ 255,255,255,229 } });
	Renderer::Instance()->LoadTextureText("Saiyan_Font", { "TEXT_BUTTON_PLAY_HOVER", "PLAY",{ 255,255,255,229 } });
	Renderer::Instance()->LoadTextureText("Saiyan_Font", { "TEXT_BUTTON_PLAY_NO_HOVER", "PLAY",{ 255,255,255,229 } });

		//Sound
	Renderer::Instance()->LoadTextureText("Saiyan_Font", { "SOUND_ON", "SOUND ON",{255,255,255,229 } });
	Renderer::Instance()->LoadTextureText("Saiyan_Font", { "SOUND_ON_HOVER", "SOUND ON",{255,255,255,229 } });
	Renderer::Instance()->LoadTextureText("Saiyan_Font", { "SOUND_ON_NO_HOVER", "SOUND ON",{255,255,255,229 } });

	Renderer::Instance()->LoadTextureText("Saiyan_Font", { "SOUND_OFF", "SOUND OFF",{255,255,255,229 } });
	Renderer::Instance()->LoadTextureText("Saiyan_Font", { "SOUND_OFF_HOVER", "SOUND OFF",{255,255,255,229 } });
	Renderer::Instance()->LoadTextureText("Saiyan_Font", { "SOUND_OFF_NO_HOVER", "SOUND OFF",{255,255,255,229 } });

		//Exit
	Renderer::Instance()->LoadTextureText("Saiyan_Font", { "TEXT_BUTTON_EXIT", "EXIT",{ 255,255,255,229 } });
	Renderer::Instance()->LoadTextureText("Saiyan_Font", { "TEXT_BUTTON_EXIT_HOVER", "EXIT",{ 255,255,255,229 } });
	Renderer::Instance()->LoadTextureText("Saiyan_Font", { "TEXT_BUTTON_EXIT_NO_HOVER", "EXIT",{ 255,255,255,229 } });

	// Music
	Mix_Music* soundtrack{ Mix_LoadMUS("../../res/au/mainTheme.mp3") };
	Mix_PlayMusic(soundtrack, -1);

	controlMusic = true;
}

void Menu::Update() {

	// Cursor


	//ButtonPlay
		//When you press the button play
	//if (Collisions::ExistCollision(mouse,)){
	if ((Renderer::Instance()->event.motion.x > 200 && Renderer::Instance()->event.motion.x < 485 && Renderer::Instance()->event.motion.y > 125 && Renderer::Instance()->event.motion.y < 200) && Inputs::Check()->mousePressed) {
		Scene::StateScene = SceneState::GOTO;
		Scene::gameScene = GameState::GAME;
		std::cout << "Play" << std::endl;
		Inputs::Check()->mousePressed = false;
	}
	//SoundToggle
	if (Renderer::Instance()->event.motion.x > 200 && Renderer::Instance()->event.motion.x < 625 && Renderer::Instance()->event.motion.y > 325 && Renderer::Instance()->event.motion.y < 400 && Inputs::Check()->mousePressed) {
		if (controlMusic) { controlMusic = false; }
		else { controlMusic = true; }
		SoundToggle();
		std::cout << "Sound" << std::endl;
		Inputs::Check()->mousePressed = false;
	}

	//ButtonExit
	if (Renderer::Instance()->event.motion.x > 200 && Renderer::Instance()->event.motion.x < 440 && Renderer::Instance()->event.motion.y > 425 && Renderer::Instance()->event.motion.y < 500 && Inputs::Check()->mousePressed) {
		Scene::StateScene = SceneState::EXIT;
		std::cout << "Exit" << std::endl;
		Inputs::Check()->mousePressed = false;
	}
}

void Menu::SoundToggle() {
	if (controlMusic) { Mix_ResumeMusic();}
	else { Mix_PauseMusic();}
}

void Menu::Draw() {
	// PlayButton
	Renderer::Instance()->PushImage("TEXT_BUTTON_PLAY", { 200,125,(Renderer::Instance()->GetTextureSize("TEXT_BUTTON_PLAY")).x, (Renderer::Instance()->GetTextureSize("TEXT_BUTTON_PLAY")).y });

	// Music Toggle
	if (controlMusic){
		Renderer::Instance()->PushImage("SOUND_ON", { 200, 325, (Renderer::Instance()->GetTextureSize("SOUND_ON")).x, (Renderer::Instance()->GetTextureSize("SOUND_ON")).y });
	}
	else {
		Renderer::Instance()->PushImage("SOUND_OFF", { 200, 325, (Renderer::Instance()->GetTextureSize("SOUND_OFF")).x, (Renderer::Instance()->GetTextureSize("SOUND_OFF")).y });
	}

	// Exit Button
	Renderer::Instance()->PushImage("TEXT_BUTTON_EXIT", { 200,425,(Renderer::Instance()->GetTextureSize("TEXT_BUTTON_EXIT")).x, (Renderer::Instance()->GetTextureSize("TEXT_BUTTON_EXIT")).y });

	//Clean-up
	Renderer::Instance()->Render();
	Renderer::Instance()->Clear();
}