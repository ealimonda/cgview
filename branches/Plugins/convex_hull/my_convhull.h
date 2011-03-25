#ifndef MY_CONVHULL_H
#define MY_CONVHULL_H

#include "mesh_definition.h"

/// Insert here your code

class My_ConvHull
{
public:
    //Constructor
    My_ConvHull();

    //Deconstructor
    ~My_ConvHull();

    //Sets the mesh
    inline void setMesh(CGMesh* m)
    {
        mesh = m;
    }

    //Process the filter
    void apply();

    /// Insert here your code

private:
    /// Insert here your code

protected:
    CGMesh* mesh;

    /// Insert here your code
};

#endif // MY_CONVHULL_H
