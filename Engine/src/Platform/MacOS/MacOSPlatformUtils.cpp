#include "kldpch.h"
#include "Kaleidoscope/Utils/PlatformUtils.h"

#ifdef KLD_PLATFORM_MACOS
// MacOS
#include "nfd.h"

namespace Kaleidoscope 
{
	std::optional<std::string> FileDialogs::OpenFile(const char* filter)
	{
		/*
		* filter syntax
		* ; Begin a new filter.
		* , Add a separate type to the filter.
		* example "png,jpg;pdf"
		*/
		nfdchar_t* outPath = NULL;
		nfdresult_t result = NFD_OpenDialog((nfdchar_t*)(filter), NULL, &outPath);

		if (result == NFD_OKAY) 
		{
			puts("Success!");
			puts(outPath);
			puts(outPath);
		}
		else if (result == NFD_CANCEL) 
		{
			puts("User pressed cancel.");
		}
		else 
		{
			printf("Error: %s\n", NFD_GetError());
		}

		return std::nullopt;
	}

	std::optional<std::string> FileDialogs::SaveFile(const char* filter)
	{
		/*
		* filter syntax
		* ; Begin a new filter.
		* , Add a separate type to the filter.
		* example "png,jpg;pdf"
		*/

		nfdchar_t* savePath = NULL;
		nfdresult_t result = NFD_OpenDialog((nfdchar_t*)(filter), NULL, &savePath);

		if (result == NFD_OKAY)
		{
			puts("Success!");
			puts(savePath);
			puts(savePath);
		}
		else if (result == NFD_CANCEL)
		{
			puts("User pressed cancel.");
		}
		else
		{
			printf("Error: %s\n", NFD_GetError());
		}

		return std::nullopt;
	}
}
#endif // KLD_PLATFORM_MACOS