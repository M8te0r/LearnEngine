#include "kldpch.h"
#include "Kaleidoscope/Layer.h"

namespace Kaleidoscope
{
    Layer::Layer(const std::string &debugName) : m_DebugName(debugName)
    {
    }

    Layer::~Layer()
    {
    }

} // namespace Kaleidoscope
