#pragma once

#include <string>

namespace Kaleidoscope 
{
	class FileDialogs 
	{
	public:
		// 如果取消，则返回空字符串
		static std::string OpenFile(const char* filter);// 文件对话框右下角的文件后缀名过滤器
		static std::string SaveFile(const char* filter);
	};
}