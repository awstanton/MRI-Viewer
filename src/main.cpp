#include <stdio.h>
#include <fstream>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <boost/program_options.hpp>
#include "getVertices.h"
//#include <thread>

// https://github.com/VictorGordan/opengl-tutorials/tree/main/YoutubeOpenGL%206%20-%20Textures


namespace po = boost::program_options;

GLFWwindow* initGLFW()
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL Learning", nullptr, nullptr);

    if (window == nullptr) {
        std::cout << "Failed to create GLFW window\n";
        glfwTerminate();
        exit(-1);
    }

    glfwMakeContextCurrent(window);

//    glewExperimental = GL_TRUE;
    glewInit();

    glViewport(0, 0, 800, 800);

    return window;
}

std::unordered_map<std::string, std::string> getConfig()
{
    std::unordered_map<std::string, std::string> ret;
    std::string vShaderPath, fShaderPath;

    po::options_description desc{"Allowed options"};

    desc.add_options()
    ("vShaderPath", po::value<std::string>()->required(), "path to vertex shader")
    ("fShaderPath", po::value<std::string>()->required(), "path to fragment shader")
    ;

    po::variables_map vm;

    std::ifstream ifs{"config.ini"};

    if (ifs)
        po::store(po::parse_config_file<char>(ifs, desc), vm);
//    notify(vm);

    vShaderPath = vm["vShaderPath"].as<std::string>();
    fShaderPath = vm["fShaderPath"].as<std::string>();
    ret.insert({{"vShaderPath", vShaderPath}, {"fShaderPath", fShaderPath}});

//    std::cout << vm["vShaderPath"].as<std::string>() << "\n";
//    std::cout << vm["fShaderPath"].as<std::string>() << "\n";
    return ret;
}

GLint initShader(GLuint& shader, GLenum shaderType, const char* shaderSource)
{
    std::ifstream sourceStream(shaderSource);
    std::stringstream sourceStringStream;
    sourceStringStream << sourceStream.rdbuf();
    std::string sourceString = sourceStringStream.str();
    const char* source = sourceString.c_str();

    GLint status;


    shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (!status)
    {
        char buffer[512];
        glGetShaderInfoLog(shader, 512, nullptr, buffer);
        std::cout << status << "\n" << buffer << "\n";
    }

    return status;
}

void initShaderProgram(GLuint& shaderProgram, GLuint& vertexShader, GLuint& fragmentShader)
{
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);
}

void cb_exit(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

int main()
{
    std::unordered_map<std::string, std::string> config;
    GLFWwindow* window;
    GLuint vao, vbo, ebo, tex, vertexShader, fragmentShader, shaderProgram;
    GLint posAttrib, colAttrib;

    window = initGLFW();
    config = getConfig();

    // set up shaders
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    initShader(vertexShader, GL_VERTEX_SHADER, config.at("vShaderPath").c_str());
    initShader(fragmentShader, GL_FRAGMENT_SHADER, config.at("fShaderPath").c_str());
    initShaderProgram(shaderProgram, vertexShader, fragmentShader);

    // set vertex data
    GLfloat vertices[] =
    {
        //     COORDINATES     /        COLORS      /   TexCoord  //
        -0.5f, -0.5f, 0.0f,    1.0f, 0.0f, 0.0f,	0.0f, 0.0f, // Lower left corner
        -0.5f,  0.5f, 0.0f,    0.0f, 1.0f, 0.0f,	0.0f, 1.0f, // Upper left corner
        0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,	1.0f, 1.0f, // Upper right corner
        0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,	1.0f, 0.0f  // Lower right corner
    };

    // set vertex order indices
    GLuint indices[] =
    {
        0, 2, 1, // Upper triangle
        0, 3, 2 // Lower triangle
    };

    // generate VAO ID
    glGenVertexArrays(1, &vao);
    // bind VAO
    glBindVertexArray(vao);

    // generate VBO ID
    glGenBuffers(1, &vbo);
    // bind VBO
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // set VBO data
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // generate EBO ID
    glGenBuffers(1, &ebo);
    // bind EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    // set EBO data
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // links VBO attributes to VAO
    // glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // unbind buffer objects to prevent accidental modification
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // get ID for uniform
    GLuint uniID = glGetUniformLocation(shaderProgram, "scale");

    // assign type to texture
    GLenum texType = GL_TEXTURE_2D;

    // assign slot to texture
    GLenum texSlot = GL_TEXTURE0;

    // assign internal format to texture
    GLenum texIntFormat = GL_R16;

    // assign format to texture
    GLenum texFormat = GL_RGBA;

    // assign pixel type to texture
    GLenum pixelType = GL_UNSIGNED_BYTE;

    // get texture data
    Uint16* texData = getVertices();

    for (int i = 0; i < 288 * 288; ++i) {

//        if (texData[i] == 0) {
//            texData[i] = 25;
//        }
        std::cout << texData[i] << " ";
    }

    // get width and height of texture data
    int width = 288, height = 288;

    glGenTextures(1, &tex);
    glActiveTexture(texSlot);
    glBindTexture(texType, tex);

    // configure how the image is made larger or smaller
    glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // configure how image repeats
    glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // assign image to texture object
    glTexImage2D(texType, 0, texIntFormat, width, height, 0, texFormat, pixelType, texData);

    // generate mipmaps
    glGenerateMipmap(texType);

    // delete image from application
    delete texData;

    // unbind texture object to prevent accidental modification
    glBindTexture(texType, 0);

    // get location of uniform
    GLuint texUni = glGetUniformLocation(shaderProgram, "tex0");

    // activate shaderProgram
    glUseProgram(shaderProgram);

    // set value of the uniform
    glUniform1i(texUni, 0);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glUniform1f(uniID, 0.5f);
        glBindTexture(texType, tex);
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        glfwPollEvents();


    }


    glfwDestroyWindow(window);
    glfwTerminate();
}

/*








    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 288 * 288 * 3, vertices, GL_STATIC_DRAW);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(Uint16) * 4 * 3, vertices, GL_STATIC_DRAW);

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    initShader(vertexShader, GL_VERTEX_SHADER, config.at("vShaderPath").c_str());
    initShader(fragmentShader, GL_FRAGMENT_SHADER, config.at("fShaderPath").c_str());
    initShaderProgram(shaderProgram, vertexShader, fragmentShader);

    posAttrib = glGetAttribLocation(shaderProgram, "position");
    colAttrib = glGetAttribLocation(shaderProgram, "color");

    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 3*sizeof(float), 0);
    glVertexAttribPointer(colAttrib, 1, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)(2*sizeof(float)));
    glEnableVertexAttribArray(posAttrib);

    glEnableVertexAttribArray(colAttrib);

    glBindFragDataLocation(shaderProgram, 0, "outColor");

//    uniColor = glGetUniformLocation(shaderProgram, "triangleColor");

//    GLuint vertexBuffer;
//    glGenBuffers(1, &vertexBuffer);
//    printf("%u\n", vertexBuffer);

    glEnable(GL_PROGRAM_POINT_SIZE);


    glfwSetKeyCallback(window, cb_exit);

    while(!glfwWindowShouldClose(window))
    {
        glDrawArrays(GL_POINTS, 0, 288 * 288);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }



*/




