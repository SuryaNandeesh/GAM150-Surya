#include "SpaceGame.h"
#include "Framework/Game.h"

#include "Player.h"
#include "Enemy.h"

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

bool SpaceGame::Initialize() {

    //make font
    //m_font = std::make_shared<Font>("ARCADECLASSIC.ttf", 24);
    m_font = GET_RESOURCE(Font, "ARCADECLASSIC.ttf", 24);

	m_scoreText = std::make_unique<Text>(GET_RESOURCE(Font, "ARCADECLASSIC.ttf", 24));
	//m_scoreText = std::make_unique<kiko::Text>(m_font);
    m_scoreText->Create(g_renderer, "SCORE 0000", Color{ 28, 163, 39, 1 });

    m_livesText = std::make_unique<Text>(GET_RESOURCE(Font, "ARCADECLASSIC.ttf", 24));
    //m_livesText = std::make_unique<kiko::Text>(m_font);
    m_livesText->Create(g_renderer, "LIVES 0", Color{ 207, 34, 25, 1 });

    m_titleText = std::make_unique<Text>(GET_RESOURCE(Font, "ARCADECLASSIC.ttf", 24));
    //m_titleText = std::make_unique<kiko::Text>(m_font);
    m_titleText->Create(g_renderer, "ASTEROID", Color{ 1, 1, 1, 1 });

    //audio bank
	g_audioSystem.AddAudio("laser", "laser.wav");
	g_audioSystem.AddAudio("death", "bwomp.wav");
	g_audioSystem.AddAudio("Background Music", "08 Red Sun (Maniac Agenda Mix).mp3");
	g_audioSystem.AddAudio("Low Health Music", "Critical Health.mp3");
	g_audioSystem.AddAudio("gameover", "gameover.mp3");
    g_audioSystem.Play("Background Music", true);
    
    //create scene
    m_scene = std::make_unique<Scene>();
    m_scene->Load("scenes/spacescene.json");
    m_scene->Initialize();
    //m_scene->SetGame(this);

    //add events
    EventManager::Instance().Subscribe("AddPoints", this, std::bind(&SpaceGame::OnAddPoints, this, std::placeholders::_1));
    EventManager::Instance().Subscribe("OnPlayerDead", this, std::bind(&SpaceGame::OnPlayerDead, this, std::placeholders::_1));

	return true;

}

void SpaceGame::Shutdown() {
    //empty
}

void SpaceGame::Update(float dt) {

	switch (m_state) {

	case SpaceGame::Title:

        if (g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE))
        {
            m_state = eState::StateGame;
            //m_scene->GetActorByName<kiko::Actor>("Background")->active;
        }
		break;

	case SpaceGame::StateGame:

        m_score = 0;
        m_lives = 3;
        m_state = eState::StartLevel;

		break;

	case SpaceGame::StartLevel:
        //create ship
    {
        auto player = INSTANTIATE(Player, "Player");
        player->transform = Transform{ {400, 300}, 0, 3 };
        player->Initialize();
        m_scene->Add(std::move(player));
        /*
        std::unique_ptr<Player> player = std::make_unique<Player>(
            100.0f,
            10.0f,
            DegToRad(270.0f),
            kiko::Transform{ {400, 300}, 0, 3 },
            "Player"
            );
        player->m_game = this;
        // create components
        
        auto renderComponent = CREATE_CLASS(SpriteRenderComponent);
        renderComponent->m_texture = GET_RESOURCE(kiko::Texture, "ship.png", kiko::g_renderer);
        player->AddComponent(std::move(renderComponent));

        //physics
        auto physicsComponent = CREATE_CLASS(EnginePhysicsComponent);
        physicsComponent->m_damping = 0.9f;
        player->AddComponent(std::move(physicsComponent));

        auto collisionComponent = CREATE_CLASS(CircleCollisionComponent);
        collisionComponent->m_radius = 30.0f;
        player->AddComponent(std::move(collisionComponent));


        player->Initialize();
        m_scene->Add(std::move(player));
        */
    }

        m_state = eState::Game;

        
		break;

	case SpaceGame::Game:

        
        m_spawnTimer += dt;
        if (m_spawnTimer >= m_spawnTime) {

            m_spawnTimer = 0;
            auto enemy = INSTANTIATE(Enemy, "Enemy");
            enemy->transform = Transform{ {400, 300}, 0, 3 };
            enemy->Initialize();
            m_scene->Add(std::move(enemy));

            //create enemy
            /*
            m_scene->Add(std::make_unique <Enemy>(
                20.0f,
                randomf(10.0f, 20.0f),
                DegToRad(270.0f),
                Transform{
                    {random(g_renderer.GetWidth()), random(g_renderer.GetHeight()) }, randomf(kiko::TwoPi), 2
                },
                randomf(1.0f, 2.0f),
                "Enemy"
                ));
                */

        }
        

		break;

	case SpaceGame::PlayerDead:
        if (m_lives == 3) {
            m_state = eState::StartLevel;
        }else if (m_lives == 2) {
            g_audioSystem.Play("Low Health Music", false);
            m_state = eState::StartLevel;
        }else if (m_lives == 1) {
           
            m_state = eState::GameOver;
        }
        m_lives--;
		break;

	case SpaceGame::GameOver:
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
    g_particleSystem.Update(dt);
    
}

void SpaceGame::Draw(kiko::Renderer& renderer) {
    
    if (m_state == eState::Title)
    {
        m_titleText->Draw(g_renderer, 350, 300);
    }

    m_scene->Draw(renderer);
    g_particleSystem.Draw(renderer);
    m_scoreText->Draw(g_renderer, 40, 20);
    m_livesText->Draw(g_renderer, 700, 20);
}



void SpaceGame::OnAddPoints(const kiko::Event& event)
{
    m_score += std::get<int>(event.data);
}

void SpaceGame::OnPlayerDead(const kiko::Event& event)
{
    m_lives--;
    m_state = eState::PlayerDead;
}
