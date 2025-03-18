#include "Fem/HelmholtzEquationWithSource.hpp"
#include "Fem/LaplaceFem.hpp"
#include "FemScene.hpp"
#include "RefinedDelaunayCircle.h"
#include <Render/Window.hpp>

int main()
{
    Window window(800, 600, "Physics");
    window.SetMouseCursor(true);

    window.AddScene(CreateDelaunayScene());
    window.AddScene(CreateFemScene<HelmholtzEquationWithSourceFEM>(5));
    window.AddScene(CreateFemScene<LaplaceFem>());

    size_t sceneIndex = 0;
    window.SetCallbackOnKey([&sceneIndex, &window](const KeyEvent& eventArgs)
                            {
            if (eventArgs.Action == GLFW_PRESS && eventArgs.Key == GLFW_KEY_1)
            {
                sceneIndex = (sceneIndex + 1) % window.GetSceneCount();
                window.SwitchScene(sceneIndex);
            } });

    window.Run();

    return 0;
}