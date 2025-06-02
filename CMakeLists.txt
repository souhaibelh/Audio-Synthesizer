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
        main.cpp
        model/AudioGenerator.cpp
        ui/MainWindow.cpp
        ./libraries/imgui/imgui.cpp
        ./libraries/imgui/imgui_demo.cpp
        ./libraries/imgui/imgui_draw.cpp
        ./libraries/imgui/imgui_widgets.cpp
        ./libraries/imgui/imgui_tables.cpp
        ./libraries/imgui/backends/imgui_impl_sdl3.cpp
        ./libraries/imgui/backends/imgui_impl_sdlrenderer3.cpp
        model/utils/Parameters.h
        model/oscillators/Oscillator.h
        model/oscillators/Oscillator.cpp
        model/AudioEngine.h
        model/AudioEngine.cpp
        model/utils/OscillatorManager.h
        model/utils/OscillatorManager.cpp
        model/effects/AudioEffect.h
        model/effects/MixEffect.h
        model/effects/MixEffect.cpp
        model/effects/EnvelopeEffect.h
        model/effects/EnvelopeEffect.cpp
        model/effects/FilterEffect.h
        model/effects/FilterEffect.cpp
        model/effects/DelayEffect.h
        model/effects/DelayEffect.cpp
        model/oscillators/WaveformStrategy.h
        model/oscillators/SineWaveStrategy.cpp
        model/oscillators/SineWaveStrategy.h
        model/oscillators/SquareWaveStrategy.h
        model/oscillators/SquareWaveStrategy.cpp
        model/oscillators/SawWaveStrategy.h
        model/oscillators/SawWaveForm.cpp
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
            simple_synth PRIVATE
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