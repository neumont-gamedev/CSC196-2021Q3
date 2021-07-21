#include "Game.h"

Game game;

bool Update(float dt)
{
	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);
	game.Update(dt);
	
	//int x, y;
	//Core::Input::GetMousePos(x, y);
	//
	//psPosition.x = static_cast<float>(x);
	//psPosition.y = static_cast<float>(y);
	//if (Core::Input::IsPressed(Core::Input::BUTTON_LEFT))
	//{
	//	std::vector<nc::Color> colors = { nc::Color::white, nc::Color::red, nc::Color::green, nc::Color::blue, nc::Color::orange, nc::Color::yellow };
	//	engine.Get<nc::ParticleSystem>()->Create(psPosition, 150, 2, colors[nc::RandomRangeInt(0, colors.size())], 150);

	//	engine.Get<nc::AudioSystem>()->PlayAudio("explosion");
	//}

	return quit;
}

void Draw(Core::Graphics& graphics)
{
	game.Draw(graphics);
}

int inc(int i) { return ++i; }
int dec(int i) { return --i; }


int main()
{
	//int (*operation)(int);
	//operation = &dec;
	//std::cout << operation(5) << std::endl;

	//operation = &inc;
	//std::cout << operation(5) << std::endl;

	//system("pause");

	char name[] = "CSC196";
	Core::Init(name, 800, 600, 120);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	game.Initialize();

	Core::GameLoop();
	Core::Shutdown();

	game.Shutdown();
}