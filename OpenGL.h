#define _CRT_SECURE_NO_WARNINGS

#ifndef OPENGL_H
#define OPENGL_H

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <time.h>
#include <string>
#include <sstream>

#include "wglext.h"
#include "glext.h"

#include "glm/vec3.hpp"// glm::vec3

using namespace glm;

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

//#include "Debug.h"
//using namespace Debug;

#define WIN_WIDTH 640
#define WIN_HEIGHT 480

#define VERT_OFFSET 0
#define VERT_TEMPERATURE 1

namespace OGL
{
	class OpenGL
	{
	private:

		HWND hWnd;
		HDC hDC;
		HGLRC hRC;

		GLuint shaderProgram;
		GLuint vertexShader;
		GLuint fragmentShader;

		PFNGLCREATEPROGRAMPROC glCreateProgram;
		PFNGLCREATESHADERPROC glCreateShader;
		PFNGLSHADERSOURCEPROC glShaderSource;
		PFNGLCOMPILESHADERPROC glCompileShader;
		PFNGLATTACHSHADERPROC glAttachShader;
		PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation;
		PFNGLLINKPROGRAMPROC glLinkProgram;
		PFNGLUSEPROGRAMPROC glUseProgram;
		PFNGLVALIDATEPROGRAMPROC glValidateProgram;
		PFNGLGETPROGRAMIVPROC glGetProgramiv;
		PFNGLGETSHADERIVPROC glGetShaderiv;
		PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
		PFNGLDELETEPROGRAMPROC glDeleteProgram;
		PFNGLDELETESHADERPROC glDeleteShader;

		bool GLInitExtensions();
		bool GLShaderInit();
		bool GLCheckProgram(GLuint& shaderProgram);
		bool GLCheckShader(GLuint& shader);
		//void GLMatrixInit();

	public:
		//mat4 MVP;
		GLuint ColorLocation;

		PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
		PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
		PFNGLGENBUFFERSPROC glGenBuffers;
		PFNGLBINDBUFFERPROC glBindBuffer;
		PFNGLBUFFERDATAPROC glBufferData;
		PFNGLDELETEBUFFERSPROC glDeleteBuffers;
		
		PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation;
		PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
		PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
		PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
		PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;
		PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;
		PFNGLVERTEXATTRIB1FPROC glVertexAttrib1f;
		PFNGLUNIFORM1FPROC glUniform1f;
		PFNGLUNIFORM3FPROC glUniform3f;
		PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;

		PFNGLDEBUGMESSAGECALLBACKPROC glDebugMessageCallback;
		PFNGLDEBUGMESSAGECONTROLPROC glDebugMessageControl;

		bool GLInit(HWND hWnd);
		void GLRenderStart();
		void GLRenderEnd();
		void GLClear();
		void GLClose();

		int GetRand(int seed);
	};

}

extern OGL::OpenGL openGL;

#endif
