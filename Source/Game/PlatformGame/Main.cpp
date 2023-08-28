#include <iostream>
#include <thread>
#include <functional>
#include "Core/Core.h"
#include "PlatformGame.h"
#include "Renderer/Renderer.h"
#include "Renderer/Texture.h"
#include "Renderer/Text.h"
#include "Renderer/ModelManager.h"
#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Framework/Framework.h"
#include "rapidjson/include/rapidjson/document.h"
#include "Physics/PhysicsSystem.h"

using namespace std;
using namespace kiko;

int main(int argc, char* argv[]) {

    INFO_LOG("Initializing the Engine...");
    MemoryTracker::Initialize();

    PhysicsSystem::Instance().Initialize();

    //seeds random to make it constantly randomizing
    seedRandom((unsigned int)time(nullptr));

    //file location
    setFilePath("assets/platformer");
    cout << getFilePath() << endl;

    //JSON - json.txt
    rapidjson::Document document;
    kiko::Json::Load("json.txt", document);

    //creation of window
    g_renderer.Initialize();
    g_renderer.CreateWindow("GAM150", 800, 600);

    //creates input system
    g_inputSystem.Initialize();
    g_audioSystem.Initialize();

    //creates the game itself
    unique_ptr<PlatformGame> game = make_unique<PlatformGame>();
    game->Initialize();

    bool quit = false;
    while (!quit) {

        ///// Updates

        g_time.Tick();
        //updates the audio and input every tick
        g_audioSystem.Update();
        g_inputSystem.Update();

        //esc exits the game
        if (g_inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE)) quit = true;

        //updates the game every tick
        game->Update(g_time.GetDeltaTime());

        /////// Drawing
        g_renderer.SetColor(0, 0, 0, 0);
        g_renderer.BeginFrame();

        game->Draw(g_renderer);

        g_renderer.EndFrame();

    }

    return 0;
};