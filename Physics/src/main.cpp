#include "Fem/HeatEquationWithoutSource.hpp"
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
    window.AddScene(CreateCircularScene());
    window.AddScene(CreateFemScene<HelmholtzEquationWithSourceFEM>(1));
    window.AddScene(CreateFemScene<LaplaceFem>());
    window.AddScene(CreateTimeFemScene<HeatEquationWithoutSource>(0.05f, 1e-3f, [](Geometry::Vertex2F vertex)
                                                                  { return (vertex.Length() <= 0.25) ? 1.0f : 0.0f; }));

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