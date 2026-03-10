cmake_minimum_required(VERSION 3.10)
project(CGraph_exp)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 包含CGraph头文件
include_directories(thirdparty/CGraph)

# 包含nlohmann/json头文件
include_directories(thirdparty)

# 包含项目头文件
include_directories(src/include)

# 收集源文件
file(GLOB SOURCES "src/src/*.cpp")

# 收集CGraph源文件
file(GLOB_RECURSE CGRAPH_SOURCES
    "thirdparty/CGraph/CBasic/*.cpp"
    "thirdparty/CGraph/GraphCtrl/GraphAspect/*.cpp"
    "thirdparty/CGraph/GraphCtrl/GraphDaemon/*.cpp"
    "thirdparty/CGraph/GraphCtrl/GraphElement/*.cpp"
    "thirdparty/CGraph/GraphCtrl/GraphElement/GNode/*.cpp"
    "thirdparty/CGraph/GraphCtrl/GraphElement/GGroup/*.cpp"
    "thirdparty/CGraph/GraphCtrl/GraphEvent/*.cpp"
    "thirdparty/CGraph/GraphCtrl/GraphParam/*.cpp"
    "thirdparty/CGraph/GraphCtrl/GraphPipeline/*.cpp"
    "thirdparty/CGraph/GraphCtrl/GraphPipeline/_GPerf/*.cpp"
    "thirdparty/CGraph/GraphCtrl/GraphPipeline/_GSchedule/*.cpp"
    "thirdparty/CGraph/GraphCtrl/GraphPipeline/_GStroage/*.cpp"
    "thirdparty/CGraph/GraphCtrl/GraphStage/*.cpp"
    "thirdparty/CGraph/UtilsCtrl/ThreadPool/*.cpp"
    "thirdparty/CGraph/UtilsCtrl/Timer/*.cpp"
    "thirdparty/CGraph/UtilsCtrl/Container/*.cpp"
    "thirdparty/CGraph/UtilsCtrl/Distance/*.cpp"
    "thirdparty/CGraph/UtilsCtrl/Lru/*.cpp"
    "thirdparty/CGraph/UtilsCtrl/Random/*.cpp"
    "thirdparty/CGraph/UtilsCtrl/Reflection/*.cpp"
    "thirdparty/CGraph/UtilsCtrl/Singleton/*.cpp"
)

# 添加可执行文件
add_executable(CGraph_exp ${SOURCES} ${CGRAPH_SOURCES})

# 不需要链接nlohmann/json库，因为它是头文件库

# 复制数据文件到构建目录
add_custom_command(TARGET CGraph_exp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/src/data
    ${CMAKE_BINARY_DIR}/src/data
)