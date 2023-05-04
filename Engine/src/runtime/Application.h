#pragma once

#include "Core.h"
namespace Kaleidoscope
{
    class Application
    {
    private:
        /* data */
    public:
        Application();
        virtual ~Application();
        void Run();
    };

    // 在客户端定义
    Application *CreateApplication();

} // namespace Kaleidoscope
