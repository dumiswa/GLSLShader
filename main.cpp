#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "ShaderUtil.h"

int main() {
    sf::Window window(
            sf::VideoMode(800, 600),
            "OpenGL Moving Quads",
            sf::Style::Default,
            sf::ContextSettings(24, 0, 0, 3, 3)
    );

    window.setVerticalSyncEnabled(true);

    GLenum glewResult = glewInit();
    if (glewResult != GLEW_OK) {
        std::cout << "Could not initialize GLEW, byeeee!" << std::endl;
        return -1;
    }

    //load shaders
    GLuint programID = ShaderUtil::createProgram("./../vertexshader.vs", "./../fragmentshader.fs");

    //quad vertices
    const GLfloat vertices[] = {
        //first quad (left side)
        -0.4f, -0.4f, 0.0f,
         0.4f, -0.4f, 0.0f,
         0.4f,  0.4f, 0.0f,
        -0.4f,  0.4f, 0.0f,

        //second quad (right side)
        -0.4f, -0.4f, 0.0f,
         0.4f, -0.4f, 0.0f,
         0.4f,  0.4f, 0.0f,
        -0.4f,  0.4f, 0.0f
    };

    //indices for indexed drawing
    const GLuint indices[] = {
        0, 1, 2, 2, 3, 0,  //first quad
        4, 5, 6, 6, 7, 4   //second quad
    };

    //create VAO
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    //vertex Buffer
    GLuint vertexBufferId;
    glGenBuffers(1, &vertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //element Buffer
    GLuint elementBufferId;
    glGenBuffers(1, &elementBufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //assign vertex attributes
    GLint vertexIndex = glGetAttribLocation(programID, "vertex");
    glEnableVertexAttribArray(vertexIndex);
    glVertexAttribPointer(vertexIndex, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    //disconnect VAO
    glBindVertexArray(0);

    glClearColor(0, 0, 0, 1);

    float speed = 1.0f; //default speed of pattern rotation and scaling
    sf::Clock clock; //timer for animation
    sf::Vector2i mousePosition; //stores mouse position

    while (window.isOpen()) {
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(programID);

        //send common uniforms
        GLint timeLoc = glGetUniformLocation(programID, "u_time");
        glUniform1f(timeLoc, clock.getElapsedTime().asSeconds());

        GLint speedLoc = glGetUniformLocation(programID, "u_speed");
        glUniform1f(speedLoc, speed);

        GLint columnsLoc = glGetUniformLocation(programID, "u_columns");
        GLint rowsLoc = glGetUniformLocation(programID, "u_rows");
        glUniform1i(columnsLoc, 8);
        glUniform1i(rowsLoc, 8);

        //get mouse position and normalize to [0,1] range
        mousePosition = sf::Mouse::getPosition(window);
        float normalizedX = (float)mousePosition.x / 800.0f;
        float normalizedY = 1.0f - ((float)mousePosition.y / 600.0f);
        GLint mouseLoc = glGetUniformLocation(programID, "u_mouse");
        glUniform2f(mouseLoc, normalizedX, normalizedY);

        //computes movement for the first quad (circular path)
        GLint offsetLoc = glGetUniformLocation(programID, "offset");
        GLint patternTypeLoc = glGetUniformLocation(programID, "u_patternType");

        //computes movement for the first quad (counter-clockwise)
        float xOffset1 = 0.6f * cos(clock.getElapsedTime().asSeconds());
        float yOffset1 = 0.6f * sin(clock.getElapsedTime().asSeconds());

        //computes movement for the second quad (clockwise)
        float xOffset2 = -0.6f * cos(clock.getElapsedTime().asSeconds());
        float yOffset2 = -0.6f * sin(clock.getElapsedTime().asSeconds());

        //converts quad positions to screen-space coordinates (0 to 1 range)
        float screenX1 = (xOffset1 + 1.0f) * 0.5f;
        float screenY1 = (yOffset1 + 1.0f) * 0.5f;

        float screenX2 = (xOffset2 + 1.0f) * 0.5f;
        float screenY2 = (yOffset2 + 1.0f) * 0.5f;

        //normalizes the mouse position correctly (Invert Y-axis)
        float normalizedMouseX = (float)mousePosition.x / 800.0f;
        float normalizedMouseY = 1.0f - ((float)mousePosition.y / 600.0f);
        glUniform2f(glGetUniformLocation(programID, "u_mouse"), normalizedMouseX, normalizedMouseY);

        //draws first quad
        glUniform2f(offsetLoc, xOffset1, yOffset1);
        glUniform1i(patternTypeLoc, 0);
        glUniform2f(glGetUniformLocation(programID, "u_quadCenter"), screenX1, screenY1);
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        //draws second quad
        glUniform2f(offsetLoc, xOffset2, yOffset2);
        glUniform1i(patternTypeLoc, 1);
        glUniform2f(glGetUniformLocation(programID, "u_quadCenter"), screenX2, screenY2);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(6 * sizeof(GLuint)));


        glBindVertexArray(0);
        window.display();

        //handle user input
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            if (event.type == sf::Event::Resized) glViewport(0, 0, event.size.width, event.size.height);
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::W) speed += 0.1f;
                if (event.key.code == sf::Keyboard::S) speed -= 0.1f;
            }
        }
    }

    return 0;
}
