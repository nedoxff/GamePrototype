include(FetchContent)

FetchContent_Declare(
        sfml
        GIT_REPOSITORY "https://github.com/SFML/SFML"
        GIT_TAG 8838030d67e1ba9ad3895e650c5d110f11c0450e
)
message(STATUS "Fetching SFML..")
FetchContent_MakeAvailable(sfml)

FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui
        GIT_TAG f5c5926fb91764c2ec0e995970818d79b5873d42
)
message(STATUS "Fetching ImGui..")
FetchContent_MakeAvailable(imgui)

FetchContent_Declare(
        imgui-sfml
        GIT_REPOSITORY https://github.com/eliasdaler/imgui-sfml
        GIT_TAG 004efd85a590343e8c9d166dc9d2524c199c9450
)
message(STATUS "Fetching ImGui-SFML...")
set(IMGUI_DIR ${imgui_SOURCE_DIR})
set(IMGUI_SFML_FIND_SFML OFF)
set(IMGUI_SFML_IMGUI_DEMO ON)
FetchContent_MakeAvailable(imgui-sfml)

FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog
        GIT_TAG b1478d98f017f3a7644e6e3a16fab6a47a5c26ba
)
message(STATUS "Fetching spdlog..")
FetchContent_MakeAvailable(spdlog)

FetchContent_Declare(
        tweeny
        GIT_REPOSITORY https://github.com/mobius3/tweeny
        GIT_TAG bfec58626cee13f4912f6d13b24042d67cc1fff3
)
message(STATUS "Fetching tweeny..")
FetchContent_MakeAvailable(tweeny)

FetchContent_Declare(
        motion
        GIT_REPOSITORY https://github.com/NedoProgrammer/MotionPP
        GIT_TAG fc3723db02256469d2fdabf87842a1bbb72a6847
)
message(STATUS "Fetching Motion..")
set(FFMPEG_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../ffmpeg")
FetchContent_MakeAvailable(motion)

FetchContent_Declare(
        pugixml
        GIT_REPOSITORY https://github.com/zeux/pugixml
        GIT_TAG 363ebdde91214e456943822ddf422860af8bb54d
)
message(STATUS "Fetching pugixml..")
FetchContent_MakeAvailable(pugixml)