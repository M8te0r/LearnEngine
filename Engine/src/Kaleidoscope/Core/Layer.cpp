#include "kldpch.h"
#include "Kaleidoscope/Core/Layer.h"

namespace Kaleidoscope
{
    Layer::Layer(const std::string &debugName) : m_DebugName(debugName)
    {
    }

    Layer::~Layer()
    {
    }

} // namespace Kaleidoscope
