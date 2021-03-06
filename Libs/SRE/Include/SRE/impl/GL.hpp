#pragma once

/// Include GL header

#if defined(_WIN32)
#   define GLEW_STATIC
#   include <GL/glew.h>
#elif defined __linux__
#   include <GL/glew.h>
#else
#   include  <OpenGL/gl3.h>
#endif