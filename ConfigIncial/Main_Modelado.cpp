//Alejandro Martinez Jimenez
//Practica 4 
//05-Septiembre-2025
//31913085

#include <iostream>
//#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Shaders
#include "Shader.h"

void Inputs(GLFWwindow* window);

const GLint WIDTH = 800, HEIGHT = 600;
float movX = 0.0f;
float movY = 0.0f;
float movZ = -5.0f;
float rot = 0.0f;

// ==================== VERTICES ====================

// Cubo color rosado (cuerpo)
float verticesCuerpo[] = {
  -0.5f,-0.5f, 0.5f, 0.980f,0.678f,0.584f,
   0.5f,-0.5f, 0.5f, 0.980f,0.678f,0.584f,
   0.5f, 0.5f, 0.5f, 0.980f,0.678f,0.584f,
   0.5f, 0.5f, 0.5f, 0.980f,0.678f,0.584f,
  -0.5f, 0.5f, 0.5f, 0.980f,0.678f,0.584f,
  -0.5f,-0.5f, 0.5f, 0.980f,0.678f,0.584f,

  -0.5f,-0.5f,-0.5f, 0.980f,0.678f,0.584f,
   0.5f,-0.5f,-0.5f, 0.980f,0.678f,0.584f,
   0.5f, 0.5f,-0.5f, 0.980f,0.678f,0.584f,
   0.5f, 0.5f,-0.5f, 0.980f,0.678f,0.584f,
  -0.5f, 0.5f,-0.5f, 0.980f,0.678f,0.584f,
  -0.5f,-0.5f,-0.5f, 0.980f,0.678f,0.584f,

   0.5f,-0.5f, 0.5f, 0.980f,0.678f,0.584f,
   0.5f,-0.5f,-0.5f, 0.980f,0.678f,0.584f,
   0.5f, 0.5f,-0.5f, 0.980f,0.678f,0.584f,
   0.5f, 0.5f,-0.5f, 0.980f,0.678f,0.584f,
   0.5f, 0.5f, 0.5f, 0.980f,0.678f,0.584f,
   0.5f,-0.5f, 0.5f, 0.980f,0.678f,0.584f,

  -0.5f, 0.5f, 0.5f, 0.980f,0.678f,0.584f,
  -0.5f, 0.5f,-0.5f, 0.980f,0.678f,0.584f,
  -0.5f,-0.5f,-0.5f, 0.980f,0.678f,0.584f,
  -0.5f,-0.5f,-0.5f, 0.980f,0.678f,0.584f,
  -0.5f,-0.5f, 0.5f, 0.980f,0.678f,0.584f,
  -0.5f, 0.5f, 0.5f, 0.980f,0.678f,0.584f,

  -0.5f,-0.5f,-0.5f, 0.980f,0.678f,0.584f,
   0.5f,-0.5f,-0.5f, 0.980f,0.678f,0.584f,
   0.5f,-0.5f, 0.5f, 0.980f,0.678f,0.584f,
   0.5f,-0.5f, 0.5f, 0.980f,0.678f,0.584f,
  -0.5f,-0.5f, 0.5f, 0.980f,0.678f,0.584f,
  -0.5f,-0.5f,-0.5f, 0.980f,0.678f,0.584f,

  -0.5f, 0.5f,-0.5f, 0.980f,0.678f,0.584f,
   0.5f, 0.5f,-0.5f, 0.980f,0.678f,0.584f,
   0.5f, 0.5f, 0.5f, 0.980f,0.678f,0.584f,
   0.5f, 0.5f, 0.5f, 0.980f,0.678f,0.584f,
  -0.5f, 0.5f, 0.5f, 0.980f,0.678f,0.584f,
  -0.5f, 0.5f,-0.5f, 0.980f,0.678f,0.584f,
};

// Cubo color rojo (orejas)
float verticesOreja[] = {
  -0.5f,-0.5f, 0.5f, 0.980f,0.678f,0.584f,
   0.5f,-0.5f, 0.5f, 0.980f,0.678f,0.584f,
   0.5f, 0.5f, 0.5f, 0.980f,0.678f,0.584f,
   0.5f, 0.5f, 0.5f, 0.980f,0.678f,0.584f,
  -0.5f, 0.5f, 0.5f, 0.980f,0.678f,0.584f,
  -0.5f,-0.5f, 0.5f, 0.980f,0.678f,0.584f,

  -0.5f,-0.5f,-0.5f, 0.980f,0.678f,0.584f,
   0.5f,-0.5f,-0.5f, 0.980f,0.678f,0.584f,
   0.5f, 0.5f,-0.5f, 0.980f,0.678f,0.584f,
   0.5f, 0.5f,-0.5f, 0.980f,0.678f,0.584f,
  -0.5f, 0.5f,-0.5f, 0.980f,0.678f,0.584f,
  -0.5f,-0.5f,-0.5f, 0.980f,0.678f,0.584f,

   0.5f,-0.5f, 0.5f, 0.980f,0.678f,0.584f,
   0.5f,-0.5f,-0.5f, 0.980f,0.678f,0.584f,
   0.5f, 0.5f,-0.5f, 0.980f,0.678f,0.584f,
   0.5f, 0.5f,-0.5f, 0.980f,0.678f,0.584f,
   0.5f, 0.5f, 0.5f, 0.980f,0.678f,0.584f,
   0.5f,-0.5f, 0.5f, 0.980f,0.678f,0.584f,

  -0.5f, 0.5f, 0.5f, 0.980f,0.678f,0.584f,
  -0.5f, 0.5f,-0.5f, 0.980f,0.678f,0.584f,
  -0.5f,-0.5f,-0.5f, 0.980f,0.678f,0.584f,
  -0.5f,-0.5f,-0.5f, 0.980f,0.678f,0.584f,
  -0.5f,-0.5f, 0.5f, 0.980f,0.678f,0.584f,
  -0.5f, 0.5f, 0.5f, 0.980f,0.678f,0.584f,

  -0.5f,-0.5f,-0.5f, 0.980f,0.678f,0.584f,
   0.5f,-0.5f,-0.5f, 0.980f,0.678f,0.584f,
   0.5f,-0.5f, 0.5f, 0.980f,0.678f,0.584f,
   0.5f,-0.5f, 0.5f, 0.980f,0.678f,0.584f,
  -0.5f,-0.5f, 0.5f, 0.980f,0.678f,0.584f,
  -0.5f,-0.5f,-0.5f, 0.980f,0.678f,0.584f,

  -0.5f, 0.5f,-0.5f, 0.980f,0.678f,0.584f,
   0.5f, 0.5f,-0.5f, 0.980f,0.678f,0.584f,
   0.5f, 0.5f, 0.5f, 0.980f,0.678f,0.584f,
   0.5f, 0.5f, 0.5f, 0.980f,0.678f,0.584f,
  -0.5f, 0.5f, 0.5f, 0.980f,0.678f,0.584f,
  -0.5f, 0.5f,-0.5f, 0.980f,0.678f,0.584f,
};
// Cubo color marrOn (patas)
float verticesPata[] = {
  -0.5f,-0.5f, 0.5f, 0.4f,0.2f,0.1f,
   0.5f,-0.5f, 0.5f, 0.4f,0.2f,0.1f,
   0.5f, 0.5f, 0.5f, 0.4f,0.2f,0.1f,
   0.5f, 0.5f, 0.5f, 0.4f,0.2f,0.1f,
  -0.5f, 0.5f, 0.5f, 0.4f,0.2f,0.1f,
  -0.5f,-0.5f, 0.5f, 0.4f,0.2f,0.1f,

  -0.5f,-0.5f,-0.5f, 0.4f,0.2f,0.1f,
   0.5f,-0.5f,-0.5f, 0.4f,0.2f,0.1f,
   0.5f, 0.5f,-0.5f, 0.4f,0.2f,0.1f,
   0.5f, 0.5f,-0.5f, 0.4f,0.2f,0.1f,
  -0.5f, 0.5f,-0.5f, 0.4f,0.2f,0.1f,
  -0.5f,-0.5f,-0.5f, 0.4f,0.2f,0.1f,

   0.5f,-0.5f, 0.5f, 0.4f,0.2f,0.1f,
   0.5f,-0.5f,-0.5f, 0.4f,0.2f,0.1f,
   0.5f, 0.5f,-0.5f, 0.4f,0.2f,0.1f,
   0.5f, 0.5f,-0.5f, 0.4f,0.2f,0.1f,
   0.5f, 0.5f, 0.5f, 0.4f,0.2f,0.1f,
   0.5f,-0.5f, 0.5f, 0.4f,0.2f,0.1f,

  -0.5f, 0.5f, 0.5f, 0.4f,0.2f,0.1f,
  -0.5f, 0.5f,-0.5f, 0.4f,0.2f,0.1f,
  -0.5f,-0.5f,-0.5f, 0.4f,0.2f,0.1f,
  -0.5f,-0.5f,-0.5f, 0.4f,0.2f,0.1f,
  -0.5f,-0.5f, 0.5f, 0.4f,0.2f,0.1f,
  -0.5f, 0.5f, 0.5f, 0.4f,0.2f,0.1f,

  -0.5f,-0.5f,-0.5f, 0.4f,0.2f,0.1f,
   0.5f,-0.5f,-0.5f, 0.4f,0.2f,0.1f,
   0.5f,-0.5f, 0.5f, 0.4f,0.2f,0.1f,
   0.5f,-0.5f, 0.5f, 0.4f,0.2f,0.1f,
  -0.5f,-0.5f, 0.5f, 0.4f,0.2f,0.1f,
  -0.5f,-0.5f,-0.5f, 0.4f,0.2f,0.1f,

  -0.5f, 0.5f,-0.5f, 0.4f,0.2f,0.1f,
   0.5f, 0.5f,-0.5f, 0.4f,0.2f,0.1f,
   0.5f, 0.5f, 0.5f, 0.4f,0.2f,0.1f,
   0.5f, 0.5f, 0.5f, 0.4f,0.2f,0.1f,
  -0.5f, 0.5f, 0.5f, 0.4f,0.2f,0.1f,
  -0.5f, 0.5f,-0.5f, 0.4f,0.2f,0.1f,

};

// Cubo color negro (ojos)
float verticesOjo[] = {
  -0.5f,-0.5f, 0.5f, 0.992f, 0.988f, 0.992f,
   0.5f,-0.5f, 0.5f, 0.992f, 0.988f, 0.992f,
   0.5f, 0.5f, 0.5f, 0.992f, 0.988f, 0.992f,
   0.5f, 0.5f, 0.5f, 0.992f, 0.988f, 0.992f,
  -0.5f, 0.5f, 0.5f, 0.992f, 0.988f, 0.992f,
  -0.5f,-0.5f, 0.5f, 0.992f, 0.988f, 0.992f,

  -0.5f,-0.5f,-0.5f, 0.992f, 0.988f, 0.992f,
   0.5f,-0.5f,-0.5f, 0.992f, 0.988f, 0.992f,
   0.5f, 0.5f,-0.5f, 0.992f, 0.988f, 0.992f,
   0.5f, 0.5f,-0.5f, 0.992f, 0.988f, 0.992f,
  -0.5f, 0.5f,-0.5f, 0.992f, 0.988f, 0.992f,
  -0.5f,-0.5f,-0.5f, 0.992f, 0.988f, 0.992f,

   0.5f,-0.5f, 0.5f, 0.992f, 0.988f, 0.992f,
   0.5f,-0.5f,-0.5f, 0.992f, 0.988f, 0.992f,
   0.5f, 0.5f,-0.5f, 0.992f, 0.988f, 0.992f,
   0.5f, 0.5f,-0.5f, 0.992f, 0.988f, 0.992f,
   0.5f, 0.5f, 0.5f, 0.992f, 0.988f, 0.992f,
   0.5f,-0.5f, 0.5f, 0.992f, 0.988f, 0.992f,

  -0.5f, 0.5f, 0.5f, 0.992f, 0.988f, 0.992f,
  -0.5f, 0.5f,-0.5f, 0.992f, 0.988f, 0.992f,
  -0.5f,-0.5f,-0.5f, 0.992f, 0.988f, 0.992f,
  -0.5f,-0.5f,-0.5f, 0.992f, 0.988f, 0.992f,
  -0.5f,-0.5f, 0.5f, 0.992f, 0.988f, 0.992f,
  -0.5f, 0.5f, 0.5f, 0.992f, 0.988f, 0.992f,

  -0.5f,-0.5f,-0.5f, 0.992f, 0.988f, 0.992f,
   0.5f,-0.5f,-0.5f, 0.992f, 0.988f, 0.992f,
   0.5f,-0.5f, 0.5f, 0.992f, 0.988f, 0.992f,
   0.5f,-0.5f, 0.5f, 0.992f, 0.988f, 0.992f,
  -0.5f,-0.5f, 0.5f, 0.992f, 0.988f, 0.992f,
  -0.5f,-0.5f,-0.5f, 0.992f, 0.988f, 0.992f,

  -0.5f, 0.5f,-0.5f, 0.992f, 0.988f, 0.992f,
   0.5f, 0.5f,-0.5f, 0.992f, 0.988f, 0.992f,
   0.5f, 0.5f, 0.5f, 0.992f, 0.988f, 0.992f,
   0.5f, 0.5f, 0.5f, 0.992f, 0.988f, 0.992f,
  -0.5f, 0.5f, 0.5f, 0.992f, 0.988f, 0.992f,
  -0.5f, 0.5f,-0.5f, 0.992f, 0.988f, 0.992f,
};

float verticesnariz[] = {
  -0.5f,-0.5f, 0.5f, 0.969f, 0.741f, 0.612f,
   0.5f,-0.5f, 0.5f, 0.969f, 0.741f, 0.612f,
   0.5f, 0.5f, 0.5f, 0.969f, 0.741f, 0.612f,
   0.5f, 0.5f, 0.5f, 0.969f, 0.741f, 0.612f,
  -0.5f, 0.5f, 0.5f, 0.969f, 0.741f, 0.612f,
  -0.5f,-0.5f, 0.5f, 0.969f, 0.741f, 0.612f,

  -0.5f,-0.5f,-0.5f, 0.969f, 0.741f, 0.612f,
   0.5f,-0.5f,-0.5f, 0.969f, 0.741f, 0.612f,
   0.5f, 0.5f,-0.5f, 0.969f, 0.741f, 0.612f,
   0.5f, 0.5f,-0.5f, 0.969f, 0.741f, 0.612f,
  -0.5f, 0.5f,-0.5f, 0.969f, 0.741f, 0.612f,
  -0.5f,-0.5f,-0.5f, 0.969f, 0.741f, 0.612f,

   0.5f,-0.5f, 0.5f, 0.969f, 0.741f, 0.612f,
   0.5f,-0.5f,-0.5f, 0.969f, 0.741f, 0.612f,
   0.5f, 0.5f,-0.5f, 0.969f, 0.741f, 0.612f,
   0.5f, 0.5f,-0.5f, 0.969f, 0.741f, 0.612f,
   0.5f, 0.5f, 0.5f, 0.969f, 0.741f, 0.612f,
   0.5f,-0.5f, 0.5f, 0.969f, 0.741f, 0.612f,

  -0.5f, 0.5f, 0.5f, 0.969f, 0.741f, 0.612f,
  -0.5f, 0.5f,-0.5f, 0.969f, 0.741f, 0.612f,
  -0.5f,-0.5f,-0.5f, 0.969f, 0.741f, 0.612f,
  -0.5f,-0.5f,-0.5f, 0.969f, 0.741f, 0.612f,
  -0.5f,-0.5f, 0.5f, 0.969f, 0.741f, 0.612f,
  -0.5f, 0.5f, 0.5f, 0.969f, 0.741f, 0.612f,

  -0.5f,-0.5f,-0.5f, 0.969f, 0.741f, 0.612f,
   0.5f,-0.5f,-0.5f, 0.969f, 0.741f, 0.612f,
   0.5f,-0.5f, 0.5f, 0.969f, 0.741f, 0.612f,
   0.5f,-0.5f, 0.5f, 0.969f, 0.741f, 0.612f,
  -0.5f,-0.5f, 0.5f, 0.969f, 0.741f, 0.612f,
  -0.5f,-0.5f,-0.5f, 0.969f, 0.741f, 0.612f,

  -0.5f, 0.5f,-0.5f, 0.969f, 0.741f, 0.612f,
   0.5f, 0.5f,-0.5f, 0.969f, 0.741f, 0.612f,
   0.5f, 0.5f, 0.5f, 0.969f, 0.741f, 0.612f,
   0.5f, 0.5f, 0.5f, 0.969f, 0.741f, 0.612f,
  -0.5f, 0.5f, 0.5f, 0.969f, 0.741f, 0.612f,
  -0.5f, 0.5f,-0.5f, 0.969f, 0.741f, 0.612f,
};

float verticesLengua[] = {
  -0.5f,-0.5f, 0.5f, 0.898f,0.451f,0.451f,
   0.5f,-0.5f, 0.5f, 0.898f,0.451f,0.451f,
   0.5f, 0.5f, 0.5f, 0.898f,0.451f,0.451f,
   0.5f, 0.5f, 0.5f, 0.898f,0.451f,0.451f,
  -0.5f, 0.5f, 0.5f, 0.898f,0.451f,0.451f,
  -0.5f,-0.5f, 0.5f, 0.898f,0.451f,0.451f,

  -0.5f,-0.5f,-0.5f, 0.898f,0.451f,0.451f,
   0.5f,-0.5f,-0.5f, 0.898f,0.451f,0.451f,
   0.5f, 0.5f,-0.5f, 0.898f,0.451f,0.451f,
   0.5f, 0.5f,-0.5f, 0.898f,0.451f,0.451f,
  -0.5f, 0.5f,-0.5f, 0.898f,0.451f,0.451f,
  -0.5f,-0.5f,-0.5f, 0.898f,0.451f,0.451f,

   0.5f,-0.5f, 0.5f, 0.898f,0.451f,0.451f,
   0.5f,-0.5f,-0.5f, 0.898f,0.451f,0.451f,
   0.5f, 0.5f,-0.5f, 0.898f,0.451f,0.451f,
   0.5f, 0.5f,-0.5f, 0.898f,0.451f,0.451f,
   0.5f, 0.5f, 0.5f, 0.898f,0.451f,0.451f,
   0.5f,-0.5f, 0.5f, 0.898f,0.451f,0.451f,

  -0.5f, 0.5f, 0.5f, 0.898f,0.451f,0.451f,
  -0.5f, 0.5f,-0.5f, 0.898f,0.451f,0.451f,
  -0.5f,-0.5f,-0.5f, 0.898f,0.451f,0.451f,
  -0.5f,-0.5f,-0.5f, 0.898f,0.451f,0.451f,
  -0.5f,-0.5f, 0.5f, 0.898f,0.451f,0.451f,
  -0.5f, 0.5f, 0.5f, 0.898f,0.451f,0.451f,

  -0.5f,-0.5f,-0.5f, 0.898f,0.451f,0.451f,
   0.5f,-0.5f,-0.5f, 0.898f,0.451f,0.451f,
   0.5f,-0.5f, 0.5f, 0.898f,0.451f,0.451f,
   0.5f,-0.5f, 0.5f, 0.898f,0.451f,0.451f,
  -0.5f,-0.5f, 0.5f, 0.898f,0.451f,0.451f,
  -0.5f,-0.5f,-0.5f, 0.898f,0.451f,0.451f,

  -0.5f, 0.5f,-0.5f, 0.898f,0.451f,0.451f,
   0.5f, 0.5f,-0.5f, 0.898f,0.451f,0.451f,
   0.5f, 0.5f, 0.5f, 0.898f,0.451f,0.451f,
   0.5f, 0.5f, 0.5f, 0.898f,0.451f,0.451f,
  -0.5f, 0.5f, 0.5f, 0.898f,0.451f,0.451f,
  -0.5f, 0.5f,-0.5f, 0.898f,0.451f,0.451f,
};


float verticespupilas[] = {

  -0.5f,-0.5f, 0.5f, 0.502f,0.235f,0.188f,
   0.5f,-0.5f, 0.5f, 0.502f,0.235f,0.188f,
   0.5f, 0.5f, 0.5f, 0.502f,0.235f,0.188f,
   0.5f, 0.5f, 0.5f, 0.502f,0.235f,0.188f,
  -0.5f, 0.5f, 0.5f, 0.502f,0.235f,0.188f,
  -0.5f,-0.5f, 0.5f, 0.502f,0.235f,0.188f,


  -0.5f,-0.5f,-0.5f, 0.502f,0.235f,0.188f,
   0.5f,-0.5f,-0.5f, 0.502f,0.235f,0.188f,
   0.5f, 0.5f,-0.5f, 0.502f,0.235f,0.188f,
   0.5f, 0.5f,-0.5f, 0.502f,0.235f,0.188f,
  -0.5f, 0.5f,-0.5f, 0.502f,0.235f,0.188f,
  -0.5f,-0.5f,-0.5f, 0.502f,0.235f,0.188f,


   0.5f,-0.5f, 0.5f, 0.502f,0.235f,0.188f,
   0.5f,-0.5f,-0.5f, 0.502f,0.235f,0.188f,
   0.5f, 0.5f,-0.5f, 0.502f,0.235f,0.188f,
   0.5f, 0.5f,-0.5f, 0.502f,0.235f,0.188f,
   0.5f, 0.5f, 0.5f, 0.502f,0.235f,0.188f,
   0.5f,-0.5f, 0.5f, 0.502f,0.235f,0.188f,


   -0.5f, 0.5f, 0.5f, 0.502f,0.235f,0.188f,
   -0.5f, 0.5f,-0.5f, 0.502f,0.235f,0.188f,
   -0.5f,-0.5f,-0.5f, 0.502f,0.235f,0.188f,
   -0.5f,-0.5f,-0.5f, 0.502f,0.235f,0.188f,
   -0.5f,-0.5f, 0.5f, 0.502f,0.235f,0.188f,
   -0.5f, 0.5f, 0.5f, 0.502f,0.235f,0.188f,


   -0.5f,-0.5f,-0.5f, 0.502f,0.235f,0.188f,
   0.5f,-0.5f,-0.5f, 0.502f,0.235f,0.188f,
   0.5f,-0.5f, 0.5f, 0.502f,0.235f,0.188f,
   0.5f,-0.5f, 0.5f, 0.502f,0.235f,0.188f,
   -0.5f,-0.5f, 0.5f, 0.502f,0.235f,0.188f,
   -0.5f,-0.5f,-0.5f, 0.502f,0.235f,0.188f,


   -0.5f, 0.5f,-0.5f, 0.502f,0.235f,0.188f,
   0.5f, 0.5f,-0.5f, 0.502f,0.235f,0.188f,
   0.5f, 0.5f, 0.5f, 0.502f,0.235f,0.188f,
   0.5f, 0.5f, 0.5f, 0.502f,0.235f,0.188f,
   -0.5f, 0.5f, 0.5f, 0.502f,0.235f,0.188f,
   -0.5f, 0.5f,-0.5f, 0.502f,0.235f,0.188f,
};


float verticescolmillos[] = {
  -0.5f,-0.5f, 0.5f, 0.992f,0.988f,0.992f,
   0.5f,-0.5f, 0.5f, 0.992f,0.988f,0.992f,
   0.5f, 0.5f, 0.5f, 0.992f,0.988f,0.992f,
   0.5f, 0.5f, 0.5f, 0.992f,0.988f,0.992f,
  -0.5f, 0.5f, 0.5f, 0.992f,0.988f,0.992f,
  -0.5f,-0.5f, 0.5f, 0.992f,0.988f,0.992f,

  -0.5f,-0.5f,-0.5f, 0.992f,0.988f,0.992f,
   0.5f,-0.5f,-0.5f, 0.992f,0.988f,0.992f,
   0.5f, 0.5f,-0.5f, 0.992f,0.988f,0.992f,
   0.5f, 0.5f,-0.5f, 0.992f,0.988f,0.992f,
  -0.5f, 0.5f,-0.5f, 0.992f,0.988f,0.992f,
  -0.5f,-0.5f,-0.5f, 0.992f,0.988f,0.992f,

   0.5f,-0.5f, 0.5f, 0.992f,0.988f,0.992f,
   0.5f,-0.5f,-0.5f, 0.992f,0.988f,0.992f,
   0.5f, 0.5f,-0.5f, 0.992f,0.988f,0.992f,
   0.5f, 0.5f,-0.5f, 0.992f,0.988f,0.992f,
   0.5f, 0.5f, 0.5f, 0.992f,0.988f,0.992f,
   0.5f,-0.5f, 0.5f, 0.992f,0.988f,0.992f,

   -0.5f, 0.5f, 0.5f, 0.992f,0.988f,0.992f,
   -0.5f, 0.5f,-0.5f, 0.992f,0.988f,0.992f,
   -0.5f,-0.5f,-0.5f, 0.992f,0.988f,0.992f,
   -0.5f,-0.5f,-0.5f, 0.992f,0.988f,0.992f,
   -0.5f,-0.5f, 0.5f, 0.992f,0.988f,0.992f,
   -0.5f, 0.5f, 0.5f, 0.992f,0.988f,0.992f,

   -0.5f,-0.5f,-0.5f, 0.992f,0.988f,0.992f,
   0.5f,-0.5f,-0.5f, 0.992f,0.988f,0.992f,
   0.5f,-0.5f, 0.5f, 0.992f,0.988f,0.992f,
   0.5f,-0.5f, 0.5f, 0.992f,0.988f,0.992f,
   -0.5f,-0.5f, 0.5f, 0.992f,0.988f,0.992f,
   -0.5f,-0.5f,-0.5f, 0.992f,0.988f,0.992f,

   -0.5f, 0.5f,-0.5f, 0.992f,0.988f,0.992f,
   0.5f, 0.5f,-0.5f, 0.992f,0.988f,0.992f,
   0.5f, 0.5f, 0.5f, 0.992f,0.988f,0.992f,
   0.5f, 0.5f, 0.5f, 0.992f,0.988f,0.992f,
   -0.5f, 0.5f, 0.5f, 0.992f,0.988f,0.992f,
   -0.5f, 0.5f,-0.5f, 0.992f,0.988f,0.992f,
};






// ==================== MAIN ====================

int main() {
	glfwInit();
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Practica 4 Modelado geometrico - Colores", nullptr, nullptr);
	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	if (!window) { std::cout << "Error creando ventana GLFW\n"; return -1; }

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	if (GLEW_OK != glewInit()) { std::cout << "Error iniciando GLEW\n"; return -1; }

	glViewport(0, 0, screenWidth, screenHeight);
	glEnable(GL_DEPTH_TEST);

	Shader ourShader("Shader/core.vs", "Shader/core.frag");

	// ----- VAO Cuerpo -----
	GLuint VAO_Cuerpo, VBO_Cuerpo;
	glGenVertexArrays(1, &VAO_Cuerpo);
	glGenBuffers(1, &VBO_Cuerpo);
	glBindVertexArray(VAO_Cuerpo);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_Cuerpo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesCuerpo), verticesCuerpo, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);

	// ----- VAO Oreja -----
	GLuint VAO_Oreja, VBO_Oreja;
	glGenVertexArrays(1, &VAO_Oreja);
	glGenBuffers(1, &VBO_Oreja);
	glBindVertexArray(VAO_Oreja);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_Oreja);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesOreja), verticesOreja, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);

	// ----- VAO Pata -----
	GLuint VAO_Pata, VBO_Pata;
	glGenVertexArrays(1, &VAO_Pata);
	glGenBuffers(1, &VBO_Pata);
	glBindVertexArray(VAO_Pata);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_Pata);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesPata), verticesPata, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);

	// ----- VAO Ojo -----
	GLuint VAO_Ojo, VBO_Ojo;
	glGenVertexArrays(1, &VAO_Ojo);
	glGenBuffers(1, &VBO_Ojo);
	glBindVertexArray(VAO_Ojo);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_Ojo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesOjo), verticesOjo, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);


	// -------VAO NARIZ
	GLuint VAO_nariz, VBO_nariz;
	glGenVertexArrays(1, &VAO_nariz);
	glGenBuffers(1, &VBO_nariz);
	glBindVertexArray(VAO_nariz);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_nariz);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesnariz), verticesnariz, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);

	// ----- VAO Lengua -----
	GLuint VAO_Lengua, VBO_Lengua;
	glGenVertexArrays(1, &VAO_Lengua);
	glGenBuffers(1, &VBO_Lengua);
	glBindVertexArray(VAO_Lengua);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_Lengua);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesLengua), verticesLengua, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);

	// ----- VAO pupila -----
	GLuint VAO_pupila, VBO_pupila;
	glGenVertexArrays(1, &VAO_pupila);
	glGenBuffers(1, &VBO_pupila);
	glBindVertexArray(VAO_pupila);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_pupila);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticespupilas), verticespupilas, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);

	// ----- VAO colmillo -----
	GLuint VAO_colmillo, VBO_colmillo;
	glGenVertexArrays(1, &VAO_colmillo);
	glGenBuffers(1, &VBO_colmillo);
	glBindVertexArray(VAO_colmillo);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_colmillo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticescolmillos), verticescolmillos, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);


	// ----- PROYECCIÓN -----
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);

	while (!glfwWindowShouldClose(window)) {
		Inputs(window);
		glfwPollEvents();

		glClearColor(0.863f, 0.863f, 0.863f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ourShader.Use();

		glm::mat4 view = glm::mat4(1.0f);
		view = glm::translate(view, glm::vec3(movX, movY, movZ));
		view = glm::rotate(view, glm::radians(rot), glm::vec3(0, 1, 0));

		GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
		GLint projLoc = glGetUniformLocation(ourShader.Program, "projection");

		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		// ----- DIBUJAR CUERPO -----
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(2.0f, 1.3f, 1.4f));
		model = glm::translate(model, glm::vec3(0.0f, 0.46f, -1.22f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO_Cuerpo);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// ----- DIBUJAR OREJA 1 -----
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.18f, 0.32f, 0.38f));
		model = glm::translate(model, glm::vec3(-3.3f, 4.0f, -3.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO_Oreja);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// ----- DIBUJAR OREJA 2 -----
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.18f, 0.32f, 0.38f));
		model = glm::translate(model, glm::vec3(-3.3f, 4.0f, -5.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO_Oreja);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// ----- PATA DELANTERA IZQUIERDA -----
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.25f, 0.5f, 0.25f));
		model = glm::translate(model, glm::vec3(-2.0f, -0.5f, -8.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO_Pata);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// ----- PATA DELANTERA DERECHA -----
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.25f, 0.5f, 0.25f));
		model = glm::translate(model, glm::vec3(-2.0f, -0.5f, -5.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO_Pata);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// ----- PATA TRASERA IZQUIERDA -----
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.25f, 0.5f, 0.25f));
		model = glm::translate(model, glm::vec3(2.0f, -0.5f, -8.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO_Pata);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// ----- PATA TRASERA DERECHA -----
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.25f, 0.5f, 0.25f));
		model = glm::translate(model, glm::vec3(2.0f, -0.5f, -5.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO_Pata);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// ----- OJO IZQUIERDO -----
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.15f, 0.3f, 0.3f));
		model = glm::translate(model, glm::vec3(-7.0f, 2.8f, -7.3f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO_Ojo);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// ----- OJO DERECHO -----
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.15f, 0.3f, 0.3f));
		model = glm::translate(model, glm::vec3(-7.0f, 2.8f, -4.3f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO_Ojo);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// ----- NARIZ -----
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.25f, 0.3f, 0.6f));
		model = glm::translate(model, glm::vec3(-4.5f, 1.6f, -2.9f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO_nariz);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// ----- LENGUA -----
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.25f, 0.15f, 0.4f)); // más delgada
		model = glm::translate(model, glm::vec3(-4.5f, 1.5f, -4.4f)); // debajo de la nariz
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO_Lengua);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// ----- pupila iz -----
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.15f, 0.15f, 0.15f));
		model = glm::translate(model, glm::vec3(-7.5f, 5.8f, -14.6f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO_pupila);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// ----- pupila der -----
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.15f, 0.15f, 0.15f));
		model = glm::translate(model, glm::vec3(-7.5f, 5.8f, -8.4f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO_pupila);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// ----- Colmillo iz -----
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.15f, 0.15f, 0.15f));
		model = glm::translate(model, glm::vec3(-7.5f, 1.3f, -14.6f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO_colmillo);
		glDrawArrays(GL_TRIANGLES, 0, 36);


		// ----- Colmillo der -----
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.15f, 0.15f, 0.15f));
		model = glm::translate(model, glm::vec3(-7.5f, 1.3f, -8.4f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO_colmillo);
		glDrawArrays(GL_TRIANGLES, 0, 36);






		glBindVertexArray(0);
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO_Cuerpo);
	glDeleteBuffers(1, &VBO_Cuerpo);
	glDeleteVertexArrays(1, &VAO_Oreja);
	glDeleteBuffers(1, &VBO_Oreja);

	glfwTerminate();
	return 0;


}

// ==================== INPUTS ====================

void Inputs(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) movX += 0.12f;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) movX -= 0.12f;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) movY += 0.12f;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) movY -= 0.12f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) movZ -= 0.12f;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) movZ += 0.12f;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) rot += 0.8f;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) rot -= 0.8f;
}
