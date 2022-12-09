#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>

#include "app.h"
#include "testing/gui.h"

#include "timer.h"

#define KEY_SEEN     1
#define KEY_RELEASED 2

#define SCALED_WIDTH 1280
#define SCALED_HEIGHT 720
#define TICKS_PER_SECOND 8.0
#define US_PER_TICK 1000000.0 / TICKS_PER_SECOND
#define TICKS_PER_US TICKS_PER_SECOND / 1000000.0

void must_init(bool test, const char* description)
{
    if (test) return;
    printf("couldn't initialize %s\n", description);
    exit(1);
}

// Init
ALLEGRO_FONT* font;
ALLEGRO_DISPLAY* display;
ALLEGRO_TIMER* timer;
ALLEGRO_EVENT_QUEUE* queue;


ALLEGRO_EVENT event;

bool running = true;


void init() {
    // Addons and peripherals
    must_init(al_init(), "allegro");
    must_init(al_install_keyboard(), "keyboard");
    must_init(al_install_mouse(), "mouse");
    must_init(al_init_primitives_addon(), "primitives");
    must_init(al_init_image_addon(), "images");

    // Font
    font = al_create_builtin_font();
    must_init(font, "font");

    // Tick Timer
    timer = al_create_timer(1.0 / TICKS_PER_SECOND);
    must_init(timer, "timer");

    // Display
    al_set_new_display_flags(ALLEGRO_RESIZABLE);
    display = al_create_display(SCALED_WIDTH, SCALED_HEIGHT);
    must_init(display, "display");
    al_set_window_title(display, "BSERG");

    // Event Queue
    queue = al_create_event_queue();
    must_init(queue, "queue");
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_mouse_event_source());

    al_start_timer(timer);
    
    // For input
    memset(UPDATE_INFO.key, 0, sizeof(UPDATE_INFO.key));
    SCREEN_W = SCALED_WIDTH;
    SCREEN_H = SCALED_HEIGHT;

}

void stop() {
    al_destroy_font(font);
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
}

void run() {
    App app(font);

    std::chrono::time_point time = std::chrono::high_resolution_clock::now();

    while (app.running) {
        ALLEGRO_EVENT event;
        // Events
        while (al_get_next_event(queue, &event)) {

            processTestGuiEvents(&event);

            switch (event.type) {
            case ALLEGRO_EVENT_TIMER:
                al_stop_timer(timer);

                time = std::chrono::high_resolution_clock::now();
                app.tick();

                al_start_timer(timer);
                break;


                // Key handling
            case ALLEGRO_EVENT_KEY_DOWN:
                UPDATE_INFO.key[event.keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
                break;
            case ALLEGRO_EVENT_KEY_UP:
                UPDATE_INFO.key[event.keyboard.keycode] &= KEY_RELEASED;
                break;

                // Mouse handling
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN: {
                MOUSE.pressed |= 1 << event.mouse.button;
                MOUSE.x = event.mouse.x;
                MOUSE.y = event.mouse.y;
                app.onMouseDown();
                break;
            }

            case ALLEGRO_EVENT_MOUSE_BUTTON_UP: {
                MOUSE.x = event.mouse.x;
                MOUSE.y = event.mouse.y;
                app.onMouseUp();
                break;
            }


                                              // Display handling
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                running = false;
                break;

            case ALLEGRO_EVENT_DISPLAY_RESIZE:
                al_acknowledge_resize(display);
                SCREEN_W = event.display.width;
                SCREEN_H = event.display.height;
                resizeTestGui();
                break;

            case ALLEGRO_EVENT_MOUSE_AXES:
                MOUSE_SCROLL = event.mouse.dz;
                break;

            default:
                //printf("Event not implemented %d\n", event.type);
                break;
            }
        }

        // Draw
        std::chrono::duration<float> dur = std::chrono::high_resolution_clock::now() - time;
        float t = std::chrono::duration_cast<std::chrono::microseconds>(dur).count() * TICKS_PER_US;


        if (!app.paused) {
            al_set_target_backbuffer(display);
            al_clear_to_color(CL_GRASS_5);

            ALLEGRO_MOUSE_STATE mouse;
            al_get_mouse_state(&mouse);
            MOUSE.down = mouse.buttons;
            MOUSE_X = mouse.x;
            MOUSE_Y = mouse.y;
            
            app.update(t);
        }

        drawTestGui(app.getCamera(), app, app.getGame());

        al_flip_display();

        // Reset keys
        for (int i = 0; i < ALLEGRO_KEY_MAX; i++) UPDATE_INFO.key[i] &= KEY_SEEN;
        MOUSE.pressed = 0;
        MOUSE_SCROLL = 0;
    }
}
int main() {

    init();
    createTestGui(display);
    
    
    run();

    stop();
    destroyTestGui();

    return 0;
    
}

