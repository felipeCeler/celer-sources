project(CelerOpenGL)

 
set(CelerOpenGL_SRCS
    OpenGLContext.cpp
    Texture.cpp
    PixelBuffer.cpp
    FrameBuffer.cpp
    Shader.cpp
    ShaderManager.cpp
)

set(CelerOpenGL_HEADERS
    OpenGLContext.hpp
    Texture.hpp
    PixelBuffer.hpp
    FrameBuffer.hpp
    Shader.hpp
    ShaderManager.hpp
)

     
add_library( CelerOpenGL STATIC  ${CelerOpenGL_SRCS} ${CelerOpenGL_HEADERS} )
     
target_link_libraries(CelerOpenGL CelerBase ${OPENGL_LIBRARIES} ${GLEW_GLEW_LIBRARY} )
