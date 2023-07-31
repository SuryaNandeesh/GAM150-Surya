#include "SpaceGame.h"
#include "Framework/Game.h"

#include "Player.h"
#include "Enemy.h"

#include "Framework/Scene.h"
#include "Framework/Emitter.h"

#include "Renderer/Renderer.h"
#include "Renderer/ModelManager.h"
#include "Renderer/ParticleSystem.h"

#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"


using namespace kiko;

bool SpaceGame::Initialize() {

    m_font = std::make_shared<Font>("ARCADECLASSIC.ttf", 24);

	m_scoreText = std::make_unique<Text>(m_font);
    m_scoreText->Create(kiko::g_renderer, "SCORE ", kiko::Color{ 28, 163, 39, 1 });

	m_livesText = std::make_unique<Text>(m_font);
    m_livesText->Create(kiko::g_renderer, "LIVES ", kiko::Color{ 207, 34, 25, 1 });

    m_titleText = std::make_unique<Text>(m_font);
    m_titleText->Create(kiko::g_renderer, "ASTEROID", kiko::Color{ 1, 1, 1, 1 });

	g_audioSystem.AddAudio("laser", "laser.wav");
	g_audioSystem.AddAudio("death", "bwomp.wav");
	g_audioSystem.AddAudio("Background Music", "08 Red Sun (Maniac Agenda Mix).mp3");
	g_audioSystem.AddAudio("Low Health Music", "Critical Health.mp3");
	g_audioSystem.AddAudio("gameover", "gameover.mp3");
    kiko::g_audioSystem.Play("Background Music", true);
    

    m_scene = std::make_unique<Scene>();

	return true;

}


void SpaceGame::Shutdown() {

}

void SpaceGame::Update(float dt) {

	switch (m_state) {

	case SpaceGame::Title:

        if (g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE))
        {
            m_state = eState::StateGame;
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
        std::unique_ptr<Player> player = std::make_unique<Player>(
            100.0f,
            10.0f,
            DegToRad(270.0f),
            kiko::Transform{ {400, 300}, 0, 3 },
            kiko::g_manager.Get("ship.txt"),
            "Player",
            0.95f
        );
        player->m_game = this;
        m_scene->Add(std::move(player));
    }

        m_state = eState::Game;

        
		break;

	case SpaceGame::Game:

        
        m_spawnTimer += dt;
        if (m_spawnTimer >= m_spawnTime) {

            m_spawnTimer = 0;
            //create enemy
            m_scene->Add(std::make_unique <Enemy>(
                20.0f,
                randomf(10.0f, 20.0f),
                DegToRad(270.0f),
                Transform{
                    {random(g_renderer.GetWidth()), random(g_renderer.GetHeight()) }, randomf(kiko::TwoPi), 2
                },
                g_manager.Get("enemy.txt"),
                randomf(1.0f, 2.0f),
                "Enemy",
                0.95f
                ));

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
    kiko::g_particleSystem.Update(dt);
    
}

void SpaceGame::Draw(kiko::Renderer& renderer) {
    
    if (m_state == eState::Title)
    {
        m_titleText->Draw(g_renderer, 350, 300);
    }

    m_scene->Draw(renderer);
    kiko::g_particleSystem.Draw(renderer);
    m_scoreText->Draw(g_renderer, 40, 20);
    m_livesText->Draw(g_renderer, 700, 20);
    

}
