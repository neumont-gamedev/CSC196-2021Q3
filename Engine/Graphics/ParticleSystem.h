#pragma once
#include "../Math/Vector2.h"
#include "../Math/Color.h"
#include <vector>

namespace nc
{
	class ParticleSystem
	{
	private:
		struct Particle
		{
			Vector2 position;
			Vector2 prevPosition;
			Vector2 velocity;
			Color color;
			float lifetime;
			bool active{ false };

			static bool IsNotActive(const Particle& particle) { return (particle.active == false); }
		};

	public:
		void Startup();
		void Shutdown();

		void Update(float dt);
		void Draw(Core::Graphics& graphics);

		void Create(const Vector2& position,
			size_t count,
			float lifetime,
			const Color& color,
			float minSpeed,
			float maxSpeed);

	private:
		std::vector<Particle> particles;
	};
}
