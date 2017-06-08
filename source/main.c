
#include <SDL.h>

#if defined(ANDROID)
#include <SDL_opengles2.h>
#else

#include <SDL_opengl.h>

#endif

#if defined(EMSCRIPTEN)
#include <emscripten.h>
#endif

#include <stdio.h>


static int done = 0;
static SDL_Window* window = NULL;
static SDL_GLContext glContext = NULL;

static float blinking = 0.0f;

void blinkerThread(void* data) {
    while (!done) {
        blinking += 0.01f;
        if (blinking > 1.0f) {
            blinking = 0.0f;
        }
        SDL_Delay(10);
    }
}

int init() {
    int width = 640;
    int height = 480;
    Uint32 flags = SDL_WINDOW_OPENGL;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
        printf("SDL init failed: %s\n", SDL_GetError());
        SDL_ClearError();
        return 0;
    }

    window = SDL_CreateWindow("SimpleSDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);
    if (!window) {
        printf("Creating window failed: %s\n", SDL_GetError());
        SDL_ClearError();
        return 0;
    }

    glContext = SDL_GL_CreateContext(window);
    if (!glContext) {
        printf("Creating GL context failed: '%s'.\n", SDL_GetError());
        SDL_ClearError();
        return 0;
    }

    SDL_Thread* thread = SDL_CreateThread(blinkerThread, "blinkerThread", (void*)NULL);
    if (!thread) {
        printf("\nSDL_CreateThread failed: %s\n", SDL_GetError());
        SDL_ClearError();
    }

    printf("Initialized.\n");
    return 1;
}

void release() {
    if (glContext) {
        SDL_GL_DeleteContext(glContext);
        glContext = 0;
    }

    if (window) {
        SDL_DestroyWindow(window);
        window = 0;
    }

    SDL_Quit();
}

void renderFrame() {
    SDL_GL_MakeCurrent(window, glContext);

    glClearColor(blinking, blinking, blinking, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    SDL_GL_SwapWindow(window);
}

void mainLoop() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            done = 1;
        }
    }

    renderFrame();
    SDL_Delay(5);
}

int main(int argc, char* argv[]) {
    if (!init()) {
        printf("Initialization failed.\n");
        release();
        return 1;
    }

#if defined(EMSCRIPTEN)
    emscripten_set_main_loop(mainLoop, 0, 0);
    return 0;
#else
    while (!done) {
        mainLoop();
    }

    release();
    printf("All done.\n");
    return 0;
#endif
}
