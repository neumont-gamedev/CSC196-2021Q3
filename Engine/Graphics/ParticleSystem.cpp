#include "ParticleSystem.h"
#include "../Math/Random.h"

namespace nc
{
	void ParticleSystem::Startup()
	{
		particles.reserve(1000);
		particles.resize(1000);
	}

	void ParticleSystem::Shutdown()
	{
		particles.clear();
	}

	void ParticleSystem::Update(float dt)
	{
		for (Particle& particle : particles)
		{
			if (particle.active)
			{
				particle.lifetime = particle.lifetime - dt;
				particle.active = particle.lifetime > 0;

				particle.prevPosition = particle.position;
				//particle.velocity += nc::Vector2{ 0, 100 } * dt;
				particle.position += (particle.velocity * dt);
			}
		}
	}
	
	void ParticleSystem::Draw(Core::Graphics& graphics)
	{
		for (Particle& particle : particles)
		{
			if (particle.active)
			{
				graphics.SetColor(particle.color);
				graphics.DrawLine(particle.position.x, particle.position.y, particle.prevPosition.x, particle.prevPosition.y);
			}
		}
	}

	void ParticleSystem::Create(const Vector2& position, size_t count, float lifetime, const Color& color, float minSpeed, float maxSpeed)
	{
		std::vector<nc::Color> colors{ nc::Color::white, nc::Color::red, nc::Color::green, nc::Color::blue, nc::Color::yellow, nc::Color::purple };

		for (size_t i = 0; i < count; i++)
		{
			auto particle = std::find_if(particles.begin(), particles.end(), Particle::IsNotActive);
			if (particle != particles.end())
			{
				particle->active = true;
				particle->lifetime = random(lifetime * 0.75f, lifetime);
				particle->position = position;
				particle->prevPosition = position;
				particle->color = colors[rand() % colors.size()];

				float speed = random(minSpeed, maxSpeed);
				particle->velocity = Vector2{ random(-1, 1), random(-1, 1) } * speed;
			}
		}
	}
}