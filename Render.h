#define _CRT_SECURE_NO_WARNINGS

#ifndef RENDER_H
#define RENDER_H

#include "OpenGL.h"

using namespace OGL;

#define RENDER_LINE_LENGTH 200
#define RENDER_DEFAULT_Y -0.98f

#include "Debug.h"
using namespace Debug;

namespace Task
{
	class Render
	{
	private:
		float temperatures[RENDER_LINE_LENGTH] = { RENDER_DEFAULT_Y };
		glm::vec3 vertex[RENDER_LINE_LENGTH];
		float color[3] = { 0.0f, 1.0f, 0.0f };

		void VAOLoad();

	public:

		GLuint VAO, VBO;
		void Load();
		/*void Update(float** arrData, int* count);*/
		void Update(std::shared_ptr<float> arrData, int* count);
		void Update(float yLevel);
		void VAOUpdate();
		void Draw();
		void Clear();
		Render();
		Render(float* color);

		void SetColor(float r, float g, float b);
		void SetColor(float* color);
	};
}

#endif
