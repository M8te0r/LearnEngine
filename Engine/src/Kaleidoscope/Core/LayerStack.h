#pragma once

#include "Kaleidoscope/Core/Core.h"
#include "Kaleidoscope/Core/Layer.h"

#include <vector>

namespace Kaleidoscope
{
    class LayerStack
    {
    public:
        LayerStack();
        ~LayerStack();

        void PushLayer(Layer *layer);
        void PushOverlay(Layer *overlay);
        void PopLayer(Layer *layer);
        void PopOverlay(Layer *overlay);

        std::vector<Layer *>::iterator begin() { return m_Layers.begin(); }
        std::vector<Layer *>::iterator end() { return m_Layers.end(); }

    private:
        std::vector<Layer *> m_Layers;
        unsigned int m_LayerInsertIndex = 0; // 记录layer数组的插入位置
    };

} // namespace Kaleidoscope