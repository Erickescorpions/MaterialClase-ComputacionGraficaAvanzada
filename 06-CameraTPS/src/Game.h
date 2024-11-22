#ifndef GAME
#define GAME

#include <GLFW/glfw3.h>
#include <iostream>
#include "Headers/Shader.h"
#include "Headers/Sphere.h"
#include "Headers/Box.h"

enum GameState {
  GAME_ACTIVE,
  GAME_MENU,
  GAME_WIN
};

class Game
{
public:
    GameState state;
    bool keys[1024];
    unsigned int width, height;
    GLFWwindow *window;
    float lastFrame;

    // Constructor
    Game(unsigned int width, unsigned int height);

    // Destructor
    ~Game();

    // Inicializar el juego
    void init();

    // Ciclo de juego
    void processInput(float dt);
    void update(float dt);
    void render();
    void run();

private:
    Shader shader;
    //Shader con skybox
    Shader shaderSkybox;
    //Shader con multiples luces
    Shader shaderMulLighting;
    //Shader para el terreno
    Shader shaderTerrain;
    Sphere skyboxSphere;
    Box boxCesped;

    // Función de limpieza
    void cleanUp();
};

#endif
