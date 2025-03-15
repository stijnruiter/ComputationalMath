#include <iostream>
#include <LinearAlgebra/VectorBase.h>
#include <LinearAlgebra/Matrix.h>

#include <LinearAlgebra/FactorizationLU.h>

#include <Render/Window.hpp>
#include <Render/Core/Renderer.hpp>

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    Matrix<float> mat(3, 3, new float[9]{
        1,2,3,
        3,2,1,
        2,1,3
    });
    ColumnVector<float> rhs(3, new float[3]{1, 2,2});

    LinearAlgebra::Factorization::FactorizationResult<float> factorization = LinearAlgebra::Factorization::PluFactorization(mat, 1e-5f);

    std::cout << "A = PLU = " << mat << std::endl;
    std::cout << "U = " << LinearAlgebra::Factorization::ExtractUpperMatrix(factorization.Factorization) << std::endl;
    std::cout << "L = " << LinearAlgebra::Factorization::ExtractLowerMatrix(factorization.Factorization) << std::endl;
    std::cout << "Determinant: " << LinearAlgebra::Factorization::Determinant(factorization) << std::endl;
    ColumnVector<float> result = LinearAlgebra::Factorization::LUSolve(mat, rhs, 1e-5f);
    std::cout << std::endl << "b = " << rhs << std::endl; 
    std::cout << "A\\b = " << result << std::endl;
	Window window(800, 600, "Physics");
    window.SetMouseCursor(true);
	{// local scope for GL destructors before the context is deleted
        Renderer renderer;
        renderer.SetClearColor(0.5f, 0.5f, 0.5f);

        double deltaTime = 0.0;
        double lastFrame = 0.0;
        while (!window.ShouldClose())
        {
            double currentFrame = glfwGetTime();
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            if (window.IsKeyPressed(GLFW_KEY_ESCAPE))
            {
                window.Close();
                return 0;
            }
            renderer.Clear();
            window.SwapBuffers();
            glfwPollEvents();
        }
    }

	return 0;
}