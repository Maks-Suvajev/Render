add_library(RenderLib 
    source/RenderSystem.cpp
    source/Renderer.cpp
)

target_include_directories(RenderLib 
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/source
)

target_link_libraries(RenderLib 
    PUBLIC TypeLib
    PUBLIC ShaderLib
    PUBLIC CameraLib
    PUBLIC EntityLib
    PUBLIC LightingLib
)