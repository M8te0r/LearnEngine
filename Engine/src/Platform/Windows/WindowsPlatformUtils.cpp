#include "kldpch.h"
#include "Kaleidoscope/Utils/PlatformUtils.h"

#ifdef KLD_PLATFORM_WINDOWS

// Windows Only
#include<commdlg.h>
#include "GLFW/glfw3.h"
#define GLFW_EXPOSE_NATIVE_WIN32
#include "GLFW/glfw3native.h"

#include "Kaleidoscope/Core/Application.h"

namespace Kaleidoscope
{
	std::string FileDialogs::OpenFile(const char* filter)
	{
		OPENFILENAMEA ofn;//common dialog box structure
		CHAR szFile[260] = { 0 };// if using TCHAR macros
		
		//Initialize OPENFILENAME
		ZeroMemory(&ofn, sizeof(OPENFILENAME));
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = glfwGetWin32Window((GLFWwindow*)Application::Get().GetWindow().GetNativeWindow());
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);
		ofn.lpstrFilter = filter;
		ofn.nFilterIndex = 1;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
		if (GetOpenFileName(&ofn) == TRUE)
		{
			return ofn.lpstrFile;
		}
		return std::string();
	}

	std::string FileDialogs::SaveFile(const char* filter)
	{
		OPENFILENAMEA ofn;//common dialog box structure
		CHAR szFile[260] = { 0 };// if using TCHAR macros

		//Initialize OPENFILENAME
		ZeroMemory(&ofn, sizeof(OPENFILENAME));
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = glfwGetWin32Window((GLFWwindow*)Application::Get().GetWindow().GetNativeWindow());
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);
		ofn.lpstrFilter = filter;
		ofn.nFilterIndex = 1;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
		if (GetSaveFileName(&ofn) == TRUE)
		{
			return ofn.lpstrFile;
		}
		return std::string();
	}
}

#endif // KLD_PLATFORM_WINDOWS
