#pragma once

#include <memory>
#include <variant>
#include <vector>

#include "raylib.h"

namespace NoECS
{
	class CInterface
	{
	public:
		bool owned = false;
	};
	
	class CTransform : public CInterface
	{
	public:
		CTransform(const Vector2 &p = Vector2{0.0, 0.0}, const Vector2 &s = Vector2{1.0, 1.0}, float a = 0.0)
			: pos(p), scale(s), angle(a) {}
		Vector2 pos = {0, 0};
		Vector2 scale = {1, 1};
		float angle = 0;
	};
	
	class CBBox : public CInterface
	{
	public:
		CBBox(const Vector2 &b = Vector2{0.0, 0.0})
			: bounds(b), radi(Vector2{b.x / 2, b.y / 2}) {}
		CBBox(std::shared_ptr<CTransform> transform)
		{
			bounds = (Vector2) {64 * transform->scale.x, 64 * transform->scale.y};
			radi = (Vector2) {32 * transform->scale.x, 32 * transform->scale.y};
		}
		Vector2 bounds = {0, 0};
		Vector2 radi;
	};
	
	class CSprite : public CInterface
	{
	public:
		CSprite(std::shared_ptr< Texture2D > t=nullptr, int f = 1, int cf = 1, const Color &c = WHITE)
			: texture(t), renderArea((Rectangle){0.0f, 0.0f, 64, 64}), frames(f), currentFrame(cf), col(c) {}
		CSprite(std::shared_ptr< Texture2D > t, Rectangle &ra, int f = 1, int cf = 1, const Color &c = WHITE)
			: texture(t), renderArea(ra), frames(f), currentFrame(cf), col(c) {}
		std::shared_ptr< Texture2D > texture;
		int frames = 1;
		int currentFrame = 1;
		Color col = WHITE;
		Rectangle renderArea;
	};
	
	class CPoly : public CInterface
	{
	public:
		CPoly(const Color& bc=GRAY, const Color& oc=BLACK, float r=0, int s=0, int ot=0)
			: backCol(bc), outlineCol(oc), radius(r), sides(s), outlineThick(ot) {}
		Color backCol = GRAY;
		Color outlineCol = BLACK;
		float radius = 0;
		int sides = 4;
		int outlineThick = 0;
	};
	
	typedef std::tuple< CTransform, CSprite, CBBox, CPoly > Components;
	typedef std::tuple< std::vector < CTransform >, std::vector < CSprite >, std::vector < CBBox >, std::vector< CPoly > > CompContainer;
	typedef std::variant< CTransform, CSprite, CBBox, CPoly > Component;
	
	class CContainer // to be inherited from
	{
	protected:
		Components components;
	public:
		CContainer() {}
		CContainer(Components c)
			: components(c) {}
		virtual ~CContainer() {}
		
		Components getComponents()
		{
			
			return components;
		}
		
		void setComponents(Components c)
		{
			components = c;
		}
		
		template <class C>
		C& getComponent()
		{
			
			return std::get< C >(components);
		}
	
		template <class C, typename... Args>
		C& addComponent(Args&&... CArgs)
		{
			auto& component = getComponent<C>();
			component = C(std::forward<Args>(CArgs)...);
			component.owned = true;
		
			return component;
		}
	
		template <class C>
		C& addComponent(C& newComponent)
		{
			auto& component = getComponent< C >();
			component = newComponent;
			component.owned = true;
		
			return component;
		}
	
		template <class C>
		bool hasComponent()
		{
		
			return getComponent< C >().owned;
		}
	};
}