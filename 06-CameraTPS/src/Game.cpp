#include "Game.h"

Game::Game(unsigned int width, unsigned int height)
{
    this->width = width;
    this->height = height;
    this->state = GAME_ACTIVE;
    this->window = nullptr;

    // Inicializa el array de teclas
    for (bool &key : this->keys)
    {
        key = false;
    }

    lastFrame = 0.0f; // Tiempo inicial para calcular deltaTime
}

Game::~Game()
{
    cleanUp();
}

void Game::init()
{
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        exit(-1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(this->width, this->height, "Ventana OpenGL", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(-1);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        exit(-1);
    }

    glViewport(0, 0, this->width, this->height);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // Color de fondo

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    // Inicialización de los shaders
    shader.initialize("../Shaders/colorShader.vs", "../Shaders/colorShader.fs");
    shaderSkybox.initialize("../Shaders/skyBox.vs", "../Shaders/skyBox.fs");
    shaderMulLighting.initialize("../Shaders/iluminacion_textura_animation.vs", "../Shaders/multipleLights.fs");
    shaderTerrain.initialize("../Shaders/terrain.vs", "../Shaders/terrain.fs");


	skyboxSphere = Sphere(20, 20);
    // Inicializacion de los objetos
    skyboxSphere.init();
    skyboxSphere.setShader(&shaderSkybox);
    skyboxSphere.setScale(glm::vec3(20.0f, 20.0f, 20.0f));

    boxCesped.init();
    boxCesped.setShader(&shaderMulLighting);
}

void Game::cleanUp()
{
    if (window)
    {
        glfwDestroyWindow(window);
        window = nullptr;
    }
    glfwTerminate();
}

void Game::update(float dt)
{
    // Lógica de actualización de los objetos del juego
    // Ejemplo: actualizar posición de objetos, colisiones, IA
    // skyboxSphere.update(dt);
    // boxCesped.update(dt);
}

void Game::processInput(float dt)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        // Ejecutar acción para la tecla W, como mover adelante
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        // Ejecutar acción para la tecla S, como mover atrás
    }
    // Añadir más teclas según se necesite
}

void Game::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Renderizar objetos
    skyboxSphere.render();
    boxCesped.render();

    // Aquí puedes llamar al renderizado de más objetos si necesitas
}

void Game::run()
{
    this->init();

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        this->processInput(deltaTime);
        this->update(deltaTime);
        this->render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    this->cleanUp();
}
