// PlantillaOpenGL.cpp: define el punto de entrada de la aplicación de consola

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>

#define GLEW_STATIC

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>

using namespace std;
GLFWwindow * window;


double tiempoAnterior = 0.0;
double tiempoActual = 0.0;
double tiempoDiferencial = 0.0;



float xTriangulo = 0.0f;
float yTriangulo = 0.0f;
float velocidad = 0.3f;

void dibujarTriangulo() {

	//Utilizar matriz identidad
	glPushMatrix();
	//Transformaciones
	glTranslatef(xTriangulo, yTriangulo, 0.0f);

	//Dibujar vertices
	glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f(0.0f, 0.2f, 0.0f);
		glVertex3f(0.2f, -0.2f, 0.0f);
		glVertex3f(-0.2f, -0.2f, 0.0f);

		glEnd();

		//Soltar matriz
		glPopMatrix();
}

void moverTriangulo() {

	//Derecha
	int estadoTeclaDerecha = glfwGetKey(window, GLFW_KEY_RIGHT);

	if (estadoTeclaDerecha == GLFW_PRESS)
	{
		xTriangulo += velocidad * tiempoDiferencial;
	}

	//Izquierda
	int estadoTeclaIzquierda = glfwGetKey(window, GLFW_KEY_LEFT);

	if (estadoTeclaIzquierda == GLFW_PRESS)
	{
		xTriangulo -= velocidad * tiempoDiferencial;
	}

	//Arriba
	int estadoTeclaArriba = glfwGetKey(window, GLFW_KEY_UP);

	if (estadoTeclaArriba == GLFW_PRESS)
	{
		yTriangulo += velocidad * tiempoDiferencial;
	}


	//Abajo
	int estadoTeclaAbajo = glfwGetKey(window, GLFW_KEY_DOWN);

	if (estadoTeclaAbajo == GLFW_PRESS)
	{
		yTriangulo -= velocidad * tiempoDiferencial;
	}


}

void dibujar() {
	dibujarTriangulo();
}

void actualizar() {

	tiempoActual = glfwGetTime();

	tiempoDiferencial = tiempoActual - tiempoAnterior;

	moverTriangulo();

	tiempoAnterior = tiempoActual;


}



void teclado_callback(GLFWwindow * window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS || action == GLFW_REPEAT)
	{
		xTriangulo += velocidad;
	}
	else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS || action == GLFW_REPEAT)
	{
		xTriangulo -= velocidad;
	}
	else if (key == GLFW_KEY_UP && action == GLFW_PRESS || action == GLFW_REPEAT)
	{
		yTriangulo += velocidad;
	}
	else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS || action == GLFW_REPEAT)
	{
		yTriangulo -= velocidad;
	}
}

int main()
{
	

	//Si no se pudo iniciar glfw
	//entonces inicializamos en la ventana
	if (!glfwInit())
		exit(EXIT_FAILURE);

	//Si se pudo iniciar GLFW
	//entonces inicializamos la ventana
	window = glfwCreateWindow(1024, 768, "Ventana", NULL, NULL);

	//Si no podemos iniciar la ventana
	//Entonces terminamos la ejecucion

	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//Establecemos el contexto
	glfwMakeContextCurrent(window);

	//Una vez establecido el contexto activamos funciones modernas (gpu / cpu)
	glewExperimental = true;
	GLenum errorGlew = glewInit();
	if (errorGlew != GLEW_OK) {
		cout << glewGetErrorString(errorGlew);
	}

	const GLubyte *versionGL = glGetString(GL_VERSION);
	cout << "Version OpenGL: " << versionGL;

	//glfwSetKeyCallback(window, teclado_callback);

	tiempoAnterior = glfwGetTime();

	//Ciclo de dibujo (Draw Loop)
	while (!glfwWindowShouldClose(window)) {
		//Establecer region del dibujo
		glViewport(0, 0, 1024, 768);
		//Establecer el color del borrado
		glClearColor(0.9, 0.2, 0.2, 1);
		//Borramos
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Rutina de dibujo
		actualizar();
		dibujar();
		

		//Cambiar Buffers
		glfwSwapBuffers(window);
		//Reconocer si hay entradas
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
    return 0;
}

