#include "Game.h"
#include "Actors/Player.h"
#include "Actors/Enemy.h"
#include "Actors/Projectile.h"

void Game::Initialize()
{
	engine = std::make_unique<nc::Engine>(); // new Engine
	engine->Startup();
	scene = std::make_unique<nc::Scene>(); // new Scene
	scene->engine = engine.get();

	engine->Get<nc::AudioSystem>()->AddAudio("explosion", "explosion.wav");
	engine->Get<nc::AudioSystem>()->AddAudio("player_fire", "player_fire.wav");
	engine->Get<nc::AudioSystem>()->AddAudio("enemy_fire", "enemy_fire.wav");

	engine->Get<nc::EventSystem>()->Subscribe("AddPoints", std::bind(&Game::OnAddPoints, this, std::placeholders::_1));
	engine->Get<nc::EventSystem>()->Subscribe("PlayerDead", std::bind(&Game::OnPlayerDead, this, std::placeholders::_1));
}

void Game::Shutdown()
{
	scene->RemoveAllActors();
	engine->Shutdown();
}

void Game::Update(float dt)
{
	stateTimer += dt;

	switch (state)
	{
	case Game::eState::Title:
		if (Core::Input::IsPressed(VK_SPACE))
		{
			state = eState::StartGame;
		}
		break;
	case Game::eState::StartGame:
		score = 0;
		lives = 3;
		state = eState::StartLevel;
		break;
	case Game::eState::StartLevel:
		UpdateStartLevel(dt);
		state = eState::Game;
		break;
	case Game::eState::Game:
		if (scene->GetActors<Enemy>().size() == 0)
		{
			state = eState::GameOver;
		}
		break;
	case Game::eState::GameOver:
		break;
	default:
		break;
	}

	engine->Update(dt);
	scene->Update(dt);
}

void Game::Draw(Core::Graphics& graphics)
{
	switch (state)
	{
	case Game::eState::Title:
		graphics.SetColor(nc::Color::red);
		graphics.DrawString(380, 300 + static_cast<int>(std::sin(stateTimer * 6.0f) * 10.0f), "VECTREX");
		graphics.SetColor(nc::Color::green);
		graphics.DrawString(340, 360, "Press Space to Start");
		break;
	case Game::eState::StartGame:
		break;
	case Game::eState::StartLevel:
		break;
	case Game::eState::Game:
		break;
	case Game::eState::GameOver:
		graphics.SetColor(nc::Color::red);
		graphics.DrawString(380, 300, "GAME OVER");
		break;
	default:
		break;
	}

	graphics.SetColor(nc::Color::white);
	graphics.DrawString(30, 20, std::to_string(score).c_str());
	graphics.DrawString(750, 20, std::to_string(lives).c_str());

	scene->Draw(graphics);
	engine->Draw(graphics);
}

void Game::UpdateTitle(float dt)
{
	if (Core::Input::IsPressed(VK_SPACE))
	{
		stateFunction = &Game::UpdateStartLevel;
		//state = eState::StartGame;
	}
}

void Game::UpdateStartLevel(float dt)
{
	scene->AddActor(std::make_unique<Player>(nc::Transform(nc::Vector2(400.0f, 300.0f), 0.0f, 3.0f), engine->Get<nc::ResourceSystem>()->Get<nc::Shape>("player.txt"), 300.0f));
	for (size_t i = 0; i < 2; i++)
	{
		scene->AddActor(std::make_unique<Enemy>(nc::Transform{ nc::Vector2{nc::RandomRange(0.0f, 800.0f), nc::RandomRange(0.0f, 600.0f)}, nc::RandomRange(0.0f, nc::TwoPi), 3.0f }, engine->Get<nc::ResourceSystem>()->Get<nc::Shape>("enemy.txt"), 100.0f));
	}
}

void Game::OnAddPoints(const nc::Event& event)
{
	score += std::get<int>(event.data);
}

void Game::OnPlayerDead(const nc::Event& event)
{
	lives--;
	std::cout << std::get<std::string>(event.data) << std::endl;
	state = eState::GameOver;
}
