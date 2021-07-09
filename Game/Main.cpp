#include "core.h"
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "Math/Random.h"
#include "Math/MathUtils.h"
#include "Graphics/Shape.h"
#include "Graphics/ParticleSystem.h"
#include <iostream>
#include <vector>
#include <string>


std::vector<nc::Vector2> points = { { -5, -5 }, { 5, -5 }, { 0, 10 }, { -5, -5 } };
nc::Shape shape{ points, nc::Color{ 0, 1, 0 } };
nc::Transform transform{ nc::Vector2{400, 300}, 0, 3 };

const float speed = 300;
float timer = 0;
nc::ParticleSystem particleSystem;
nc::Vector2 psPosition;

float deltaTime;
float gameTime = 0;

bool Update(float dt)
{
	deltaTime = dt;
	gameTime += deltaTime;

	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	timer += dt * 5;
	
	int x, y;
	Core::Input::GetMousePos(x, y);
	
	psPosition.x = static_cast<float>(x);
	psPosition.y = static_cast<float>(y);

	if (Core::Input::IsPressed(Core::Input::BUTTON_LEFT))
	{
		std::vector<nc::Color> colors = { nc::Color::white, nc::Color::red, nc::Color::green, nc::Color::blue, nc::Color::orange, nc::Color::yellow };
		particleSystem.Create(psPosition, 150, 2, colors[nc::RandomRangeInt(0, colors.size())], 150);
	}
	particleSystem.Update(dt);

	float thrust = 0;
	if (Core::Input::IsPressed('A')) transform.rotation -= 5 * dt;
	if (Core::Input::IsPressed('D')) transform.rotation += 5 * dt;
	if (Core::Input::IsPressed('W')) thrust = speed;
	
	//if (Core::Input::IsPressed('S')) input.y =  1;
	transform.position += nc::Vector2::Rotate(nc::Vector2::down, transform.rotation) * thrust * dt;
	transform.position.x = nc::Wrap(transform.position.x, 0.0f, 800.0f);
	transform.position.y = nc::Wrap(transform.position.y, 0.0f, 600.0f);

	particleSystem.Create(transform.position, 3, 2, nc::Color::white, 50);

	return quit;
}

void Draw(Core::Graphics& graphics)
{
	float scale = 1 + (std::sin(timer) + 1) * 2;
	shape.Draw(graphics, transform);
	particleSystem.Draw(graphics);

	nc::Color color = nc::Lerp(nc::Color::green, nc::Color::orange, psPosition.x / 800);
	graphics.SetColor(color);

	graphics.DrawString(10, 10, std::to_string(deltaTime).c_str());
	graphics.DrawString(10, 20, std::to_string(gameTime).c_str());
	graphics.DrawString(10, 30, std::to_string(1 / deltaTime).c_str());
	graphics.DrawString(10, 40, std::to_string(psPosition.Length()).c_str());
}

int main()
{
	char name[] = "CSC196";
	Core::Init(name, 800, 600, 60);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);
	particleSystem.Startup();
	Core::GameLoop();
	Core::Shutdown();
	particleSystem.Shutdown();
}