// PlantillaOpenGL.cpp: define el punto de entrada de la aplicación de consola

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>

#define GLEW_STATIC

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>
#include <time.h>

using namespace std;

float xCuadrado = -0.7f;
float yCuadrado = -0.8f;

float xTriangulo = 0.0f;
float yTriangulo = 0.0f;

float velocidad = 0.3f;

double tiempoAnterior = 0.0;
double tiempoActual = 0.0;
double tiempoDiferencial = 0.0;

float rTriangulo = 1.0f;
float gTriangulo = 1.0f;
float bTriangulo = 1.0f;


GLFWwindow * window;



void dibujarTriangulo() {

	//Utilizar matriz identidad
	glPushMatrix();
	//Transformaciones
	glTranslatef(xTriangulo, yTriangulo, 0.0f);

	//Dibujar vertices
	glBegin(GL_TRIANGLES);
	glColor3f(rTriangulo, gTriangulo, bTriangulo);
	glVertex3f(0.0f, 0.2f, 0.0f);
	glVertex3f(0.2f, -0.2f, 0.0f);
	glVertex3f(-0.2f, -0.2f, 0.0f);

	glEnd();

	//Soltar matriz
	glPopMatrix();
}

void dibujarCuadrado() {
	glPushMatrix();

		//Transformaciones
		glTranslatef(xCuadrado, yCuadrado, 0);

		glBegin(GL_QUADS);
			glColor3f(1.0f, 0.4f, 0.5f);
			glVertex3f(-0.1f, 0.1f, 0.0f);
			glVertex3f(0.1f, 0.1f, 0.0f);
			glVertex3f(0.1f, -0.1f, 0.0f);
			glVertex3f(-0.1f, -0.1f, 0.0f);
		glEnd();
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
	dibujarCuadrado();
}

void checarColisiones() {

	//Corroborar si el triangulo colisiona con el cuadrado
	if (xTriangulo - 0.2f < xCuadrado + 0.1f
		&&
		xTriangulo + 0.2f > xCuadrado - 0.f
		&&
		yTriangulo - 0.2f < yCuadrado + 0.1f
		&&
		yTriangulo + 0.2f > yCuadrado - 0.f) {

		gTriangulo = 0.0f;
		bTriangulo = 0.0f;
	
		xCuadrado = (rand() %2 ) - 1;
		yCuadrado = (rand() %2 ) - 1;

	}
	
	else
	{
	
		gTriangulo = 1.0f;
		bTriangulo = 1.0f;

	}
}


void actualizar() {

	tiempoActual = glfwGetTime();

	checarColisiones();

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

