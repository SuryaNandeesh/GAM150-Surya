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
    //kiko::g_audioSystem.AddAudio("Background Music", "insertmusic.wav");

    //create scene
    m_scene = std::make_unique<Scene>();
    m_scene->Load("Scenes/platformscene.json");
    m_scene->Load("Scenes/tilemap.json");
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
    {
        auto actor = INSTANTIATE(Actor, "Crate");
        actor->transform.position = vec2{ random(g_renderer.GetWidth(), 100), 0};
        actor->Initialize();
        m_scene->Add(std::move(actor));
    }
        break;

    case PlatformGame::StateGame:

        m_score = 0;
        m_lives = 3;
        m_state = eState::StartLevel;

        break;

    case PlatformGame::StartLevel:
        //create player
    {

        auto renderComponent = CREATE_CLASS(SpriteRenderComponent);
        renderComponent->m_texture = GET_RESOURCE(kiko::Texture, "player_idle.png", kiko::g_renderer);

        //physics
        auto physicsComponent = CREATE_CLASS(EnginePhysicsComponent);
        physicsComponent->m_damping = 0.9f;

        auto collisionComponent = CREATE_CLASS(CircleCollisionComponent);
        collisionComponent->m_radius = 30.0f;

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
            m_state = eState::StartLevel;
        }
        else if (m_lives == 1) {

            m_state = eState::GameOver;
        }
        m_lives--;
        break;

    case PlatformGame::GameOver:
        if (m_state = eState::GameOver) {
            break;
        }
        break;

    default:
        break;

    }

    m_scene->Update(dt);
    kiko::g_particleSystem.Update(dt);

}

void PlatformGame::Draw(kiko::Renderer& renderer) {
    m_scene->Draw(renderer);
    kiko::g_particleSystem.Draw(renderer);
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
