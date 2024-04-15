#include <GL/glew.h>
#include <GLFW/glfw3.h>
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "glfw3.lib")
#pragma warning(disable: 4711 4710 4100)

#include "./common.c"

const unsigned int WIN_W = 300;
const unsigned int WIN_H = 300;
const unsigned int WIN_X = 100;
const unsigned int WIN_Y = 100;

const char* vertFileName = "22-colored-tri.vert";
const char* fragFileName = "22-colored-tri.frag";

GLuint vert = 0;
GLuint frag = 0;
GLuint prog = 0;

void initFunc(void)
{
	const char* vertSource = loadFile(vertFileName);
	const char* fragSource = loadFile(fragFileName);

	vert = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vert, 1, &vertSource, NULL);
	glCompileShader(vert);

	frag = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(frag, 1, &fragSource, NULL);
	glCompileShader(frag);

	// prog: program
	prog = glCreateProgram();
	glAttachShader(prog, vert);
	glAttachShader(prog, frag);
	glLinkProgram(prog); // link to get .EXE
	// execute it!
	glUseProgram(prog);
	// done
	free((void*)vertSource);
	free((void*)fragSource);
}

GLfloat vertPos[] = {
	-0.5F, -0.5F, 0.0F, 1.0F,
	+0.5F, -0.5F, 0.0F, 1.0F,
	-0.5F, +0.5F, 0.0F, 1.0F,
};

GLfloat vertColor[] = {
	1.0F, 0.0F, 0.0F, 1.0F, // red
	0.0F, 1.0F, 0.0F, 1.0F, // green
	0.0F, 0.0F, 1.0F, 1.0F, // blue
};

void drawFunc(void)
{
	// clear in gray color
	glClear(GL_COLOR_BUFFER_BIT);
	// provide the vertex attributes
	GLuint loc = glGetAttribLocation(prog, "aPos");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 0, vertPos);
	// provide the color attributes
	loc = glGetAttribLocation(prog, "aColor");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 0, vertColor);
	// draw a triangle
	glDrawArrays(GL_TRIANGLES, 0, 3);
	// done
	glFinish();
}

void refreshFunc(GLFWwindow* window) {
	drawFunc();

	glfwSwapBuffers(window);
}
void keyFunc(GLFWwindow* window, int key, int scancode, int action, int mods) {
	switch (key) {
	case GLFW_KEY_ESCAPE:
		if (action == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
		break;
	}
}
int main(int argc, char* argv[])
{
	const char* basename = getBaseName(argv[0]);

	glfwInit();
	GLFWwindow* window = glfwCreateWindow(WIN_W, WIN_H, basename, NULL, NULL);
	glfwSetWindowPos(window, WIN_X, WIN_Y);
	glfwMakeContextCurrent(window);

	glewInit();
	glfwSetWindowRefreshCallback(window, refreshFunc);
	glfwSetKeyCallback(window, keyFunc);
	glClearColor(0.3F, 0.3F, 0.3F, 1.0F);

	initFunc();
	while (! glfwWindowShouldClose(window))
	{
		drawFunc();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// done
	glfwTerminate();
	return 0;
}