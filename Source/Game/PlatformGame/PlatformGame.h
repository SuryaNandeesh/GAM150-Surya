#pragma once
#include "Framework/Event/EventManager.h"
#include "Framework/Game.h"
#include "Renderer/Text.h"

class PlatformGame : public kiko::Game, kiko::IEventListener {

public:
	enum eState {

		Title,
		StateGame,
		StartLevel,
		Game,
		PlayerDead,
		GameOver

	};

public:

	virtual bool Initialize() override;
	virtual void Shutdown() override;

	virtual void Update(float dt) override;
	virtual void Draw(kiko::Renderer& renderer) override;

	void SetState(eState state) { m_state = state; }
	void OnAddPoints(const kiko::Event& event);
	void OnPlayerDead(const kiko::Event& event);

private:

	eState m_state = eState::Title;
	float m_spawnTimer = 0;
	float m_spawnTime = 0;
};