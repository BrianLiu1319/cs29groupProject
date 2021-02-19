#pragma once
#include"Tower.h"

class Land
{

	
	private:
		int width;
		int height;
		TPosition centerPosition; //
		TPosition oPoint;
		bool empty;
		Texture image;
		Sprite spLand;
		
	public:
		Land();
		Land(int num, TPosition pt);
		void setWidth(int x)
		{
			width = x;
		}
		int getWidth()
		{
			return width;
		}
		void setHeight(int height)
		{
			height = height;
		}
		int getHeight()
		{
			return height;
		}
		TPosition getLandPosition()
		{
			return centerPosition;
		}
		void setPosition(TPosition tp)
		{
			centerPosition = tp;
		}
		Sprite getSprite()
		{
			return spLand;
		}
		TPosition getOPosition()
		{
			return oPoint;
		}
		void setOposition(TPosition tp)
		{
			oPoint = tp;
		}
		void setEmpty(bool em)
		{
			empty = em;
		}
		bool getEnpty()
		{
			return empty;
		}

	};




