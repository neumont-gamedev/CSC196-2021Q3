#pragma once
#include "core.h"

namespace nc
{
	struct Color
	{
		float r, g, b;

		Color() : r{ 0 }, g{ 0 }, b{ 0 } {}
		Color(float r, float g, float b) : r{ r }, g{ g }, b{ b } {}
		Color(DWORD rgb) // DWORD( x | b | g | r )
		{
			r = (rgb & 0xff) / 255.0f;
			g = ((rgb >> 8) & 0xff) / 255.0f;
			b = ((rgb >> 16) & 0xff) / 255.0f;
		}

		Color operator * (float s) const { return { this->r * s, this->g * s, this->b * s }; }


		operator DWORD() const { return ToRGB(); }

		DWORD ToRGB() const
		{
			// BYTE  = 1 byte | 8  bits
			// WORD  = 2 byte | 16 bits
			// DWORD = 4 byte | 32 bits
			BYTE _r = static_cast<BYTE>(r * 255); // (0 - 1) -> (0 - 255)
			BYTE _g = static_cast<BYTE>(g * 255);
			BYTE _b = static_cast<BYTE>(b * 255);

			return (_r | (_g << 8) | (_b << 16)); // DWORD( x | b | g | r )
		}

		static const Color white;
		static const Color red;
		static const Color green;
		static const Color blue;
	};
}