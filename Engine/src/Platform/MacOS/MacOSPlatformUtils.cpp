#include "kldpch.h"
#include "Kaleidoscope/Utils/PlatformUtils.h"

namespace Kaleidoscope 
{
	std::string FileDialogs::OpenFile(const char* filter) 
	{
		KLD_CORE_ERROR("MacOS not support Open File now!");
		return " ";
	}

	std::string FileDialogs::SaveFile(const char* filter) 
	{
		KLD_CORE_ERROR("MacOS not support Save File now!");
		return " ";
	}
}