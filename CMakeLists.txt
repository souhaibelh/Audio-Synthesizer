cmake_minimum_required(VERSION 3.31)
project(61610.synthetizer)

set(CMAKE_CXX_STANDARD 23)

include_directories(
        "libraries/portaudio/include"
        "libraries/imgui/backends"
        "libraries/imgui"
        "libraries/sdl/include"
)

add_executable(
        61610.synthetizer
        src/main.cpp
        src/model/AudioGenerator.cpp
        src/ui/MainWindow.cpp
        ./libraries/imgui/imgui.cpp
        ./libraries/imgui/imgui_demo.cpp
        ./libraries/imgui/imgui_draw.cpp
        ./libraries/imgui/imgui_widgets.cpp
        ./libraries/imgui/imgui_tables.cpp
        ./libraries/imgui/backends/imgui_impl_sdl3.cpp
        ./libraries/imgui/backends/imgui_impl_sdlrenderer3.cpp
        include/model/utils/Parameters.h
        include/model/oscillators/Oscillator.h
        src/model/oscillators/Oscillator.cpp
        include/model/AudioEngine.h
        src/model/AudioEngine.cpp
        include/model/utils/OscillatorManager.h
        src/model/utils/OscillatorManager.cpp
        include/model/effects/AudioEffect.h
        include/model/effects/MixEffect.h
        src/model/effects/MixEffect.cpp
        include/model/effects/EnvelopeEffect.h
        src/model/effects/EnvelopeEffect.cpp
        include/model/effects/FilterEffect.h
        src/model/effects/FilterEffect.cpp
        include/model/effects/DelayEffect.h
        src/model/effects/DelayEffect.cpp
        include/model/oscillators/WaveformStrategy.h
        src/model/oscillators/SineWaveStrategy.cpp
        include/model/oscillators/SineWaveStrategy.h
        include/model/oscillators/SquareWaveStrategy.h
        src/model/oscillators/SquareWaveStrategy.cpp
        include/model/oscillators/SawWaveStrategy.h
        src/model/oscillators/SawWaveForm.cpp
)

if (APPLE)
    set(
            CMAKE_INSTALL_RPATH
            "${CMAKE_SOURCE_DIR}/../libraries/sdl/lib/macos/SDL3.framework"
    )
    target_link_libraries(
            "-framework CoreFoundation"
            "-framework AudioToolbox"
            "-framework CoreAudio"
            "-framework Carbon"
            "${CMAKE_SOURCE_DIR/libraries/portaudio/lib/macos/libportaudio.a}"
    )
    target_link_libraries(
            61610.synthetizer PRIVATE
            "${CMAKE_SOURCE_DIR}/libraries/sdl/lib/macos/SDL3.framework"
            "-framework CoreFoundation"
    )
elseif (WIN32)
    target_link_libraries(
            61610.synthetizer PRIVATE
            "${CMAKE_SOURCE_DIR}/libraries/sdl/lib/win32/sdl3.dll"
    )
    target_link_libraries(
            61610.synthetizer PRIVATE
            "${CMAKE_SOURCE_DIR}/libraries/portaudio/lib/win32/portaudio_x64.dll"
    )
    add_custom_command(TARGET 61610.synthetizer POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_SOURCE_DIR}/libraries/portaudio/lib/win32/portaudio_x64.dll"
            "$<TARGET_FILE_DIR:61610.synthetizer>/portaudio_x64.dll"
    )
    add_custom_command(
            TARGET 61610.synthetizer POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_SOURCE_DIR}/libraries/sdl/lib/win32/sdl3.dll"
            "$<TARGET_FILE_DIR:61610.synthetizer>"
    )
elseif (UNIX)
    target_link_libraries(
            61610.synthetizer PRIVATE
            "-ldl"
            "-ljack"
            "${CMAKE_SOURCE_DIR}/libraries/sdl/lib/linux-x86_64/libSDL3.a"
    )
    target_link_libraries(
            61610.synthetizer PRIVATE
            "-ljack"
            "${CMAKE_SOURCE_DIR}/libraries/portaudio/lib/linux-x86_64/libportaudio.a"
    )
endif ()