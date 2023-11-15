#pragma once

#include "colors.h"
#include "components/simple_scene.h"
#include "star.h"
#include "regpoly.h"
#include "diamondGun.h"
#include "board.h"
#include "guns.h"
#include "playerState.h"
#include "transform2d.h"
#include "enemies.h"
#include "mouseEvent.h"
#include "service.h"
#include "responsiveViewport.h"

namespace m1
{
    class GeomWarGame : public gfxc::SimpleScene
    {
    public:
        GeomWarGame();
        ~GeomWarGame();

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

    protected:
        game::Board* board;
        game::Guns* guns;
        game::PlayerState* playerState;
        game::Enemies* enemies;
        game::MouseEvent* mouseEvent;
        game::ResizableViewport* resizableViewport;
    };

}
