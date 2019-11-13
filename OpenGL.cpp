#include "OpenGL.h"

namespace OGL
{

	bool OpenGL::GLInit(HWND hWnd)
	{
		this->hWnd = hWnd;

		hDC = GetDC(this->hWnd);

		PIXELFORMATDESCRIPTOR pfd;

		memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));

		pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		pfd.nVersion = 1;
		pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.cColorBits = 32;
		pfd.cDepthBits = 24;

		GLuint pixelFormat = ChoosePixelFormat(hDC, &pfd);
		SetPixelFormat(hDC, pixelFormat, &pfd);

		HGLRC hRCTemp = wglCreateContext(hDC);

		wglMakeCurrent(hDC, hRCTemp);

		PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");

		if (!wglCreateContextAttribsARB)
		{
			wglMakeCurrent(NULL, NULL);
			wglDeleteContext(hRCTemp);
			hRCTemp = NULL;
			return false;
		}

		int attributes[] =
		{
			WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
			WGL_CONTEXT_MINOR_VERSION_ARB, 3,
			WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
			WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
			0
		};

		hRC = wglCreateContextAttribsARB(hDC, 0, attributes);

		if (!hRC)
		{
			wglMakeCurrent(NULL, NULL);
			wglDeleteContext(hRCTemp);
			hRCTemp = NULL;
			return false;
		}

		if (!GLInitExtensions())
			return false;

		//Дебагинг OpenGL отключен

		//glEnable(GL_DEBUG_OUTPUT);
		//glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

		//glDebugMessageCallback(Debuger::GLDebugMessageCallback, NULL);
		//GLuint unusedIds = 0;
		//glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, &unusedIds, true);
		//glDebugMessageControl(GL_DEBUG_SOURCE_API, GL_DEBUG_TYPE_ERROR, GL_DONT_CARE, 0, NULL, GL_TRUE);

		if (!GLShaderInit())
			return false;

		return true;

	}

	bool OpenGL::GLInitExtensions()
	{
		glCreateProgram = (PFNGLCREATEPROGRAMPROC)wglGetProcAddress("glCreateProgram");
		glUseProgram = (PFNGLUSEPROGRAMPROC)wglGetProcAddress("glUseProgram");
		glCreateShader = (PFNGLCREATESHADERPROC)wglGetProcAddress("glCreateShader");
		glShaderSource = (PFNGLSHADERSOURCEPROC)wglGetProcAddress("glShaderSource");
		glCompileShader = (PFNGLCOMPILESHADERPROC)wglGetProcAddress("glCompileShader");
		glAttachShader = (PFNGLATTACHSHADERPROC)wglGetProcAddress("glAttachShader");
		glBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC)wglGetProcAddress("glBindAttribLocation");
		glLinkProgram = (PFNGLLINKPROGRAMPROC)wglGetProcAddress("glLinkProgram");
		glValidateProgram = (PFNGLVALIDATEPROGRAMPROC)wglGetProcAddress("glValidateProgram");
		glGetProgramiv = (PFNGLGETPROGRAMIVPROC)wglGetProcAddress("glGetProgramiv");
		glGetShaderiv = (PFNGLGETSHADERIVPROC)wglGetProcAddress("glGetShaderiv");
		glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)wglGetProcAddress("glGetShaderInfoLog");
		glDeleteProgram = (PFNGLDELETEPROGRAMPROC)wglGetProcAddress("glDeleteProgram");
		glDeleteShader = (PFNGLDELETESHADERPROC)wglGetProcAddress("glDeleteShader");

		glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)wglGetProcAddress("glGenVertexArrays");
		glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)wglGetProcAddress("glBindVertexArray");
		glGenBuffers = (PFNGLGENBUFFERSPROC)wglGetProcAddress("glGenBuffers");
		glBindBuffer = (PFNGLBINDBUFFERPROC)wglGetProcAddress("glBindBuffer");
		glBufferData = (PFNGLBUFFERDATAPROC)wglGetProcAddress("glBufferData");
		glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)wglGetProcAddress("glDeleteBuffers");

		glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC)wglGetProcAddress("glGetAttribLocation");
		glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)wglGetProcAddress("glGetUniformLocation");
		glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)wglGetProcAddress("glVertexAttribPointer");
		glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glEnableVertexAttribArray");
		glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glDisableVertexAttribArray");
		glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)wglGetProcAddress("glDeleteVertexArrays");
		glVertexAttrib1f = (PFNGLVERTEXATTRIB1FPROC)wglGetProcAddress("glVertexAttrib1f");
		glUniform1f = (PFNGLUNIFORM1FPROC)wglGetProcAddress("glUniform1f");
		glUniform3f = (PFNGLUNIFORM3FPROC)wglGetProcAddress("glUniform3f");
		glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)wglGetProcAddress("glUniformMatrix4fv");

		glDebugMessageCallback = (PFNGLDEBUGMESSAGECALLBACKPROC)wglGetProcAddress("glDebugMessageCallback");
		glDebugMessageControl = (PFNGLDEBUGMESSAGECONTROLPROC)wglGetProcAddress("glDebugMessageControl");

		return true;
	}

	bool OpenGL::GLShaderInit()
	{
		FILE * vertexShaderFile = NULL;
		fopen_s(&vertexShaderFile, "shader.vert", "r");
		if (!vertexShaderFile)
			return false;

		FILE * fragmentShaderFile = NULL;
		fopen_s(&fragmentShaderFile, "shader.frag", "r");
		if (!fragmentShaderFile)
			return false;

		shaderProgram = glCreateProgram();
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		long vertexShaderFileSize, fragmentShaderFileSize;

		fseek(vertexShaderFile, 0, SEEK_END);
		vertexShaderFileSize = (long)ftell(vertexShaderFile);
		rewind(vertexShaderFile);

		fseek(fragmentShaderFile, 0, SEEK_END);
		fragmentShaderFileSize = (long)ftell(fragmentShaderFile);
		rewind(fragmentShaderFile);

		char* vertexBuffer = new char[vertexShaderFileSize + 1];
		char* fragmentBuffer = new char[fragmentShaderFileSize + 1];

		for (int i = 0; i < vertexShaderFileSize; i++)
		{
			vertexBuffer[i] = ' ';
		}

		for (int j = 0; j < fragmentShaderFileSize; j++)
		{
			fragmentBuffer[j] = ' ';
		}
		vertexBuffer[vertexShaderFileSize] = '\0';
		fragmentBuffer[fragmentShaderFileSize] = '\0';

		fread(vertexBuffer, sizeof(char), vertexShaderFileSize, vertexShaderFile);
		fread(fragmentBuffer, sizeof(char), fragmentShaderFileSize, fragmentShaderFile);

		glShaderSource(vertexShader, 1, (const GLchar* const*)&vertexBuffer, NULL);
		glCompileShader(vertexShader);

		if (!GLCheckShader(vertexShader))
			return false;

		glShaderSource(fragmentShader, 1, (const GLchar* const*)&fragmentBuffer, NULL);
		glCompileShader(fragmentShader);

		if (!GLCheckShader(fragmentShader))
			return false;

		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);

		glBindAttribLocation(shaderProgram, VERT_OFFSET, "vertex");

		glLinkProgram(shaderProgram);

		if (!GLCheckProgram(shaderProgram))
			return false;

		glUseProgram(shaderProgram);

		ColorLocation = glGetUniformLocation(shaderProgram, "color");

		delete[] vertexBuffer;
		delete[] fragmentBuffer;

		fclose(vertexShaderFile);
		fclose(fragmentShaderFile);

		return true;
	}

	bool OpenGL::GLCheckProgram(GLuint& shaderProgram)
	{
		glValidateProgram(shaderProgram);

		GLint status;

		glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &status);
		if (status != GL_TRUE)
		{
			glDeleteProgram(shaderProgram);
			perror("Shader program not validate!");
			return false;
		}
		return true;
	}

	bool OpenGL::GLCheckShader(GLuint& shader)
	{
		GLint status, length;
		GLchar buffer[1024];

		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
		if (status != GL_TRUE)
		{
			glGetShaderInfoLog(shader, 1024, &length, buffer);
			glDeleteShader(shader);
			perror("Shader not validate!");
			return false;
		}
		return true;
	}

	void OpenGL::GLRenderStart()
	{
		glUseProgram(shaderProgram);
		glClearColor(0.05f, 0.12f, 0.22f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGL::GLRenderEnd()
	{
		SwapBuffers(hDC);
	}

	void OpenGL::GLClear()
	{
		glUseProgram(0);

		glDeleteProgram(shaderProgram);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void OpenGL::GLClose()
	{
		if (hRC != NULL)
		{
			wglMakeCurrent(NULL, NULL);
			wglDeleteContext(hRC);
			hRC = NULL;
		}
		if (hDC != NULL)
		{
			ReleaseDC(hWnd, hDC);
		}
	}

	

	int OpenGL::GetRand(int seed)
	{
		return rand() % seed;
	}
}