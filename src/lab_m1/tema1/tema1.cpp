#include "lab_m1/tema1/tema1.h"

#include <vector>
#include <iostream>

using namespace std;
using namespace m1;
using namespace game;

GeomWarGame::GeomWarGame()
{
}

GeomWarGame::~GeomWarGame()
{
}

void GeomWarGame::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    resizableViewport = new ResizableViewport(window, this);
    mouseEvent = new MouseEvent();
    Service::getInstance()->mouseEvent = mouseEvent;
    playerState = new PlayerState(900, 600, 10, 120, resizableViewport, this);
    board = new Board(200, 100, 120, 50, 10, playerState, this);
    guns = new Guns(200, 600, 120, 10, board, resizableViewport, this);
    enemies = new Enemies(board, board->getLinesY(), this, playerState, resizableViewport);
}

void GeomWarGame::FrameStart()
{
    glm::vec3 color = ColorSingleton::getInstance()->getColor("background");
    glClearColor(color.x, color.y, color.z, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(
        resizableViewport->leftX,
        resizableViewport->leftY,
        resizableViewport->width,
        resizableViewport->height
    );
}


void GeomWarGame::Update(float deltaTimeSeconds)
{
    Service::getInstance()->deltaTime = deltaTimeSeconds;

    board->draw();
    guns->draw();
    guns->drawBullets();
    playerState->draw();
    enemies->generate(deltaTimeSeconds);
    playerState->generateHP();
    Service::getInstance()->emptyEnemyTrash();

    if (Service::getInstance()->dropped != NULL) {
        Service::getInstance()->dropped->draw();
    }
}


void GeomWarGame::FrameEnd()
{
}


void GeomWarGame::OnInputUpdate(float deltaTime, int mods)
{
}


void GeomWarGame::OnKeyPress(int key, int mods)
{
}


void GeomWarGame::OnKeyRelease(int key, int mods)
{

}


void GeomWarGame::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{    
    if (Service::getInstance()->dragged != NULL) {
        if (window->MouseHold(GLFW_MOUSE_BUTTON_1)) {
            glm::ivec2 mouseCoords = resizableViewport->getMouseCoords(mouseX, mouseY);

            if (Service::getInstance()->dropped == NULL) {
                Service::getInstance()->dropped = new Gun(
                    mouseCoords.x,
                    mouseCoords.y,
                    Service::getInstance()->dragged->cost,
                    Service::getInstance()->dragged->line,
                    Service::getInstance()->dragged->mesh,
                    Service::getInstance()->dragged->colorId,
                    guns,
                    board,
                    this
                );
            }
            else {
                Service::getInstance()->dropped->setPosition(mouseCoords.x, mouseCoords.y);
            }
        }
    }
}


void GeomWarGame::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    glm::ivec2 resolution = window->GetResolution();
    int swappedY = resolution.y - mouseY;

    if (mouseX >= resizableViewport->leftX &&
        mouseX <= resizableViewport->leftX + resizableViewport->width &&
        swappedY >= resizableViewport->leftY &&
        swappedY <= resizableViewport->leftY + resizableViewport->height) {
        glm::ivec2 mouseCoords = resizableViewport->getMouseCoords(mouseX, mouseY);
        mouseEvent->setEvent(
            mouseCoords.x,
            mouseCoords.y,
            button,
            0
        );
    }
}


void GeomWarGame::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    glm::ivec2 resolution = window->GetResolution();
    int swappedY = resolution.y - mouseY;

    if (mouseX >= resizableViewport->leftX &&
        mouseX <= resizableViewport->leftX + resizableViewport->width &&
        swappedY >= resizableViewport->leftY &&
        swappedY <= resizableViewport->leftY + resizableViewport->height) {
        std::cout << "hei";
        glm::ivec2 mouseCoords = resizableViewport->getMouseCoords(mouseX, mouseY);
        mouseEvent->setEvent(
            mouseCoords.x,
            mouseCoords.y,
            button,
            1
        );

        Service::getInstance()->dragged = NULL;
        delete Service::getInstance()->dropped;
        Service::getInstance()->dropped = NULL;
    }
}


void GeomWarGame::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void GeomWarGame::OnWindowResize(int width, int height)
{
    resizableViewport->update();
}