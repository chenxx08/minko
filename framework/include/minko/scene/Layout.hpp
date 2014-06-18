/*
Copyright (c) 2014 Aerys

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute,
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#pragma once

#include "minko/Common.hpp"

namespace minko
{
	typedef uint32_t Layouts;

	namespace scene
	{
		class Layout
		{
		public:

			class Group
			{
			public:
				static const Layouts DEFAULT;
				// static const Layouts STATIC;
				static const Layouts IGNORE_RAYCASTING;
				static const Layouts CULLING;
				static const Layouts PICKING;
			};

			class Mask
			{
			public:
				static const Layouts NOTHING;
				static const Layouts EVERYTHING;
				static const Layouts COLLISIONS_DYNAMIC_DEFAULT;
				// static const Layouts COLLISIONS_STATIC_DEFAULT;
				static const Layouts RAYCASTING_DEFAULT;
			};

		};
	}
}