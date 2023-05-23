#include "kldpch.h"
#include "Kaleidoscope/Core/LayerStack.h"

namespace Kaleidoscope
{
    LayerStack::LayerStack()
    {
    }

    LayerStack::~LayerStack()
    {
        for (Layer *layer : m_Layers)
        {
            delete layer;
        }
    }

    void LayerStack::PushLayer(Layer *layer)
    {
        // 在m_LayerInsert位置插入layer
        m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
        m_LayerInsertIndex++;
    }

    void LayerStack::PushOverlay(Layer *overlay)
    {
        m_Layers.emplace_back(overlay);
    }

    void LayerStack::PopLayer(Layer *layer)
    {
        // 寻找待pop的layer的位置it
        auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);

        // 如果找到了，
        if (it != m_Layers.end())
        {
            m_Layers.erase(it);
            m_LayerInsertIndex--;
        }
    }

    void LayerStack::PopOverlay(Layer *overlay)
    {
        auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
        if (it != m_Layers.end())
        {
            m_Layers.erase(it);
        }
    }
} // namespace Kaleidoscope
