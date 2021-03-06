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

#include "minko/render/Effect.hpp"

#include "minko/render/Pass.hpp"
#include "minko/data/Provider.hpp"

using namespace minko;
using namespace minko::render;

Effect::Effect(const std::string& name) :
_name(name),
_techniques(),
_fallback(),
_data(data::Provider::create()),
_uniformFunctions(),
_attributeFunctions(),
_indexFunction(nullptr),
_macroFunctions()
{

}

void
Effect::addTechnique(const std::string& name, Technique& passes)
{
    if (_techniques.count(name) != 0)
        throw std::logic_error("A technique named '" + name + "' already exists.");

    for (auto& pass : passes)
    {
        for (auto& func : _uniformFunctions)
            func(pass);
        for (auto& func : _attributeFunctions)
            func(pass);
        if (_indexFunction)
            _indexFunction->operator()(pass);
        for (auto& func : _macroFunctions)
            func(pass);
    }
    _techniques[name] = passes;
}

void
Effect::addTechnique(const std::string& name, Technique& passes, const std::string& fallback)
{
    _fallback[name] = fallback;

    addTechnique(name, passes);
}

void
Effect::removeTechnique(const std::string& name)
{
    if (_techniques.count(name) == 0)
        throw std::logic_error("The technique named '" + name + "' does not exist.");

    _techniques.erase(name);
    _fallback.erase(name);
}
