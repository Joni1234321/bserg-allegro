#pragma once

#include "imgui/imgui.h"
#include "imgui/imgui_impl_allegro5.h"

#include "game.h"
#include "camera.h"

#include "ecs/old/helper.h"

#define TESTING

void resizeTestGui() {
    ImGui_ImplAllegro5_InvalidateDeviceObjects();
    ImGui_ImplAllegro5_CreateDeviceObjects();
}

void processTestGuiEvents(ALLEGRO_EVENT* event) {
#ifdef TESTING
    ImGui_ImplAllegro5_ProcessEvent(event);
#endif
}

void createTestGui(ALLEGRO_DISPLAY* display) {
    // IMGUI
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplAllegro5_Init(display);
}

void drawTestGui(Camera& camera, App &game, const Game& logic) {
#ifdef TESTING
    static bool show_demo_window = false;
    static float cameraTestScale = 1.0f;
    static float2 cameraTestPosition;

    // Render
    ImGui_ImplAllegro5_NewFrame();
    ImGui::NewFrame();

    // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
    if (show_demo_window)
        ImGui::ShowDemoWindow(&show_demo_window);

    {
        ImGui::Begin("Testing GUI");
        ImGui::Checkbox("Paused", &game.paused);
        
#if DESIGN == OOP
        for (int i = 0; i < logic.n_teams; i++)
            ImGui::Text("Players on team %d: %d", i, logic.units[i].size());
#else 
        // ecs::getBatch<ecs::UnitBatch>().positionAnimations.size()
        ImGui::Text("Players active: %d", ecs::getBatch<ecs::UnitBatch>().positionAnimations.size());
#endif
        
        
        ImGui::Checkbox("Demo Window", &show_demo_window);
        ImGui::SliderFloat("Camera Scale", &cameraTestScale, 0.2f, 10.0f);            

        if (ImGui::Button("Delete units"))
            DeleteUnits(ecs::getBatch<ecs::UnitBatch>());
        if (ImGui::Button("Spawn Unit"))
            SpawnUnit(ecs::getBatch<ecs::UnitBatch>(), float2(300, 300));
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();
    }

    cameraTestScale = camera.getScale();
    
    ImGui::Render();
    ImGui_ImplAllegro5_RenderDrawData(ImGui::GetDrawData());
#endif
}

void destroyTestGui() {
    ImGui_ImplAllegro5_Shutdown();
    ImGui::DestroyContext();

}