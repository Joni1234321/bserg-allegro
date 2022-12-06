# define STOP

#ifndef STOP
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include "math/mathb.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_allegro5.h"


using namespace mathb::types;

void must_init(bool test, const char* description)
{
    if (test) return;

    printf("couldn't initialize %s\n", description);
    exit(1);
}


#define SCALED_WIDTH 1280
#define SCALED_HEIGHT 720

int main()
{

    must_init(al_init(), "allegro");
    must_init(al_install_keyboard(), "keyboard");
    must_init(al_install_mouse(), "mouse");
    must_init(al_init_primitives_addon(), "primitives");


    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0); must_init(timer, "timer");

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue(); must_init(queue, "queue");

    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR | ALLEGRO_VIDEO_BITMAP);


    al_set_new_display_flags(ALLEGRO_RESIZABLE);
    ALLEGRO_DISPLAY* disp = al_create_display(SCALED_WIDTH, SCALED_HEIGHT);
    must_init(disp, "display");
    al_set_window_title(disp, "BSERG");
    

    ALLEGRO_FONT* font = al_create_builtin_font();
    must_init(font, "font");



    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_mouse_event_source());

    bool done = false;
    bool redraw = true;
    ALLEGRO_EVENT event;

    float x, y;
    x = 100;
    y = 100;

    float dx, dy;
    dx = 0;
    dy = 0;


    //al_grab_mouse(disp);

    //al_hide_mouse_cursor(disp);

#define KEY_SEEN     1
#define KEY_RELEASED 2

    unsigned char key[ALLEGRO_KEY_MAX];
    memset(key, 0, sizeof(key));


    // IMGUI
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplAllegro5_Init(disp);

    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);




    al_start_timer(timer);
    while (!done)
    {
        while (al_get_next_event(queue, &event)) {
            ImGui_ImplAllegro5_ProcessEvent(&event);

            switch (event.type)
            {
            case ALLEGRO_EVENT_TIMER:
                // Tick timer
                if (key[ALLEGRO_KEY_ESCAPE])
                    done = true;

                x += dx;
                y += dy;

                if (x < 0)
                {
                    x *= -1;
                    dx *= -1;
                }
                if (x > 640)
                {
                    x -= (x - 640) * 2;
                    dx *= -1;
                }
                if (y < 0)
                {
                    y *= -1;
                    dy *= -1;
                }
                if (y > 480)
                {
                    y -= (y - 480) * 2;
                    dy *= -1;
                }

                dx *= 0.9;
                dy *= 0.9;

                for (int i = 0; i < ALLEGRO_KEY_MAX; i++)
                    key[i] &= KEY_SEEN;

                break;

            case ALLEGRO_EVENT_MOUSE_AXES:
                dx += event.mouse.dx * 0.1;
                dy += event.mouse.dy * 0.1;
                //al_set_mouse_xy(disp, 320, 240);
                break;

            case ALLEGRO_EVENT_KEY_DOWN:
                key[event.keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
                break;
            case ALLEGRO_EVENT_KEY_UP:
                key[event.keyboard.keycode] &= KEY_RELEASED;
                break;

            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;

            case ALLEGRO_EVENT_DISPLAY_RESIZE:
                ImGui_ImplAllegro5_InvalidateDeviceObjects();
                al_acknowledge_resize(disp);
                ImGui_ImplAllegro5_CreateDeviceObjects();
                break;
            }
        }

        // Render
        ImGui_ImplAllegro5_NewFrame();
        ImGui::NewFrame();

        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }

        ImGui::Render();
        al_clear_to_color(al_map_rgba_f(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w));
        ImGui_ImplAllegro5_RenderDrawData(ImGui::GetDrawData());

        al_draw_textf(font, al_map_rgb(255, 255, 255), 0, 0, 0, "X: %.1f Y: %.1f", x, y);
        al_draw_filled_rectangle(x, y, x + 10, y + 10, al_map_rgb(255, 0, 0));

        al_flip_display();
    }

    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);


    ImGui_ImplAllegro5_Shutdown();
    ImGui::DestroyContext();


    return 0;
}

#endif