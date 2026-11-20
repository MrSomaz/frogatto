#pragma once
// Desktop GL enums/functions missing from GLES3
#ifndef GL_BGRA
#define GL_BGRA 0x80E1
#endif
#ifndef GL_BGR
#define GL_BGR 0x80E0
#endif
#ifndef GL_QUADS
#define GL_QUADS 0x0007
#endif
#ifndef GL_CLAMP
#define GL_CLAMP 0x2900
#endif
#ifndef GL_CLAMP_TO_BORDER
#define GL_CLAMP_TO_BORDER 0x812D
#endif
#ifndef GL_TEXTURE_1D
#define GL_TEXTURE_1D 0x0DE0
#endif
#ifndef GL_DOUBLE
#define GL_DOUBLE 0x140A
#endif
#ifndef GL_POLYGON
#define GL_POLYGON 0x0009
#endif
#ifndef GL_QUAD_STRIP
#define GL_QUAD_STRIP 0x0008
#endif
#ifndef GL_LINE
#define GL_LINE 0x1B01
#endif
#ifndef GL_FILL
#define GL_FILL 0x1B02
#endif
#ifndef GL_POINT
#define GL_POINT 0x1B00
#endif
#ifndef GL_UNSIGNED_INT_8_8_8_8
#define GL_UNSIGNED_INT_8_8_8_8 0x8035
#endif
#ifndef GL_UNSIGNED_INT_8_8_8_8_REV
#define GL_UNSIGNED_INT_8_8_8_8_REV 0x8367
#endif
#ifndef GL_PROGRAM_POINT_SIZE
#define GL_PROGRAM_POINT_SIZE 0x8642
#endif
#ifndef GL_POINT_SPRITE
#define GL_POINT_SPRITE 0x8861
#endif
#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE 0x809D
#endif
#ifndef GL_LINE_SMOOTH
#define GL_LINE_SMOOTH 0x0B20
#endif
#ifndef GL_POLYGON_SMOOTH
#define GL_POLYGON_SMOOTH 0x0B41
#endif
#ifndef GL_TEXTURE_BORDER_COLOR
#define GL_TEXTURE_BORDER_COLOR 0x1004
#endif
#ifndef GL_DEPTH_COMPONENT32
#define GL_DEPTH_COMPONENT32 0x81A7
#endif
#ifndef GL_STENCIL_INDEX1
#define GL_STENCIL_INDEX1 0x8D46
#endif
#ifndef GL_STENCIL_INDEX4
#define GL_STENCIL_INDEX4 0x8D47
#endif
#ifndef GL_STENCIL_INDEX16
#define GL_STENCIL_INDEX16 0x8D49
#endif
#ifndef GL_R16
#define GL_R16 0x822A
#endif
#ifndef GL_RG16
#define GL_RG16 0x822C
#endif
#ifndef GL_RGB16
#define GL_RGB16 0x8054
#endif
#ifndef GL_RGBA16
#define GL_RGBA16 0x805B
#endif
#ifndef GL_RGBA12
#define GL_RGBA12 0x805A
#endif
#ifndef GL_RGB4
#define GL_RGB4 0x804F
#endif
#ifndef GL_RGB5
#define GL_RGB5 0x8050
#endif
#ifndef GL_RGB10
#define GL_RGB10 0x8052
#endif
#ifndef GL_RGB12
#define GL_RGB12 0x8053
#endif
#ifndef GL_RGBA2
#define GL_RGBA2 0x8055
#endif
#ifndef GL_R3_G3_B2
#define GL_R3_G3_B2 0x2A10
#endif
#ifndef GL_ALPHA8
#define GL_ALPHA8 0x803C
#endif
#ifndef GL_LUMINANCE8
#define GL_LUMINANCE8 0x8040
#endif
#ifndef GL_LUMINANCE8_ALPHA8
#define GL_LUMINANCE8_ALPHA8 0x8045
#endif
#ifndef GL_UNSIGNED_BYTE_3_3_2
#define GL_UNSIGNED_BYTE_3_3_2 0x8032
#endif
#ifndef GL_UNSIGNED_BYTE_2_3_3_REV
#define GL_UNSIGNED_BYTE_2_3_3_REV 0x8362
#endif
#ifndef GL_UNSIGNED_SHORT_5_6_5_REV
#define GL_UNSIGNED_SHORT_5_6_5_REV 0x8364
#endif
#ifndef GL_UNSIGNED_SHORT_4_4_4_4_REV
#define GL_UNSIGNED_SHORT_4_4_4_4_REV 0x8365
#endif
#ifndef GL_UNSIGNED_SHORT_1_5_5_5_REV
#define GL_UNSIGNED_SHORT_1_5_5_5_REV 0x8366
#endif
#ifndef GL_UNSIGNED_INT_10_10_10_2
#define GL_UNSIGNED_INT_10_10_10_2 0x8036
#endif
#ifndef GL_TEXTURE_CUBE_MAP_SEAMLESS
#define GL_TEXTURE_CUBE_MAP_SEAMLESS 0x884F
#endif
#ifndef GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER
#define GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER 0x8CDB
#endif
#ifndef GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER
#define GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER 0x8CDC
#endif
#ifndef GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS
#define GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS 0x8DA8
#endif
#ifndef GL_SAMPLER_1D
#define GL_SAMPLER_1D 0x8B5D
#endif
#ifndef GL_SAMPLER_1D_SHADOW
#define GL_SAMPLER_1D_SHADOW 0x8B61
#endif
#ifndef GL_FUNC_ADD_EXT
#define GL_FUNC_ADD_EXT 0x8006
#endif
#ifndef GL_MIN_EXT
#define GL_MIN_EXT 0x8007
#endif
#ifndef GL_MAX_EXT
#define GL_MAX_EXT 0x8008
#endif
#ifndef GL_FUNC_SUBTRACT_EXT
#define GL_FUNC_SUBTRACT_EXT 0x800A
#endif
#ifndef GL_FUNC_REVERSE_SUBTRACT_EXT
#define GL_FUNC_REVERSE_SUBTRACT_EXT 0x800B
#endif
#ifndef GL_FRAMEBUFFER_EXT
#define GL_FRAMEBUFFER_EXT GL_FRAMEBUFFER
#define GL_RENDERBUFFER_EXT GL_RENDERBUFFER
#define GL_COLOR_ATTACHMENT0_EXT GL_COLOR_ATTACHMENT0
#define GL_DEPTH_ATTACHMENT_EXT GL_DEPTH_ATTACHMENT
#define GL_STENCIL_ATTACHMENT_EXT GL_STENCIL_ATTACHMENT
#define GL_FRAMEBUFFER_COMPLETE_EXT GL_FRAMEBUFFER_COMPLETE
#define GL_DEPTH_STENCIL_EXT GL_DEPTH_STENCIL
#define GL_DEPTH24_STENCIL8_EXT GL_DEPTH24_STENCIL8
#endif
#ifndef GL_READ_FRAMEBUFFER_EXT
#define GL_READ_FRAMEBUFFER_EXT GL_READ_FRAMEBUFFER
#define GL_DRAW_FRAMEBUFFER_EXT GL_DRAW_FRAMEBUFFER
#endif
#ifndef GL_STACK_OVERFLOW
#define GL_STACK_OVERFLOW 0x0503
#define GL_STACK_UNDERFLOW 0x0504
#endif
#ifndef GL_TEXTURE_RECTANGLE
#define GL_TEXTURE_RECTANGLE 0x84F5
#endif
#ifndef GL_TEXTURE_1D_ARRAY
#define GL_TEXTURE_1D_ARRAY 0x8C18
#endif
#ifndef GL_PROXY_TEXTURE_2D
#define GL_PROXY_TEXTURE_2D 0x8064
#endif

#ifdef __cplusplus
extern "C" {
#endif
static inline void glPolygonMode(GLenum, GLenum) {}
static inline void glPointSize(GLfloat) {}
static inline void glLineStipple(GLint, GLushort) {}
static inline void glTexImage1D(GLenum, GLint, GLint, GLsizei, GLint, GLenum, GLenum, const void*) {}
static inline void glTexSubImage1D(GLenum, GLint, GLint, GLsizei, GLenum, GLenum, const void*) {}
static inline void glGetTexImage(GLenum, GLint, GLenum, GLenum, void*) {}
static inline void glDrawBuffer(GLenum) {}
static inline void glClearDepth(double d) { glClearDepthf((float)d); }
static inline void glDepthRange(double n, double f) { glDepthRangef((float)n, (float)f); }
#ifdef __cplusplus
}
#endif
#ifndef GL_STENCIL_INDEX
#define GL_STENCIL_INDEX 0x1901
#endif
#ifndef GL_RED_INTEGER
#define GL_RED_INTEGER 0x8D94
#endif
#ifndef GL_GREEN_INTEGER
#define GL_GREEN_INTEGER 0x8D95
#endif
#ifndef GL_BLUE_INTEGER
#define GL_BLUE_INTEGER 0x8D96
#endif
#ifndef GL_BGR_INTEGER
#define GL_BGR_INTEGER 0x8D9A
#endif
#ifndef GL_BGRA_INTEGER
#define GL_BGRA_INTEGER 0x8D9B
#endif
#ifndef GL_LINE_STIPPLE
#define GL_LINE_STIPPLE 0x0B24
#endif
#ifndef GL_GEOMETRY_SHADER
#define GL_GEOMETRY_SHADER 0x8DD9
#endif
#ifndef GL_TESS_EVALUATION_SHADER
#define GL_TESS_EVALUATION_SHADER 0x8E87
#endif
#ifndef GL_TESS_CONTROL_SHADER
#define GL_TESS_CONTROL_SHADER 0x8E88
#endif
#ifndef GL_COMPUTE_SHADER
#define GL_COMPUTE_SHADER 0x91B9
#endif
#ifndef GL_TEXTURE_LOD_BIAS
#define GL_TEXTURE_LOD_BIAS 0x8501
#endif
#ifndef GL_WRITE_ONLY
#define GL_WRITE_ONLY 0x88B9
#endif
#ifndef GL_READ_ONLY
#define GL_READ_ONLY 0x88B8
#endif
#ifndef GL_READ_WRITE
#define GL_READ_WRITE 0x88BA
#endif
#ifndef GL_BLEND_SRC
#define GL_BLEND_SRC 0x0BE1
#endif
#ifndef GL_BLEND_DST
#define GL_BLEND_DST 0x0BE0
#endif
#define GLEW_ARB_explicit_attrib_location 0
static inline int glewIsSupported(const char*) { return 0; }
static inline void glMultiDrawArrays(GLenum mode, const GLint* first, const GLsizei* count, GLsizei n) { for (GLsizei i = 0; i < n; ++i) glDrawArrays(mode, first[i], count[i]); }
static inline void glVertexAttribI1i(GLuint i, GLint x) { glVertexAttribI4i(i, x, 0, 0, 1); }
static inline void glVertexAttribI2i(GLuint i, GLint x, GLint y) { glVertexAttribI4i(i, x, y, 0, 1); }
static inline void glVertexAttribI3iv(GLuint i, const GLint* v) { glVertexAttribI4i(i, v[0], v[1], v[2], 1); }
static inline void glVertexAttrib4ubv(GLuint i, const GLubyte* v) { glVertexAttrib4f(i, v[0]/255.0f, v[1]/255.0f, v[2]/255.0f, v[3]/255.0f); }
// GLES has no GL_BLEND_SRC/DST queries: use the RGB variants.
#undef GL_BLEND_SRC
#undef GL_BLEND_DST
#define GL_BLEND_SRC GL_BLEND_SRC_RGB
#define GL_BLEND_DST GL_BLEND_DST_RGB
