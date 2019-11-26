#include "Render.h"

namespace Task
{
	Render::Render()
	{
	}

	Render::Render(float* color)
	{
		DEBUG_ASSERT(sizeof(color) < (sizeof(float) * 3),
							L"Assert: Color data is out of range");
		SetColor(color[0], color[1], color[2]);
	}

	void Render::SetColor(float* color)
	{
		DEBUG_ASSERT(sizeof(color) < (sizeof(float) * 3), 
							L"Assert: Color data is out of range");
		SetColor(color[0], color[1], color[2]);
	}

	void Render::SetColor(float r, float g, float b)
	{
		color[0] = r;
		color[1] = g;
		color[2] = b;
	}

	void Render::Load() 
	{
		VAOLoad();
	}

	void Render::VAOLoad()
	{
		for (int i = 0, j = 0; i < RENDER_LINE_LENGTH; i++, j++)
		{
			vertex[i].x = -1.05f + (j * (4.2f / RENDER_LINE_LENGTH));
			vertex[i].y = RENDER_DEFAULT_Y;
			vertex[i].z = 0.0f;
			if (i > 0 && i % 2 == 1)
				j--;
		}

		openGL.glGenVertexArrays(1, &VAO);

		openGL.glBindVertexArray(VAO);

		openGL.glGenBuffers(1, &VBO);

		openGL.glBindBuffer(GL_ARRAY_BUFFER, VBO);
		openGL.glBufferData(GL_ARRAY_BUFFER, RENDER_LINE_LENGTH * 3 * sizeof(GLfloat), vertex, GL_STATIC_DRAW);
		openGL.glVertexAttribPointer(VERT_OFFSET, 3, GL_FLOAT, GL_FALSE, 0, 0);
		openGL.glEnableVertexAttribArray(VERT_OFFSET);

		openGL.glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Render::Update(std::shared_ptr<float> arrData, int* count)
	{
		DEBUG_ASSERT(arrData != nullptr, L"Assert: Render data is null");
		DEBUG_ASSERT(count != nullptr, L"Assert: Count of render data is null");

		if (arrData == nullptr || count == nullptr)
			return;

		for (int i = 0; i < RENDER_LINE_LENGTH; i++)
		{
			float value = 0.0f;
			if (i < *count) {
				value = arrData.get()[i];
			}
			temperatures[i] = (value * 1.8f) + RENDER_DEFAULT_Y;
		}
	}

	void Render::Update(float yLevel)
	{
		for (int i = 0; i < RENDER_LINE_LENGTH; i++)
		{
			temperatures[i] = (yLevel * 1.8f) + RENDER_DEFAULT_Y;
		}
	}

	void Render::VAOUpdate()
	{
		for (int i = 0, j = 0; i < RENDER_LINE_LENGTH; i++, j++)
		{
			vertex[i].y = temperatures[j];
			if (i > 0 && i % 2 == 1)
				j--;
		}

		openGL.glBindVertexArray(VAO);

		openGL.glBindBuffer(GL_ARRAY_BUFFER, VBO);
		openGL.glBufferData(GL_ARRAY_BUFFER, RENDER_LINE_LENGTH * 3 * sizeof(GLfloat), vertex, GL_STATIC_DRAW);
		openGL.glVertexAttribPointer(VERT_OFFSET, 3, GL_FLOAT, GL_FALSE, 0, 0);
		openGL.glEnableVertexAttribArray(VERT_OFFSET);

		openGL.glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Render::Draw()
	{
		openGL.glBindVertexArray(VAO);
		openGL.glUniform3f(openGL.ColorLocation, color[0], color[1], color[2]);
		glDrawArrays(GL_LINES, 0, RENDER_LINE_LENGTH * 2);
	}

	void Render::Clear()
	{
		//Deleting VBO
		openGL.glBindBuffer(GL_ARRAY_BUFFER, 0);
		openGL.glDeleteBuffers(1, &VBO);

		//Deleting VAO
		openGL.glBindVertexArray(0);
		openGL.glDeleteVertexArrays(1, &VAO);
	}
}