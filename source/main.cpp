
#include <SDL.h>

#if defined(ANDROID)
#include <SDL_opengles2.h>
#else
#include <SDL_opengl.h>
#endif

#include <cstdio>

int mainLoop();

extern "C" {
    int main(int argc, char* argv[]) {
        return mainLoop();
    }
}

static bool done = false;
static SDL_Window* window = nullptr;
static SDL_GLContext glContext;

static float blinking = 0.0f;

void renderFrame() {
    SDL_GL_MakeCurrent(window, glContext);

    blinking += 0.01f;
    if (blinking > 1.0f) {
        blinking = 0.0f;
    }

    glClearColor(blinking, blinking, blinking, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    SDL_GL_SwapWindow(window);
}

int mainLoop() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
        printf("SDL init failed: %s\n", SDL_GetError());
        SDL_ClearError();
        return 1;
    }

    int width = 640;
    int height = 480;
    Uint32 flags = SDL_WINDOW_OPENGL;
    window = SDL_CreateWindow("SimpleSDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);
    if (window == nullptr) {
        printf("Creating window failed: %s\n", SDL_GetError());
        SDL_ClearError();
        SDL_Quit();
        return 1;
    }

    glContext = SDL_GL_CreateContext(window);
    if (glContext == nullptr) {
        printf("Creating GL context failed: '%s'.\n", SDL_GetError());
        SDL_ClearError();
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    printf("Init done.\n");

    while (!done) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                done = true;
            }
        }

        renderFrame();
        SDL_Delay(2);
    }

    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();

    printf("Quitting.\n");
    return 0;
}
