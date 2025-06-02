#include "MainWindow.h"
#include <cmath>
#include <functional>
#include <iostream>
#include <thread>
#include <unordered_map>
#include <vector>
#include "../model/utils/Parameters.h"
#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"

constexpr float FRAMERATE = 60.0f;
constexpr std::chrono::duration<double, std::milli> TARGET_FRAMETIME(1000.0 / FRAMERATE);

MainWindow::MainWindow(SynthParameters& parameters) : parameters(parameters) {

}

void MainWindow::init() {
    // Setup SDL
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD)) {
        SDL_Log("Error: SDL_Init(): %s\n", SDL_GetError());
        return;
    }
    // Create window with SDL_Renderer graphics context
    Uint32 window_flags = SDL_WINDOW_HIDDEN | SDL_WINDOW_RESIZABLE;
    window = SDL_CreateWindow("", 500, 300, window_flags);
    if (nullptr == window) {
        SDL_Log("Error: SDL_CreateWindow(): %s\n", SDL_GetError());
        return;
    }
    renderer = SDL_CreateRenderer(window, nullptr);
    SDL_SetRenderVSync(renderer, 1);
    if (nullptr == renderer) {
        SDL_Log("Error: SDL_CreateRenderer(): %s\n", SDL_GetError());
        return;
    }
    SDL_SetWindowPosition(
            window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    SDL_ShowWindow(window);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    // Setup DearImGui style
    ImGui::StyleColorsDark();
    ImGui::GetStyle().WindowRounding = 0.0f;

    // Setup Platform/Renderer backends
    ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer3_Init(renderer);
}

void MainWindow::run() {
    const auto clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    bool done { false };
    while (!done){
        auto frameStart = std::chrono::high_resolution_clock::now();

        SDL_Event event;
        while (SDL_PollEvent(&event)){
            ImGui_ImplSDL3_ProcessEvent(&event);
            if (SDL_EVENT_QUIT == event.type)
                done = true;
            if ((SDL_EVENT_WINDOW_CLOSE_REQUESTED == event.type)
                && (SDL_GetWindowID(window) == event.window.windowID))
                done = true;
        }

        // Start the Dear ImGui frame
        ImGui_ImplSDLRenderer3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

        // all the UI code description
        draw();

        // Rendering
        ImGui::Render();
        SDL_SetRenderDrawColorFloat(renderer,
                                    clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        SDL_RenderClear(renderer);
        ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);
        SDL_RenderPresent(renderer);

        // Calculate time spent and sleep if needed
        auto frameEnd = std::chrono::high_resolution_clock::now();
        auto frameDuration = frameEnd - frameStart;
        if (frameDuration < TARGET_FRAMETIME) {
            std::this_thread::sleep_for(TARGET_FRAMETIME - frameDuration);
        }
    }

    // Cleanup
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void MainWindow::oscillatorOptions() {
    ImGui::Checkbox("OSC 1", &parameters.osc1.enabled);

    static std::vector oscillators = {
        "SINE", "SQUARE", "SAW"
    };
    ImGui::Combo("OSC1 Waveform", &parameters.osc1.waveform, oscillators.data(), static_cast<int>(oscillators.size()));

    ImGui::SliderFloat("OSC1 Frequency Offset", &parameters.osc1.frequencyOffset, -5, 5);

    ImGui::Checkbox("OSC 2", &parameters.osc2.enabled);
}

void MainWindow::envelopeOptions() {
    ImGui::SliderFloat("Attack", &parameters.envelope.attack, 0.0f, 1.0f);

    ImGui::SliderFloat("Release", &parameters.envelope.release, 0.0f, 2.0f);
}

void MainWindow::filterOptions() {
    ImGui::SliderInt("Filter Cutoff", &parameters.filter.cutoff, 20, 20000);

    ImGui::SliderFloat("Filter Resonance", &parameters.filter.resonance, 0.0f, 1.0f);
}

void MainWindow::delayOptions() {
    ImGui::SliderFloat("Delay Time", &parameters.delay.time, 0.1f, 2.0f);

    ImGui::SliderFloat("Delay Mix", &parameters.delay.mix, 0.0f, 1.0f);
}

void MainWindow::playNote(float frequency, int durationMs) {
    auto start = std::chrono::steady_clock::now();
    parameters.note.noteOnTime = parameters.currentTime;

    while (true) {
        parameters.note.isOn = true;
        parameters.note.frequency = frequency;

        auto now = std::chrono::steady_clock::now();
        auto elapsedMs = std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count();

        if (elapsedMs >= durationMs) {
            break;
        }
    }
}

void MainWindow::handleNoteTrigger() {
    bool wasOn = parameters.note.isOn;
    bool isNowOn = false;

    for (int i = 0; i < 12; i++) {
        if (ImGui::Button(std::to_string(i).c_str()) || ImGui::IsItemActive()) {
            isNowOn = true;
            parameters.note.frequency = 220.0f * std::pow(2, i / 12.0f);
        }
        ImGui::SameLine();
    }

    static const std::unordered_map<ImGuiKey, int> keyToNoteIndex = {
        { ImGuiKey_Q, 0 },
        { ImGuiKey_Z, 1 },
        { ImGuiKey_S, 2 },
        { ImGuiKey_E, 3 },
        { ImGuiKey_D, 4 },
        { ImGuiKey_F, 5 },
        { ImGuiKey_T, 6 },
        { ImGuiKey_G, 7 },
        { ImGuiKey_Y, 8 },
        { ImGuiKey_H, 9 },
        { ImGuiKey_U, 10 },
        { ImGuiKey_J, 11 },
    };

    for (const auto& [key, index] : keyToNoteIndex) {
        if (ImGui::IsKeyDown(key)) {
            isNowOn = true;
            parameters.note.frequency = 220.0f * std::pow(2, index / 12.0f);
        }
    }

    if (isNowOn && !wasOn) {
        parameters.note.noteOnTime = parameters.currentTime;
    } else if (!isNowOn && wasOn) {
        parameters.note.noteOffTime = parameters.currentTime;
    }

    parameters.note.isOn = isNowOn;
}

void MainWindow::draw() {
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
    ImGui::Begin("Synthetizer");
    oscillatorOptions();
    envelopeOptions();
    filterOptions();
    delayOptions();
    handleNoteTrigger();
    ImGui::NewLine();
    if (ImGui::Button("sample1")) {
        std::thread([this]() {
            playNote(261.63, 500);
            playNote(261.63, 500);
            playNote(349.23, 500);
            playNote(349.23, 500);
            playNote(392.00, 500);
            playNote(392.00, 500);
            playNote(349.23, 1000);
            playNote(369.99, 500);
            playNote(369.99, 500);
            playNote(329.63, 500);
            playNote(329.63, 500);
            playNote(293.66, 500);
            playNote(293.66, 500);
            playNote(277.18, 1000);
            playNote(261.63, 500);
            playNote(261.63, 500);
            playNote(349.23, 500);
            playNote(349.23, 500);
            playNote(392.00, 500);
            playNote(392.00, 500);
            playNote(349.23, 1000);
            playNote(369.99, 500);
            playNote(369.99, 500);
            playNote(329.63, 500);
            playNote(329.63, 500);
            playNote(293.66, 500);
            playNote(293.66, 500);
            playNote(277.18, 1000);
        }).detach();
    }
    ImGui::SameLine();
    if (ImGui::Button("sample2")) {
        std::thread([this]() {
            playNote(220.00, 500);
            playNote(246.94, 500);
            playNote(277.18, 500);
            playNote(246.94, 500);
            playNote(220.00, 500);
            playNote(220.00, 500);
            playNote(220.00, 1000);

            playNote(246.94, 500);
            playNote(246.94, 500);
            playNote(246.94, 1000);
            playNote(220.00, 500);
            playNote(349.23, 500);
            playNote(349.23, 1000);

            playNote(220.00, 500);
            playNote(246.94, 500);
            playNote(277.18, 500);
            playNote(246.94, 500);
            playNote(220.00, 500);
            playNote(220.00, 500);
            playNote(220.00, 1000);

            playNote(246.94, 500);
            playNote(246.94, 500);
            playNote(220.00, 500);
            playNote(349.23, 500);
            playNote(220.00, 1000);
        }).detach();
    }
    ImGui::SameLine();
    if (ImGui::Button("sample3")) {
        std::thread([this]() {
            playNote(220.00f, 500);   // Q
            playNote(220.00f, 500);   // Q
            playNote(246.94f, 500);   // S
            playNote(277.18f, 500);   // D
            playNote(293.66f, 500);   // F
            playNote(293.66f, 500);   // F
            playNote(246.94f, 1000);  // S

            playNote(220.00f, 500);   // Q
            playNote(220.00f, 500);   // Q
            playNote(246.94f, 500);   // S
            playNote(277.18f, 500);   // D
            playNote(293.66f, 500);   // F
            playNote(293.66f, 500);   // F
            playNote(246.94f, 1000);  // S

            playNote(277.18f, 500);   // D
            playNote(277.18f, 500);   // D
            playNote(261.63f, 500);   // E
            playNote(261.63f, 500);   // E
            playNote(293.66f, 500);   // F
            playNote(329.63f, 500);   // G
            playNote(392.00f, 1000);  // U

            playNote(293.66f, 500);   // F
            playNote(293.66f, 500);   // F
            playNote(261.63f, 500);   // E
            playNote(261.63f, 500);   // E
            playNote(277.18f, 500);   // D
            playNote(246.94f, 500);   // S
            playNote(220.00f, 1000);  // Q
        }).detach();
    }
    if (ImGui::Button("sample4")) {
        std::thread([this]() {
            // Section 1 (16 sec)
            playNote(220.00f, 500); // Q (A)
            playNote(246.94f, 500); // S (B)
            playNote(277.18f, 500); // D (C#)
            playNote(293.66f, 500); // F (D#)
            playNote(329.63f, 250); // G (E)
            playNote(293.66f, 250); // F (D#)
            playNote(277.18f, 500); // D (C#)
            playNote(246.94f, 1000); // S (B)
            playNote(220.00f, 500); // Q (A)
            playNote(220.00f, 500); // Q (A)
            playNote(246.94f, 500); // S (B)
            playNote(277.18f, 500); // D (C#)
            playNote(293.66f, 250); // F (D#)
            playNote(329.63f, 250); // G (E)
            playNote(369.99f, 500); // U (F#)
            playNote(329.63f, 1000); // G (E)

            // Section 2 (16 sec)
            playNote(293.66f, 500); // F (D#)
            playNote(277.18f, 500); // D (C#)
            playNote(246.94f, 500); // S (B)
            playNote(220.00f, 1000); // Q (A)
            playNote(246.94f, 500); // S (B)
            playNote(277.18f, 500); // D (C#)
            playNote(293.66f, 500); // F (D#)
            playNote(329.63f, 500); // G (E)
            playNote(293.66f, 250); // F (D#)
            playNote(277.18f, 250); // D (C#)
            playNote(246.94f, 500); // S (B)
            playNote(220.00f, 1000); // Q (A)
            playNote(196.00f, 500); // Z (G)
            playNote(220.00f, 500); // Q (A)
            playNote(246.94f, 500); // S (B)
            playNote(277.18f, 1000); // D (C#)

            // Section 3 (16 sec)
            playNote(293.66f, 500); // F (D#)
            playNote(329.63f, 500); // G (E)
            playNote(369.99f, 500); // U (F#)
            playNote(392.00f, 500); // H (G#)
            playNote(440.00f, 500); // Y (A)
            playNote(392.00f, 500); // H (G#)
            playNote(369.99f, 500); // U (F#)
            playNote(329.63f, 1000); // G (E)
            playNote(293.66f, 500); // F (D#)
            playNote(277.18f, 500); // D (C#)
            playNote(246.94f, 500); // S (B)
            playNote(220.00f, 500); // Q (A)
            playNote(196.00f, 500); // Z (G)
            playNote(220.00f, 500); // Q (A)
            playNote(246.94f, 1000); // S (B)

            // Section 4 (16 sec)
            playNote(277.18f, 500); // D (C#)
            playNote(246.94f, 500); // S (B)
            playNote(220.00f, 500); // Q (A)
            playNote(196.00f, 500); // Z (G)
            playNote(174.61f, 500); // T (F)
            playNote(196.00f, 500); // Z (G)
            playNote(220.00f, 500); // Q (A)
            playNote(246.94f, 500); // S (B)
            playNote(277.18f, 500); // D (C#)
            playNote(293.66f, 500); // F (D#)
            playNote(329.63f, 500); // G (E)
            playNote(349.23f, 500); // U (F)
            playNote(369.99f, 1000); // U (F#)
            playNote(329.63f, 1000); // G (E)
            playNote(293.66f, 2000); // F (D#)
        }).detach();
    }
    if (ImGui::Button("sample5")) {
        std::thread([this]() {
            // Section 1 (16 sec)
            playNote(220.00f, 500); // Q (A)
            playNote(246.94f, 250); // S (B)
            playNote(277.18f, 750); // D (C#)
            playNote(329.63f, 500); // G (E)
            playNote(293.66f, 250); // F (D#)
            playNote(246.94f, 250); // S (B)
            playNote(220.00f, 1000); // Q (A)
            playNote(196.00f, 500); // Z (G)
            playNote(174.61f, 250); // T (F)
            playNote(196.00f, 250); // Z (G)
            playNote(220.00f, 500); // Q (A)
            playNote(246.94f, 750); // S (B)
            playNote(277.18f, 250); // D (C#)
            playNote(293.66f, 250); // F (D#)
            playNote(329.63f, 500); // G (E)
            playNote(369.99f, 1000); // U (F#)

            // Section 2 (16 sec)
            playNote(392.00f, 250); // H (G#)
            playNote(440.00f, 250); // Y (A)
            playNote(392.00f, 500); // H (G#)
            playNote(369.99f, 500); // U (F#)
            playNote(329.63f, 750); // G (E)
            playNote(293.66f, 250); // F (D#)
            playNote(277.18f, 500); // D (C#)
            playNote(246.94f, 1000); // S (B)
            playNote(220.00f, 500); // Q (A)
            playNote(196.00f, 250); // Z (G)
            playNote(174.61f, 250); // T (F)
            playNote(196.00f, 500); // Z (G)
            playNote(220.00f, 750); // Q (A)
            playNote(246.94f, 250); // S (B)
            playNote(277.18f, 500); // D (C#)
            playNote(293.66f, 1000); // F (D#)

            // Section 3 (16 sec)
            playNote(329.63f, 500); // G (E)
            playNote(349.23f, 500); // U (F)
            playNote(369.99f, 250); // U (F#)
            playNote(392.00f, 250); // H (G#)
            playNote(440.00f, 500); // Y (A)
            playNote(493.88f, 750); // J (B)
            playNote(440.00f, 250); // Y (A)
            playNote(392.00f, 500); // H (G#)
            playNote(369.99f, 250); // U (F#)
            playNote(329.63f, 250); // G (E)
            playNote(293.66f, 500); // F (D#)
            playNote(277.18f, 750); // D (C#)
            playNote(246.94f, 250); // S (B)
            playNote(220.00f, 500); // Q (A)
            playNote(196.00f, 1000); // Z (G)
            playNote(174.61f, 500); // T (F)

            // Section 4 (16 sec)
            playNote(196.00f, 500); // Z (G)
            playNote(220.00f, 250); // Q (A)
            playNote(246.94f, 250); // S (B)
            playNote(277.18f, 500); // D (C#)
            playNote(293.66f, 500); // F (D#)
            playNote(329.63f, 500); // G (E)
            playNote(349.23f, 500); // U (F)
            playNote(369.99f, 1000); // U (F#)
            playNote(392.00f, 500); // H (G#)
            playNote(440.00f, 250); // Y (A)
            playNote(493.88f, 250); // J (B)
            playNote(523.25f, 500); // K (C)
            playNote(493.88f, 750); // J (B)
            playNote(440.00f, 250); // Y (A)
            playNote(392.00f, 500); // H (G#)
            playNote(369.99f, 1000); // U (F#)
        }).detach();
    }
    if (ImGui::Button("sample6")) {
        std::thread([this]() {
            // Section A (60 sec) - Intro / Theme
            playNote(220.00f, 500);  // Q
            playNote(246.94f, 500);  // S
            playNote(277.18f, 500);  // D
            playNote(293.66f, 750);  // F
            playNote(329.63f, 250);  // G
            playNote(293.66f, 500);  // F
            playNote(277.18f, 500);  // D
            playNote(246.94f, 750);  // S
            playNote(220.00f, 500);  // Q
            playNote(196.00f, 500);  // Z
            playNote(174.61f, 1000); // T

            // Repeat with variation
            playNote(220.00f, 500);
            playNote(246.94f, 250);
            playNote(277.18f, 750);
            playNote(329.63f, 500);
            playNote(369.99f, 500);
            playNote(440.00f, 750);  // Y
            playNote(493.88f, 250);  // J
            playNote(440.00f, 500);
            playNote(392.00f, 500);  // H
            playNote(369.99f, 750);
            playNote(329.63f, 500);
            playNote(293.66f, 500);
            playNote(277.18f, 750);
            playNote(246.94f, 250);
            playNote(220.00f, 500);
            playNote(196.00f, 1000);

            // Section B (60 sec) - Development
            playNote(277.18f, 500);
            playNote(329.63f, 500);
            playNote(369.99f, 250);
            playNote(392.00f, 250);
            playNote(440.00f, 500);
            playNote(493.88f, 750);
            playNote(523.25f, 1000);  // K (High C)
            playNote(493.88f, 500);
            playNote(440.00f, 500);
            playNote(392.00f, 750);
            playNote(369.99f, 250);
            playNote(329.63f, 250);
            playNote(293.66f, 500);
            playNote(277.18f, 500);
            playNote(246.94f, 750);
            playNote(220.00f, 1000);

            playNote(196.00f, 500);
            playNote(174.61f, 500);
            playNote(196.00f, 250);
            playNote(220.00f, 250);
            playNote(246.94f, 500);
            playNote(277.18f, 500);
            playNote(293.66f, 750);
            playNote(329.63f, 500);
            playNote(369.99f, 500);
            playNote(392.00f, 1000);

            // Section C (60 sec) - Climax / Variation
            playNote(440.00f, 250);
            playNote(493.88f, 250);
            playNote(523.25f, 500);
            playNote(587.33f, 750);   // L (D)
            playNote(659.26f, 1000);  // M (E)
            playNote(587.33f, 500);
            playNote(523.25f, 500);
            playNote(493.88f, 750);
            playNote(440.00f, 250);
            playNote(392.00f, 250);
            playNote(369.99f, 500);
            playNote(329.63f, 750);
            playNote(293.66f, 1000);
            playNote(277.18f, 500);
            playNote(246.94f, 500);
            playNote(220.00f, 1000);

            playNote(196.00f, 500);
            playNote(174.61f, 750);
            playNote(196.00f, 250);
            playNote(220.00f, 500);
            playNote(246.94f, 500);
            playNote(277.18f, 750);
            playNote(293.66f, 1000);
            playNote(329.63f, 500);
            playNote(369.99f, 500);

            // Section D (60 sec) - Resolution / Outro
            playNote(329.63f, 500);
            playNote(293.66f, 500);
            playNote(277.18f, 750);
            playNote(246.94f, 250);
            playNote(220.00f, 1000);
            playNote(196.00f, 750);
            playNote(174.61f, 500);
            playNote(196.00f, 250);
            playNote(220.00f, 250);
            playNote(246.94f, 500);
            playNote(277.18f, 500);
            playNote(293.66f, 750);
            playNote(329.63f, 1000);
            playNote(369.99f, 500);
            playNote(392.00f, 500);
            playNote(440.00f, 1000);

            playNote(493.88f, 500);
            playNote(440.00f, 500);
            playNote(392.00f, 750);
            playNote(369.99f, 250);
            playNote(329.63f, 250);
            playNote(293.66f, 500);
            playNote(277.18f, 500);
            playNote(246.94f, 1000);
            playNote(220.00f, 1000);
        }).detach();
    }
    ImGui::End();
}