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
			: pos(p), scale(s), rotation(a) {}
		Vector2 pos;
		Vector2 scale;
		float rotation;
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
		Vector2 bounds;
		Vector2 radi;
	};
	
	class CAsset
	{
	public:
		CAsset(const std::string &n, int f = 1, int cf = 1, const Color &c = WHITE)
			: name(n), renderArea((Rectangle){0.0f, 0.0f, 64.0f * f, 64.0f}), frames(f), currentFrame(cf), col(c) {}
		CAsset(const std::string &n, Rectangle &ra, int f = 1, int cf = 1, const Color &c = WHITE)
			: name(n), renderArea(ra), frames(f), currentFrame(cf), col(c) {}
		const std::string name;
		Rectangle renderArea;
		int frames;
		int currentFrame;
		Color col;
	};
	
	typedef std::tuple< CTransform, CAsset, CBBox > Components;
	typedef std::tuple< std::vector < CTransform >, std::vector < CAsset >, std::vector < CBBox > > CompContainer;
	typedef std::variant< CTransform, CAsset, CBBox > Component;
	
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
}