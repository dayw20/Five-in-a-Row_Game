cmake_minimum_required(VERSION 3.10)
project(FiveInARow VERSION 1.0.0 LANGUAGES CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 源文件
set(SOURCES
    gobang.cpp
)

# 创建可执行文件
add_executable(gobang ${SOURCES})

# Windows特定设置
if(WIN32)
    # 链接WinSock2库
    target_link_libraries(gobang ws2_32)
    
    # 查找EasyX库（如果已安装）
    find_path(EASYX_INCLUDE_DIR graphics.h
        PATHS
        "C:/Program Files (x86)/Microsoft Visual Studio/*/Community/VC/Auxiliary/VS/include"
        "C:/Program Files (x86)/Microsoft Visual Studio/*/Professional/VC/Auxiliary/VS/include"
        "C:/Program Files (x86)/Microsoft Visual Studio/*/Enterprise/VC/Auxiliary/VS/include"
        "C:/Program Files/Microsoft Visual Studio/*/Community/VC/Auxiliary/VS/include"
        "C:/Program Files/Microsoft Visual Studio/*/Professional/VC/Auxiliary/VS/include"
        "C:/Program Files/Microsoft Visual Studio/*/Enterprise/VC/Auxiliary/VS/include"
        DOC "EasyX include directory"
    )
    
    if(EASYX_INCLUDE_DIR)
        target_include_directories(gobang PRIVATE ${EASYX_INCLUDE_DIR})
        message(STATUS "Found EasyX at: ${EASYX_INCLUDE_DIR}")
    else()
        message(WARNING "EasyX not found. Please install EasyX graphics library.")
        message(STATUS "Download from: https://easyx.cn/")
    endif()
    
    # 设置Windows子系统
    set_target_properties(gobang PROPERTIES
        WIN32_EXECUTABLE TRUE
    )
endif()

# Linux/macOS特定设置
if(UNIX AND NOT APPLE)
    message(STATUS "Linux detected. You may need to install X11 development libraries.")
    message(STATUS "Ubuntu/Debian: sudo apt-get install libx11-dev")
    message(STATUS "CentOS/RHEL: sudo yum install libX11-devel")
endif()

if(APPLE)
    message(STATUS "macOS detected. You may need to install XQuartz for X11 support.")
endif()

# 编译选项
target_compile_options(gobang PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W3>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra>
)

# 安装规则
install(TARGETS gobang
    RUNTIME DESTINATION bin
)

# 打印构建信息
message(STATUS "Building Five-in-a-Row Game")
message(STATUS "Target: ${CMAKE_TARGET}")
message(STATUS "Output directory: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
