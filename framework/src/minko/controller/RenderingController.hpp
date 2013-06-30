/*
Copyright (c) 2013 Aerys

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
#include "minko/controller/AbstractController.hpp"

namespace
{
	using namespace minko::scene;
	using namespace minko::render;
	using namespace minko::render;
}

namespace minko
{
	namespace controller
	{
		class RenderingController :
			public AbstractController,
			public std::enable_shared_from_this<RenderingController>
		{
		public:
			typedef std::shared_ptr<RenderingController>	Ptr;

		private:
			typedef std::shared_ptr<Node>				NodePtr;
			typedef std::shared_ptr<AbstractController>	AbsCtrlPtr;
			typedef std::shared_ptr<SurfaceController>	SurfaceCtrlPtr;
			typedef std::shared_ptr<DrawCall>			DrawCallPtr;

		private:
			std::shared_ptr<AbstractContext>			_context;
			std::list<std::shared_ptr<DrawCall>>		_drawCalls;

			Signal<Ptr>::Ptr							_enterFrame;
			Signal<Ptr>::Ptr							_exitFrame;

			Signal<AbsCtrlPtr, NodePtr>::Slot			_targetAddedSlot;
			Signal<AbsCtrlPtr, NodePtr>::Slot			_targetRemovedSlot;
			Signal<NodePtr, NodePtr, NodePtr>::Slot		_addedSlot;
			Signal<NodePtr, NodePtr, NodePtr>::Slot		_removedSlot;
			Signal<NodePtr, NodePtr, NodePtr>::Slot		_rootDescendantAddedSlot;
			Signal<NodePtr, NodePtr, NodePtr>::Slot		_rootDescendantRemovedSlot;
			Signal<NodePtr, NodePtr, AbsCtrlPtr>::Slot	_controllerAddedSlot;
			Signal<NodePtr, NodePtr, AbsCtrlPtr>::Slot	_controllerRemovedSlot;

		public:
			static
			Ptr
			create(std::shared_ptr<AbstractContext> context)
			{
				auto ctrl = std::shared_ptr<RenderingController>(new RenderingController(context));

				ctrl->initialize();

				return ctrl;
			}

			void
			render();

			inline
			Signal<Ptr>::Ptr
			enterFrame()
			{
				return _enterFrame;
			}

			inline
			Signal<Ptr>::Ptr
			exitFrame()
			{
				return _exitFrame;
			}

		private:
			RenderingController(std::shared_ptr<AbstractContext> context) :
				AbstractController(),
				_context(context),
				_enterFrame(Signal<Ptr>::create()),
				_exitFrame(Signal<Ptr>::create())
			{
			}

			void
			initialize();

			void
			targetAddedHandler(std::shared_ptr<AbstractController>, NodePtr target);

			void
			targetRemovedHandler(std::shared_ptr<AbstractController> ctrl, NodePtr target);

			void
			addedHandler(NodePtr node, NodePtr target, NodePtr parent);

			void
			removedHandler(NodePtr node, NodePtr target, NodePtr parent);

			void
			rootDescendantAddedHandler(NodePtr	node,
										NodePtr	target,
										NodePtr	parent);

			void
			rootDescendantRemovedHandler(NodePtr	node,
											NodePtr	target,
											NodePtr	parent);
			void
			controllerAddedHandler(NodePtr								node,
									NodePtr								target,
									std::shared_ptr<AbstractController>	ctrl);

			void
			controllerRemovedHandler(NodePtr								node,
										NodePtr								target,
										std::shared_ptr<AbstractController>	ctrl);

			void
			addSurfaceController(std::shared_ptr<SurfaceController> ctrl);

			void
			removeSurfaceController(std::shared_ptr<SurfaceController> ctrl);

			void
			geometryChanged(std::shared_ptr<SurfaceController>);

			void
			materialChanged(std::shared_ptr<SurfaceController>);
		};
	}
}
