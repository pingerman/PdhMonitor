#ifndef DEBUG_H
#define DEBUG_H

#include <Windows.h>
#include <iostream>
#include <string>
#include <Pdh.h>
#include <PdhMsg.h>
#include "OpenGL.h"

#define DEBUG_ASSERT(condition, message)			\
        do {										\
            static bool s_bIgnoreAssert = false;	\
            if (!s_bIgnoreAssert && !(condition)) {	\
				Debuger::OutputMessage(message);	\
				__debugbreak();						\
            }										\
        } while(0)

#define GL_CHECK_ERROR(str) openGL.CheckGLError(str, glGetError())

namespace Debug
{
	class Debuger
	{
	private:

	public:
		static LPWSTR ConvertString(const std::string& instr);
		static void OutputMessage(const TCHAR* title, const TCHAR* msg);
		static void OutputMessage(const TCHAR* msg);

		static const TCHAR* PdhConvert(PDH_STATUS status);
		static void CheckPdhStatus(const TCHAR* title, PDH_STATUS status);

		static void APIENTRY GLDebugMessageCallback(GLenum source, GLenum type, GLuint id,
			GLenum severity, GLsizei length,
			const GLchar *msg, const void *data);
		static void CheckGLError(std::string comment, GLenum format);
		static std::string convertGLErrorToString(GLenum format);
	};
}

#endif
