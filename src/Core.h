#pragma once

#include <cstring>
//#include <string.h>

#include "raylib.h"

// TODO: move to NoMEM
namespace NoMAD
{
	const size_t TAGBUFF = 51;
	const size_t INBUFF = 2001;
	extern size_t OBJCOUNT;
	
	struct ObjTag // hack to make tag const
	{
		char tag[TAGBUFF] = "Default";
		ObjTag(const char* t)
		{
			tag[0] = '\0';
			strncat(tag, t, TAGBUFF - 1);
		}
		
		bool operator<(const ObjTag& o) const // for map
		{
			int result = strcmp(tag, o.tag);
			
			return result < 0;
		}
	};
	
	class GameObj
	{
	protected:
		const size_t id = 0; // unique identifier
		const ObjTag tag = "Default"; // common identifier
		char inner[INBUFF] = ""; // short description or content
	public:
		GameObj(const size_t& num=OBJCOUNT, const char* type="Default", const char* in="")
			: id(num), tag(type) {setInner(in); OBJCOUNT++;}
		
		const size_t getId()
		{
			
			return id;
		}
		
		const char* getTag()
		{
			
			return tag.tag;
		}
		
		const char* getInner()
		{
			
			return inner;
		}
		
//		void setTag(const char* type)
//		{
//			// use strncat so null terminator is added to the end if 'in' is too big
//			tag[0] = '\0';
//			strncat(tag, type, TAGBUFF - 1);
//		}
		
		void setInner(const char* in)
		{
			// use strncat so null terminator is added to the end if 'in' is too big
			inner[0] = '\0';
			strncat(inner, in, INBUFF - 1);
		}
	};
}