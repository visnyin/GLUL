#include <Utils/Window.h>
#include <Utils/GL+/VertexArray.h>
#include <Utils/GL+/Program.h>

#include <iostream>
#include <vector>

/**
 * Initialize functions
 */
void initVertices(std::vector<glm::vec4>& vertices) {
    vertices.push_back(glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f));
    vertices.push_back(glm::vec4( 0.5f, -0.5f, 0.0f, 1.0f));
    vertices.push_back(glm::vec4( 0.0f,  0.5f, 0.0f, 1.0f));
}

void initProgram(GL::Program& program) {
    program.load(
        GL::Shader("assets/shaders/basic.vs", GL::Shader::Type::VertexShader),
        GL::Shader("assets/shaders/basic.fs", GL::Shader::Type::FragmentShader)
    );
}

void initVBO(GL::VertexBuffer& vbo, std::vector<glm::vec4>& vertices) {
    GL::VertexBuffer::Data vertexData;

    // VertexData
    vertexData.data = &vertices[0]; //pointer to data
    vertexData.size = sizeof(glm::vec4) * vertices.size(); // size of data
    vertexData.pointers.push_back(GL::VertexAttrib(0, 4, GL_FLOAT, 0, 0)); // vertex attributes description

    // VBO settings
    vbo.setTarget(GL::VertexBuffer::Target::Array);
    vbo.setUsage(GL::VertexBuffer::Usage::StaticDraw);
    vbo.bind();
        vbo.setData(vertexData);
    vbo.unbind();
}

void initVAO(GL::VertexArray& vao, const GL::VertexBuffer& vbo, const std::vector<glm::vec4>& vertices) {
    vao.setDrawCount(vertices.size());
    vao.setDrawTarget(GL::VertexArray::DrawTarget::Triangles);

    vao.bind();
        vao.attachVBO(&vbo);
        vao.setAttribPointers();
    vao.unbind();
}

/**
 * Main loop
 */
void run() {
    Util::Window window(800, 600, "Title"); // Window must use create() before creating any GL::* object!
    GL::Program program;
    GL::VertexArray vao;
    GL::VertexBuffer vbo;
    std::vector<glm::vec4> vertices;

    initVertices(vertices);         // initialize vertices for VBO
    initProgram(program);           // load program (vertex shader & fragment shader)
    initVBO(vbo, vertices);         // set-up VBO
    initVAO(vao, vbo, vertices);    // set-up VAO & attach VBO to it

    window.getContext().setClearColor(glm::vec4(0.1f, 0.1, 0.1, 1.0f));

    while(window.isCreated()) {
        window.getContext().clearBuffers(GL::Context::BufferMask::Color);

        program.use();
            vao.bind();
            vao.drawArrays();
            vao.unbind();
        program.unbind();
        
        window.update();
    }
}

/**
 * Start of application
 */
int main() {
    try {
        run();

    } catch(const Util::Exception::FatalError& exception) {
        std::cerr << "Cought fatal error exception:\n" << exception.what() << std::endl;
        return 1;

    } catch(const std::exception& exception) {
        std::cerr << "Cought std::exception:\n" << exception.what() << std::endl;
        return 1;

    } catch(...) {
        std::cerr << "Cought unknown exception!" << std::endl;
        return 1;
    }

    return 0;
}