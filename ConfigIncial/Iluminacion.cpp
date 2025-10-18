//Alejandro Martínez Jiménez
//practica 8
//17-Octubre-2025
//319130865
//
// Std. Includes
#include <string>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GL includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other Libs
#include "SOIL2/SOIL2.h"
#include "stb_image.h"
// Properties
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Function prototypes
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void DoMovement();


// Camera
Camera camera(glm::vec3(0.0f, 0.0f, 0.0f));
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;


// Light attributes
glm::vec3 sunPos(0.0f);
glm::vec3 moonPos(0.0f);
float manualTimeOffset = 0.0f; // Para controlar con teclas 'O' y 'L'
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;
float rot = 0.0f;
bool activanim = false;

int main()
{
    // Init GLFW
    glfwInit();
    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Materiales e Iluminacion Practica 8         Alejandro Martinez Jimenez", nullptr, nullptr);

    if (nullptr == window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();

        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);

    glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

    // Set the required callback functions
    glfwSetKeyCallback(window, KeyCallback);
    glfwSetCursorPosCallback(window, MouseCallback);

    // GLFW Options
    //glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_DISABLED );

    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    if (GLEW_OK != glewInit())
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }

    // Define the viewport dimensions
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    // OpenGL options
    glEnable(GL_DEPTH_TEST);

    // Setup and compile our shaders
    Shader lampshader("Shader/lamp.vs", "Shader/lamp.frag");
    Shader lightingShader("Shader/lighting.vs", "Shader/lighting.frag");



    // Load models
    Model red_dog((char*)"Models/RedDog.obj");
    glm::mat4 projection = glm::perspective(camera.GetZoom(), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);

    Model table((char*)"Models/old_stool.obj");

    Model sofa((char*)"Models/ModernSofa.obj");


    Model mesa((char*)"Models/oak_sideboard.obj");

    Model maceta((char*)"Models/Ceramic_pot_model.obj");

    Model macetados((char*)"Models/Indoor_plant_.obj");

    float vertices[] = {
      -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };

    // First, set the container's VAO (and VBO)
    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Load textures


// Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Set frame time
        GLfloat currentFrame = (float)glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Check and call events
        glfwPollEvents();
        DoMovement();


        // --- 1. ACTUALIZAR POSICIONES DE LUZ (CICLO DÍA/NOCHE) ---
        // Calculamos el "tiempo efectivo" usando SOLAMENTE el ajuste manual
        float effectiveTime = manualTimeOffset;

        float orbitSpeed = 0.3f; // Velocidad de la órbita
        float orbitRadius = 10.0f; // Qué tan lejos giran las luces

        // El Sol hará un círculo vertical en el plano X-Y
        sunPos.x = cos(effectiveTime * orbitSpeed) * orbitRadius;
        sunPos.y = sin(effectiveTime * orbitSpeed) * orbitRadius;
        sunPos.z = 5.0f;

        // La Luna estará en el lado opuesto exacto del círculo
        moonPos.x = cos(effectiveTime * orbitSpeed + 3.14159f) * orbitRadius;
        moonPos.y = sin(effectiveTime * orbitSpeed + 3.14159f) * orbitRadius;
        moonPos.z = 5.0f;


        // --- 2. CONFIGURAR ILUMINACIÓN Y FONDO (DÍA/NOCHE) ---

        // 'sunFactor' irá de 0.0 (noche) a 1.0 (día)
        float sunFactor = (sunPos.y + orbitRadius) / (2.0f * orbitRadius);
        sunFactor = glm::smoothstep(0.4f, 0.6f, sunFactor);

        // 2a. Color del cielo (fondo) dinámico
        glm::vec3 skyColorDay(0.5f, 0.7f, 0.9f); // Azul claro
        glm::vec3 skyColorNight(0.0f, 0.0f, 0.1f); // Azul oscuro
        glm::vec3 currentSkyColor = glm::mix(skyColorNight, skyColorDay, sunFactor);
        glClearColor(currentSkyColor.r, currentSkyColor.g, currentSkyColor.b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpiar con el nuevo color

        // 2b. Propiedades de las luces (intensidad basada en el ciclo)
        glm::vec3 sunAmbient, sunDiffuse, sunSpecular;
        glm::vec3 moonAmbient, moonDiffuse, moonSpecular;

        // El Sol es fuerte de día (sunFactor=1) y nulo de noche (sunFactor=0)
        sunAmbient = glm::vec3(0.3f, 0.3f, 0.3f) * sunFactor;  // Luz ambiental de día
        sunDiffuse = glm::vec3(1.0f, 1.0f, 0.9f) * sunFactor;  // Luz de sol amarilla/blanca
        sunSpecular = glm::vec3(1.0f, 1.0f, 1.0f) * sunFactor; // Brillo blanco

        // La Luna es lo opuesto: fuerte de noche (sunFactor=0) y nula de día
        float moonFactor = 1.0f - sunFactor;
        moonAmbient = glm::vec3(0.05f, 0.05f, 0.15f) * moonFactor; // Luz ambiental azulada de noche
        moonDiffuse = glm::vec3(0.2f, 0.2f, 0.3f) * moonFactor;   // Luz de luna azulada
        moonSpecular = glm::vec3(0.1f, 0.1f, 0.1f) * moonFactor;  // Brillo tenue


        // --- 3. DIBUJAR TODOS LOS MODELOS ILUMINADOS ---
        lightingShader.Use();

        // Enviar posición de la cámara
        glUniform3f(glGetUniformLocation(lightingShader.Program, "viewPos"), camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);

        // Enviar propiedad de material (brillo). El shader nuevo la necesita.
        glUniform1f(glGetUniformLocation(lightingShader.Program, "material_shininess"), 32.0f);

        // --- Enviar datos del SOL (Luz 1) ---
        glUniform3f(glGetUniformLocation(lightingShader.Program, "sun.position"), sunPos.x, sunPos.y, sunPos.z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "sun.ambient"), sunAmbient.r, sunAmbient.g, sunAmbient.b);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "sun.diffuse"), sunDiffuse.r, sunDiffuse.g, sunDiffuse.b);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "sun.specular"), sunSpecular.r, sunSpecular.g, sunSpecular.b);

        // --- Enviar datos de la LUNA (Luz 2) ---
        glUniform3f(glGetUniformLocation(lightingShader.Program, "moon.position"), moonPos.x, moonPos.y, moonPos.z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "moon.ambient"), moonAmbient.r, moonAmbient.g, moonAmbient.b);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "moon.diffuse"), moonDiffuse.r, moonDiffuse.g, moonDiffuse.b);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "moon.specular"), moonSpecular.r, moonSpecular.g, moonSpecular.b);

        // --- Matrices de Vista y Proyección ---
        glm::mat4 view = camera.GetViewMatrix();
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));


        // --- Draw Red Dog ---
        glm::mat4 model(1);
        model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        red_dog.Draw(lightingShader);

        // --- table ---
        glm::mat4 modeltable = glm::mat4(1.0f);
        modeltable = glm::translate(modeltable, glm::vec3(1.0f, 0.0f, 1.0f));
        modeltable = glm::scale(modeltable, glm::vec3(0.01f, 0.01f, 0.01f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modeltable));
        table.Draw(lightingShader);

        // --- Sofa ---
        glm::mat4 modelsofa = glm::mat4(1.0f);
        modelsofa = glm::translate(modelsofa, glm::vec3(0.5f, 0.0f, -3.0));
        modelsofa = glm::scale(modelsofa, glm::vec3(1.5f, 1.5f, 1.5f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelsofa));
        sofa.Draw(lightingShader);

        // --- mesa tv ---
        glm::mat4 modeltv = glm::mat4(1.0f);
        modeltv = glm::translate(modeltv, glm::vec3(0.0f, 0.0f, 4.0f));
        modeltv = glm::scale(modeltv, glm::vec3(1.6f, 1.6f, 1.6f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modeltv));
        mesa.Draw(lightingShader);

        // --- maceta ---
        glm::mat4 modelmaceta = glm::mat4(1.0f);
        modelmaceta = glm::translate(modelmaceta, glm::vec3(-2.0f, 0.0f, 2.6f));
        modelmaceta = glm::scale(modelmaceta, glm::vec3(4.0f, 4.0f, 4.0f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelmaceta));
        maceta.Draw(lightingShader);

        // --- maceta2 ---
        glm::mat4 modelmacetados = glm::mat4(1.0f);
        modelmacetados = glm::translate(modelmacetados, glm::vec3(4.0f, 0.0f, -4.0f));
        modelmacetados = glm::scale(modelmacetados, glm::vec3(0.5f, 0.5f, 0.5f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelmacetados));
        macetados.Draw(lightingShader);


        // --- 4. DIBUJAR LAS LÁMPARAS (CUBOS DEL SOL Y LA LUNA) ---
        lampshader.Use();
        glUniformMatrix4fv(glGetUniformLocation(lampshader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(lampshader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

        glBindVertexArray(VAO); // Vinculamos el VAO del cubo

        // Dibujar el Sol (un cubo grande)
        model = glm::mat4(1.0f);
        model = glm::translate(model, sunPos);
        model = glm::scale(model, glm::vec3(0.8f)); // Sol más grande
        glUniformMatrix4fv(glGetUniformLocation(lampshader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Dibujar la Luna (un cubo pequeño)
        model = glm::mat4(1.0f);
        model = glm::translate(model, moonPos);
        model = glm::scale(model, glm::vec3(0.5f)); // Luna más pequeña
        glUniformMatrix4fv(glGetUniformLocation(lampshader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glBindVertexArray(0);


        // Swap the buffers
        glfwSwapBuffers(window);
    }

    // --- ¡¡AGREGA ESTAS LÍNEAS AQUÍ!! ---
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
} // <--- ¡¡ESTA ES LA LLAVE QUE CIERRA 'main'!!

// --- AHORA SÍ PUEDE EMPEZAR DoMovement ---
// Moves/alters the camera positions based on user input

void DoMovement()
{
    // Camera controls
    if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
    {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
    {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
    {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
    {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }

    // --- Control del Ciclo Día/Noche ---
    float timeControlSpeed = 3.0f; // Ajusta esta velocidad si es necesario

    if (keys[GLFW_KEY_O])
    {
        // Adelanta el tiempo
        manualTimeOffset += timeControlSpeed * deltaTime;
    }

    if (keys[GLFW_KEY_L])
    {
        // Retrocede el tiempo
        manualTimeOffset -= timeControlSpeed * deltaTime;
    }

    // ... (tu código de 'activanim' si aún lo tienes) ...
}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
        {
            keys[key] = true;
        }
        else if (action == GLFW_RELEASE)
        {
            keys[key] = false;
        }
    }


}

void MouseCallback(GLFWwindow* window, double xPos, double yPos)
{
    if (firstMouse)
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }

    GLfloat xOffset = xPos - lastX;
    GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left

    lastX = xPos;
    lastY = yPos;

    camera.ProcessMouseMovement(xOffset, yOffset);
}


