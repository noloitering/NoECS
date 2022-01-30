#include "System.h"

using namespace NoECS;

void EntitySystem::update()
{
	entities.update();
}

void EntitySystem::render()
{
	for (auto tag : entities.getEntityMap())
	{
		for (auto e : tag.second)
		{
			CTransform& et = e->getComponent< CTransform >();
			if ( et.owned )
			{
				CSprite& es = e->getComponent< CSprite >();
				CPoly& ep = e->getComponent< CPoly >();
				if ( ep.owned )
				{
					Vector2 size = {ep.radius * et.scale.x, ep.radius * et.scale.y};
					DrawPoly(et.pos, ep.sides, size.x, et.angle, ep.backCol);
					DrawPolyLinesEx(et.pos, ep.sides, size.x + ep.outlineThick / 2, et.angle, ep.outlineThick, ep.outlineCol);
				}
				if ( es.owned )
				{
					if ( es.texture )
					{
						// TODO: optimize, maybe use some extra memory in CSprite
						Vector2 size = {es.texture->width / es.frames, es.texture->height};
						Rectangle dest = (Rectangle){et.pos.x, et.pos.y, size.x * et.scale.x, size.y * et.scale.y};
						Vector2 origin = (Vector2){size.x / 2 * et.scale.x, size.y / 2 * et.scale.y};
						DrawTexturePro(*(es.texture), es.renderArea, dest, origin, et.angle, es.col);
					}
				}
			}
		}
	}
}