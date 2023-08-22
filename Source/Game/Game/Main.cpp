#include <iostream>
#include <thread>
#include <functional>
#include "Core/Core.h"
#include "SpaceGame.h"
#include "Player.h"
#include "Enemy.h"
#include "Renderer/Renderer.h"
#include "Renderer/Texture.h"
#include "Renderer/Text.h"
#include "Renderer/ModelManager.h"
#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Framework/Framework.h"
#include "rapidjson/include/rapidjson/document.h"

using namespace std;
using namespace kiko;

void print_arg(int count, ...) {
    va_list args;
    va_start(args, count);
    for (int i = 0; i < count; ++i)
    {
        std::cout << va_arg(args, const char*) << std::endl;
    }
    va_end(args);
}

union Data
{
    int i;
    bool b;
    char c[6];
};


int main(int argc, char* argv[]) {

    Data data;
    data.i = 0;
    cout << data.i << endl;




    //kiko::Factory::Instance().Register<kiko::SpriteRenderComponent>("SpriteComponent");

    INFO_LOG("Initializing the Engine...");
    MemoryTracker::Initialize();

    //seeds random to make it constantly randomizing
    seedRandom((unsigned int)time(nullptr));

    //file location
    setFilePath("assets");
    cout << getFilePath() << endl;

    //JSON - json.txt
    rapidjson::Document document;
    kiko::Json::Load("json.txt", document);

    //creation of window
    g_renderer.Initialize();
    g_renderer.CreateWindow("CSC196", 800, 600);

    //creates input system
    g_inputSystem.Initialize();
    g_audioSystem.Initialize();

    //creates the game itself
    unique_ptr<SpaceGame> game = make_unique<SpaceGame>();
    game->Initialize();


    // create texture
    kiko::res_t<kiko::Texture> texture = GET_RESOURCE(kiko::Texture, "ship.png", kiko::g_renderer);
    //texture->Load("garflied.jpg", g_renderer);

    bool quit = false;
    while (!quit) {

        ///// Updates

        g_time.Tick();
        //updates the audio and input every tick
        g_audioSystem.Update();
        g_inputSystem.Update();

        if (g_inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE)) quit = true;

        game->Update(g_time.GetDeltaTime());

        /////// Drawing

        g_renderer.SetColor(0, 0, 0, 0);
        g_renderer.BeginFrame();

        kiko::g_renderer.DrawTexture(texture.get(), 200.0f, 200.0f, 0.0f);

        game->Draw(g_renderer);

        g_renderer.EndFrame();

    }

    return 0;
};