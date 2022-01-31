#include "../../src/System.h"

Vector2 window = {470, 720};
Vector2 center = {window.x / 2, window.y / 2};
Vector2 scale = {1.0, 1.0};
float size = 35;
int fps = 60;

int main(int argc, char ** argv)
{
	InitWindow(window.x, window.y, "Sprite");
	SetTargetFPS(fps);
	NoECS::EntitySystem game = NoECS::EntitySystem();
	std::shared_ptr< Texture > texture = std::make_shared< Texture >(LoadTexture("../resources/player3.png"));
	std::shared_ptr< NoECS::Entity > player = game.entities.addEntity("player");
	NoECS::CTransform& transform = player->addComponent< NoECS::CTransform >(center, scale, 0);
	NoECS::CSprite& sprite = player->addComponent< NoECS::CSprite >(texture, 8);
	size_t frame = 0;
	
	while ( !WindowShouldClose() )
	{
		game.update();
		if ( IsKeyDown(KEY_SPACE) )
		{
			sprite.renderArea.x = 64 * 7;
		}
		else if ( IsKeyDown(KEY_W) || IsKeyDown(KEY_UP) )
		{
			sprite.renderArea.x = 64 * 4;
		}
		else if ( IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN) )
		{
			sprite.renderArea.x = 64 * 3;
		}
		else if ( IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT) )
		{
			frame++;
			if ( ((frame/20)%2) == 0 )
			{
				sprite.renderArea.x = 64 * 1;
			}
			else
			{
				sprite.renderArea.x = 64 * 2;
			}
			
			sprite.renderArea.width = 64;
		}
		else if ( IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT) )
		{
			frame++;
			if ( ((frame/20)%2) == 0 )
			{
				sprite.renderArea.x = 64 * 2;
			}
			else
			{
				sprite.renderArea.x = 64 * 1;
			}
			sprite.renderArea.width = -64;
		}
		else if ( IsKeyDown(KEY_E) || IsKeyDown(KEY_Q) || IsKeyDown(KEY_F) ||  IsKeyDown(KEY_Z) || IsKeyDown(KEY_X) || IsKeyDown(KEY_C))
		{
			sprite.renderArea.x = 64 * 6;
		}
		else // return to idle
		{
			if ( sprite.renderArea.x >= 64 * 4 &&  sprite.renderArea.x <= 64 * 5 ) // falling
			{
				sprite.renderArea.x = 64 * 5;
			}
			else
			{
				sprite.renderArea.x = 0;
			}
		}
		BeginDrawing();
			ClearBackground(BLACK);
			game.render();
			DrawText("Controls:\nWASD = Move\nSPACE = Talk\nEFZXC = Body Slam", 10, center.y + 74, 20, RAYWHITE);
		EndDrawing();
	}
}