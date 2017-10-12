
#include <SDL.h>

#if defined(ANDROID)

#include <SDL_opengles2.h>

#else
#include <SDL_opengl.h>
#endif

#if defined(ANDROID)
// Just rerouting printf to logcat on android (not a complete logging solution).
#include <android/log.h>

#define printf(...) __android_log_print(ANDROID_LOG_INFO, "SIMPLE_EXAMPLE", __VA_ARGS__)
#endif

#if defined(EMSCRIPTEN)
#include <emscripten.h>
#endif

#include <stdio.h>


static int done = 0;
static SDL_Window* window = NULL;
static SDL_GLContext glContext = NULL;

static float blinking = 0.0f;
GLuint shader1 = 0;
GLuint shader2 = 0;

typedef struct {
    // Handle to a program object
    GLuint programObject;
} UserData;

///
// Create a shader object, load the shader source, and
// compile the shader.
//
GLuint createShader(const char *shaderSrc, GLenum type) {
    GLuint shader;
    GLint compiled;

    // Create the shader object
    shader = glCreateShader(type);
    if (shader == 0)
        return 0;
    // Load the shader source
    glShaderSource(shader, 1, &shaderSrc, NULL);

    // Compile the shader
    glCompileShader(shader);
    // Check the compile status
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (!compiled) {
        GLint infoLen = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

        if (infoLen > 1) {
            char *infoLog = malloc(sizeof(char) * infoLen);
            glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
            printf("Error compiling shader:\n%s\n", infoLog);
            free(infoLog);
        }
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

///
// Initialize the shader and program object
//
GLuint loadShader(const char* vShaderStr, const char* fShaderStr) {

    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint programObject;
    GLint linked;
    // Load the vertex/fragment shaders
    vertexShader = createShader(vShaderStr, GL_VERTEX_SHADER);
    fragmentShader = createShader(fShaderStr, GL_FRAGMENT_SHADER);
    // Create the program object
    programObject = glCreateProgram();
    if (programObject == 0)
        return 0;
    glAttachShader(programObject, vertexShader);
    glAttachShader(programObject, fragmentShader);
    // Bind vPosition to attribute 0
    glBindAttribLocation(programObject, 0, "vPosition");
    // Link the program
    glLinkProgram(programObject);
    // Check the link status
    glGetProgramiv(programObject, GL_LINK_STATUS, &linked);
    if (!linked) {
        GLint infoLen = 0;
        glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &infoLen);

        if (infoLen > 1) {
            char *infoLog = malloc(sizeof(char) * infoLen);
            glGetProgramInfoLog(programObject, infoLen, NULL, infoLog);
            printf("Error linking program:\n%s\n", infoLog);

            free(infoLog);
        }
        glDeleteProgram(programObject);
        return 0;
    }
    return programObject;
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

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    // Require an alpha channel for testing:
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

    window = SDL_CreateWindow("SimpleSDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width,
                              height, flags);
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

    SDL_DisplayMode mode;
    SDL_GetCurrentDisplayMode(0, &mode);
    printf("Screen bpp: %d\n", SDL_BITSPERPIXEL(mode.format));
    printf("Alpha: %d\n", SDL_ISPIXELFORMAT_ALPHA(mode.format));

    printf("Initialized.\n");

    const char vShaderStr1[] = "#version 100\n"
            "attribute vec4 vPosition; \n"
            "void main() \n"
            "{ \n"
            " gl_Position = vPosition; \n"
            "} \n";

    const char fShaderStr1[] = "#version 100\n"
            "precision mediump float; \n"
            "void main() \n"
            "{ \n"
            " gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0); \n"
            "} \n";

    const char fShaderStr2[] = "#version 100\n"
            "precision mediump float; \n"
            "void main() \n"
            "{ \n"
            " gl_FragColor = vec4(1.0, 0.0, 0.0, 0.3); \n"
            "} \n";

    shader1 = loadShader(vShaderStr1, fShaderStr1);
    shader2 = loadShader(vShaderStr1, fShaderStr2);

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

    blinking += 0.01f;
    if (blinking > 1.0f) {
        blinking = 0.0f;
    }
    // Set the viewport
    glViewport(0, 0, 1200, 1200);

    glClearColor(0.0f, 0.0f, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    glEnable(GL_BLEND);
    glBlendEquation(GL_FUNC_ADD);
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

    glUseProgram(shader1);
    GLfloat vVertices1[] = {0.0f, 0.95f, 0.0f,
                           -0.95f, -0.95f, 0.0f,
                           0.95f, -0.95f, 0.0f};
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices1);
    glEnableVertexAttribArray(0);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glUseProgram(shader2);
    GLfloat vVertices2[] = {0.0f + 0.45f, 0.25f, 0.0f,
                           -0.25f + 0.45f, -0.25f, 0.0f,
                           0.25f + 0.45f, -0.25f, 0.0f};
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices2);
    glEnableVertexAttribArray(0);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    SDL_GL_SwapWindow(window);
}

void mainLoop() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            printf("Event: SDL_QUIT\n");
            done = 1;
        }
    }

    renderFrame();
    SDL_Delay(5);
}

int main(int argc, char *argv[]) {
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
