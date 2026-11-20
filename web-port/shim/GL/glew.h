#pragma once
// GLEW shim for Emscripten/WebGL2
#include <GLES3/gl3.h>
#include <GLES2/gl2ext.h>
#define GLEW_OK 0
static inline unsigned glewInit(void) { return GLEW_OK; }
static inline const unsigned char* glewGetErrorString(unsigned) { return (const unsigned char*)"ok"; }
#define GLEW_EXT_blend_minmax 1
#define GLEW_ARB_framebuffer_object 1
#define GLEW_EXT_framebuffer_object 1
#define GLEW_EXT_framebuffer_multisample 0
#define GLEW_EXT_packed_depth_stencil 1
#define GLEW_VERSION_2_0 1
#define GLEW_VERSION_3_0 1
#include "gl_desktop_compat.h"
