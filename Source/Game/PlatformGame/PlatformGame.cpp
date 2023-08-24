#include "Framework/Game.h"
#include "PlatformGame.h"
#include "Framework/Scene.h"
#include "Framework/Emitter.h"
#include "Framework/Resource/ResourceManager.h"
#include "Framework/Components/SpriteRenderComponent.h"
#include <Framework/Components/ModelRenderComponent.h>
#include "Framework/Components/EnginePhysicsComponent.h"
#include <Framework/Components/CircleCollisionComponent.h>

#include "Renderer/Renderer.h"
#include "Renderer/ModelManager.h"
#include "Renderer/ParticleSystem.h"

#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"

using namespace kiko;

bool PlatformGame::Initialize() {


    //audio bank
    g_audioSystem.AddAudio("laser", "laser.wav");
    g_audioSystem.AddAudio("death", "bwomp.wav");
    g_audioSystem.AddAudio("Background Music", "08 Red Sun (Maniac Agenda Mix).mp3");
    g_audioSystem.AddAudio("Low Health Music", "Critical Health.mp3");
    g_audioSystem.AddAudio("gameover", "gameover.mp3");
    kiko::g_audioSystem.Play("Background Music", true);

    //create scene
    m_scene = std::make_unique<Scene>();
    m_scene->Load("scene/spacescene.json");
    m_scene->Initialize();
    //m_scene->SetGame(this);

    //add events
    kiko::EventManager::Instance().Subscribe("AddPoints", this, std::bind(&PlatformGame::OnAddPoints, this, std::placeholders::_1));
    kiko::EventManager::Instance().Subscribe("OnPlayerDead", this, std::bind(&PlatformGame::OnPlayerDead, this, std::placeholders::_1));

    return true;

}

void PlatformGame::Shutdown() {
    //empty
}

void PlatformGame::Update(float dt) {

    switch (m_state) {

    case PlatformGame::Title:

        if (g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE))
        {
            m_state = eState::StateGame;
            //m_scene->GetActorByName<kiko::Actor>("Background")->active;
        }
        break;

    case PlatformGame::StateGame:

        m_score = 0;
        m_lives = 3;
        m_state = eState::StartLevel;

        break;

    case PlatformGame::StartLevel:
        //create ship
    {
        //std::unique_ptr<Player> player = std::make_unique<Player>(
        //    100.0f,
        //    10.0f,
        //    DegToRad(270.0f),
        //    kiko::Transform{ {400, 300}, 0, 3 },
        //    "Player"
        //);
        //player->m_game = this;
        // create components

        auto renderComponent = CREATE_CLASS(SpriteRenderComponent);
        renderComponent->m_texture = GET_RESOURCE(kiko::Texture, "ship.png", kiko::g_renderer);
        //player->AddComponent(std::move(renderComponent));

        //physics
        auto physicsComponent = CREATE_CLASS(EnginePhysicsComponent);
        physicsComponent->m_damping = 0.9f;
        //player->AddComponent(std::move(physicsComponent));

        auto collisionComponent = CREATE_CLASS(CircleCollisionComponent);
        collisionComponent->m_radius = 30.0f;
        //player->AddComponent(std::move(collisionComponent));


        //player->Initialize();
        //m_scene->Add(std::move(player));
    }

    m_state = eState::Game;


    break;

    case PlatformGame::Game:


        m_spawnTimer += dt;
        if (m_spawnTimer >= m_spawnTime) {

            m_spawnTimer = 0;
            //create enemy
            /*m_scene->Add(std::make_unique <Enemy>(
                20.0f,
                randomf(10.0f, 20.0f),
                DegToRad(270.0f),
                Transform{
                    {random(g_renderer.GetWidth()), random(g_renderer.GetHeight()) }, randomf(kiko::TwoPi), 2
                },
                randomf(1.0f, 2.0f),
                "Enemy"
            ));*/

        }


        break;

    case PlatformGame::PlayerDead:
        if (m_lives == 3) {
            m_state = eState::StartLevel;
        }
        else if (m_lives == 2) {
            g_audioSystem.Play("Low Health Music", false);
            m_state = eState::StartLevel;
        }
        else if (m_lives == 1) {

            m_state = eState::GameOver;
        }
        m_lives--;
        break;

    case PlatformGame::GameOver:
        if (m_state = eState::GameOver) {
            g_audioSystem.Play("gameover", false);
            break;
        }
        break;

    default:
        break;

    }

    m_scoreText->Create(g_renderer, "Score " + std::to_string(m_score), { 28, 163, 39, 1 });
    m_livesText->Create(g_renderer, "Lives " + std::to_string(m_lives), { 207, 34, 25, 1 });

    m_scene->Update(dt);
    kiko::g_particleSystem.Update(dt);

}

void PlatformGame::Draw(kiko::Renderer& renderer) {

    if (m_state == eState::Title)
    {
        m_titleText->Draw(g_renderer, 350, 300);
    }

    m_scene->Draw(renderer);
    kiko::g_particleSystem.Draw(renderer);
    m_scoreText->Draw(g_renderer, 40, 20);
    m_livesText->Draw(g_renderer, 700, 20);
}


void PlatformGame::OnAddPoints(const kiko::Event& event)
{
    m_score += std::get<int>(event.data);
}

void PlatformGame::OnPlayerDead(const kiko::Event& event)
{
    m_lives--;
    m_state = eState::PlayerDead;
}
