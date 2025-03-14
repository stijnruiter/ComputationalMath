#include "TestHelper.h"

bool TestHelper::TriangleElementCyclicalEqual(Geometry::TriangleElement element1, Geometry::TriangleElement element2)
{
    return (element1.I == element2.I && element1.J == element2.J && element1.K == element2.K) ||
            (element1.I == element2.J && element1.J == element2.K && element1.K == element2.I) ||
            (element1.I == element2.K && element1.J == element2.I && element1.K == element2.J);
}

bool TestHelper::LineElementCyclicalEqual(Geometry::LineElement element1, Geometry::LineElement element2)
{
    return (element1.I == element2.I && element1.J == element2.J) ||
        (element1.I == element2.J && element1.J == element2.I);
}

bool TestHelper::Vertex2FNearlyEqual(Geometry::Vertex2F vertex1, Geometry::Vertex2F vertex2)
{
    return (vertex1 - vertex2).LengthSquared() < 1e-9f;
}