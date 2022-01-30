#include "../../src/System.h"

Vector2 window = {470, 720};
Vector2 center = {window.x / 2, window.y / 2};
Vector2 scale = {1.0, 1.0};
float size = 35;
int fps = 60;

int main(int argc, char ** argv)
{
	InitWindow(window.x, window.y, "boundsBounce");
	SetTargetFPS(fps);
	NoECS::EntitySystem game = NoECS::EntitySystem();
	std::shared_ptr< NoECS::Entity > player = game.entities.addEntity("player");
	NoECS::CTransform& transform = player->addComponent< NoECS::CTransform >(center, scale, 270);
	NoECS::CPoly& poly = player->addComponent< NoECS::CPoly >(MAROON, GRAY, size, 3, 0);
	
	Vector2 vel;
	if ( argc > 2 )
	{
		vel.x = std::stof(argv[1]);
		vel.y = std::stof(argv[2]);
	}
	else
	{
		vel.x = GetRandomValue(-1 * center.x / fps, center.x / fps);
		vel.y = GetRandomValue(-1 * center.y / fps, center.y / fps);
	}
	
	
	while ( !WindowShouldClose() )
	{
		game.update();
		transform.pos.x += vel.x;
		transform.pos.y += vel.y;
		if ( transform.pos.x <= size || transform.pos.x >= window.x - size)
		{
			vel.x = vel.x * -1;
			poly.backCol = {GetRandomValue(0, 255), GetRandomValue(0, 255), GetRandomValue(0, 255), 255};
		}
		if ( transform.pos.y <= size || transform.pos.y >= window.y - size)
		{
			vel.y = vel.y * -1;
			poly.backCol = {GetRandomValue(0, 255), GetRandomValue(0, 255), GetRandomValue(0, 255), 255};
		}
		BeginDrawing();
			ClearBackground(BLACK);
			game.render();
		EndDrawing();
	}
}