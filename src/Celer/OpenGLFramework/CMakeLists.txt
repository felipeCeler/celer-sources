project(CelerOpenGLFramework)

 
set(CelerOpenGLFramework_SRCS
    OpenGLContext.cpp
    GLTexture.cpp
    PixelBuffer.cpp
    FrameBuffer.cpp
    Shader.cpp
    ShaderManager.cpp
)

set(CelerOpenGLFramework_HEADERS
    OpenGLContext.hpp
    GLTexture.hpp
    PixelBuffer.hpp
    FrameBuffer.hpp
    Shader.hpp
    ShaderManager.hpp
)

     
add_library( CelerOpenGLFramework STATIC  ${CelerOpenGLFramework_SRCS} ${CelerOpenGLFramework_HEADERS} )
     
target_link_libraries(CelerOpenGLFramework CelerBase ${OPENGL_LIBRARIES} ${GLEW_GLEW_LIBRARY} )
