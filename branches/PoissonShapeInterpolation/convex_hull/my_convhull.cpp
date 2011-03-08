#include "my_convhull.h"
#include <vcg/complex/trimesh/append.h>

My_ConvHull::My_ConvHull()
{
    /// Insert here your code
}

My_ConvHull::~My_ConvHull()
{
    /// Insert here your code
}

void My_ConvHull::apply()
{
    //The convex hull
    CGMesh conv_hull;

    conv_hull.Clear();

    /// Insert here your code

    //Add the processed convex hull to the original mesh
    vcg::tri::Append<CGMesh, CGMesh>::Mesh(*(mesh), conv_hull);
}
