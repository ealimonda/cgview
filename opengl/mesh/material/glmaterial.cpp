#include "glmaterial.h"

const float GLMaterial::PRESET[n_PRESET][17] =
{
    //NAME
    //
    //AMBIENT
    //DIFFUSE
    //SPECULAR
    //EMISSION
    //SHININESS (in the range 0.0f - 1.0f)

    //DEFAULT
    {
        0.2f, 0.2f, 0.2f, 1.0f,
        0.8f, 0.8f, 0.8f, 1.0f,
        0.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 0.0f, 1.0f,
        0.0f
    },

    //EMERALD
    {
        0.0215f, 0.1745f, 0.0215f, 0.55f,
        0.07568f, 0.61424f, 0.07568f, 0.55f,
        0.633f, 0.727811f, 0.633f, 0.55f,
        0.0f, 0.0f, 0.0f, 1.0f,
        0.6f
    },

    //JADE
    {
        0.135f, 0.2225f, 0.1575f, 0.95f,
        0.54f, 0.89f, 0.63f, 0.95f,
        0.316228f, 0.316228f, 0.316228f, 0.95f,
        0.0f, 0.0f, 0.0f, 1.0f,
        0.1f
    },

    //OBSIDIAN
    {
        0.05375f, 0.05f, 0.06625f, 0.82f,
        0.18275f, 0.17f, 0.22525f, 0.82f,
        0.332741f, 0.328634f, 0.346435f, 0.82f,
        0.0f, 0.0f, 0.0f, 1.0f,
        0.3f
    },

    //PEARL
    {
        0.25f, 0.20725f, 0.20725f, 0.922f,
        1.0f, 0.829f, 0.829f, 0.922f,
        0.296648f, 0.296648f, 0.296648f, 0.922f,
        0.0f, 0.0f, 0.0f, 1.0f,
        0.088f
    },

    //RUBY
    {
        0.1745f, 0.01175f, 0.01175f, 0.55f,
        0.61424f, 0.04136f, 0.04136f, 0.55f,
        0.727811f, 0.626959f, 0.626959f, 0.55f,
        0.0f, 0.0f, 0.0f, 1.0f,
        0.6f
    },

    //TURQUOISE
    {
        0.1f, 0.18725f, 0.1745f, 0.8f,
        0.396f, 0.74151f, 0.69102f, 0.8f,
        0.297254f, 0.30829f, 0.306678f, 0.8f,
        0.0f, 0.0f, 0.0f, 1.0f,
        0.1f
    },

    //BRASS
    {
        0.329412f, 0.223529f, 0.027451f, 1.0f,
        0.780392f, 0.568627f, 0.113725f, 1.0f,
        0.992157f, 0.941176f, 0.807843f, 1.0f,
        0.0f, 0.0f, 0.0f, 1.0f,
        0.2179484375f
    },

    //BRONZE
    {
        0.2125f, 0.1275f, 0.054f, 1.0f,
        0.714f, 0.4284f, 0.18144f, 1.0f,
        0.393548f, 0.271906f, 0.166721f, 1.0f,
        0.0f, 0.0f, 0.0f, 1.0f,
        0.2
    },

    //POLISHED BRONZE
    {
        0.25f, 0.148f, 0.06475f, 1.0f,
        0.4f, 0.2368f, 0.1036f, 1.0f,
        0.774597f, 0.458561f, 0.200621f, 1.0f,
        0.0f, 0.0f, 0.0f, 1.0f,
        0.6f
    },

    //CHROME
    {
        0.25f, 0.25f, 0.25f, 1.0f,
        0.4f, 0.4f, 0.4f, 1.0f,
        0.774597f, 0.774597f, 0.774597f, 1.0f,
        0.0f, 0.0f, 0.0f, 1.0f,
        0.6f
    },

    //COPPER
    {
        0.19125f, 0.0735f, 0.0225f, 1.0f,
        0.7038f, 0.27048f, 0.0828f, 1.0f,
        0.256777f, 0.137622f, 0.086014f, 1.0f,
        0.0f, 0.0f, 0.0f, 1.0f,
        0.1f
    },

    //POLISHED COPPER
    {
        0.2295f, 0.08825f, 0.0275f, 1.0f,
        0.5508f, 0.2118f, 0.066f, 1.0f,
        0.580594f, 0.223257f, 0.0695701f, 1.0f,
        0.0f, 0.0f, 0.0f, 1.0f,
        0.4f
    },

    //GOLD
    {
        0.24725f, 0.1995f, 0.0745f, 1.0f,
        0.75164f, 0.60648f, 0.22648f, 1.0f,
        0.628281f, 0.555802f, 0.366065f, 1.0f,
        0.0f, 0.0f, 0.0f, 1.0f,
        0.4f
    },

    //POLISHED GOLD
    {
        0.24725f, 0.2245f, 0.0645f, 1.0f,
        0.34615f, 0.3143f, 0.0903f, 1.0f,
        0.797357f, 0.723991f, 0.208006f, 1.0f,
        0.0f, 0.0f, 0.0f, 1.0f,
        0.65f
    },

    //SILVER
    {
        0.19225f, 0.19225f, 0.19225f, 1.0f,
        0.50754f, 0.50754f, 0.50754f, 1.0f,
        0.508273f, 0.508273f, 0.508273f, 1.0f,
        0.0f, 0.0f, 0.0f, 1.0f,
        0.4f
    },

    //POLISHED SILVER
    {
        0.23125f, 0.23125f, 0.23125f, 1.0f,
        0.2775f, 0.2775f, 0.2775f, 1.0f,
        0.773911f, 0.773911f, 0.773911f, 1.0f,
        0.0f, 0.0f, 0.0f, 1.0f,
        0.7f
    },

    //PEWTER
    {
        0.105882f, 0.058824f, 0.113725f, 1.0f,
        0.427451f, 0.470588f, 0.541176f, 1.0f,
        0.333333f, 0.333333f, 0.521569f, 1.0f,
        0.0f, 0.0f, 0.0f, 1.0f,
        0.076925046875f
    },

    //BLACK PLASTIC
    {
        0.0f, 0.0f, 0.0f, 1.0f,
        0.01f, 0.01f, 0.01f, 1.0f,
        0.50f, 0.50f, 0.50f, 1.0f,
        0.0f, 0.0f, 0.0f, 1.0f,
        0.25f
    },

    //BLACK RUBBER
    {
        0.02f, 0.02f, 0.02f, 1.0f,
        0.01f, 0.01f, 0.01f, 1.0f,
        0.4f, 0.4f, 0.4f, 1.0f,
        0.0f, 0.0f, 0.0f, 1.0f,
        0.078125f
    }
};