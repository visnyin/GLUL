#pragma once

#include <GLUL/Config.h>
#include <GLUL/Rectangle.h>

#include <GL/glew.h>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>


namespace GLUL {
    class Window;
}

namespace GL {

    class GLUL_API Context {
        public:
            enum class BufferMask : GLbitfield {
                Color   = GL_COLOR_BUFFER_BIT,
                Depth   = GL_DEPTH_BUFFER_BIT,
                Stencil = GL_STENCIL_BUFFER_BIT,
                Color_Depth   = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT,
                Color_Stencil = GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT,
                Depth_Stencil = GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT,
                Color_Depth_Stencil = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT,
            };

        public:
            Context();
            ~Context();

            void makeActive(GLUL::Window* window);
            void bindWindow(GLUL::Window* window);

            void logErrors(bool flag);

            void clearBuffers(Context::BufferMask mask);

            void enableScissorTest();
            void disableScissorTest();


            void setClearColor(const glm::vec4& data);
            void setClearDepth(const GLclampf value);
            void setClearStencil(const GLint value);

            void setViewport(GLint x, GLint y, GLint width, GLint height);
            void setViewport(const glm::ivec2& position, const glm::ivec2& size);
            void setScissorBox(GLint x, GLint y, GLsizei width, GLsizei height);
            void setScissorBox(const GLUL::Rectangle& scissorBox);

            void setPixelPackAlignment(GLint value);
            void setPixelUnpackAlignment(GLint value);

            bool isScissorTestEnabled() const;

            const glm::vec4& getClearColor() const;
            GLclampf getClearDepth() const;
            GLint getClearStencil() const;

            const glm::ivec2& getViewportSize() const;
            const glm::ivec2& getViewportPosition() const;
            const GLUL::Rectangle& getScissorBox() const;

            GLint getPixelPackAlignment() const;
            GLint getPixelUnpackAlignment() const;

            GLUL::Window* getWindow();


            static void GLAPIENTRY logError(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);

            static Context* Current;
            static Context DefaultContext;

        private:
            void setActive(bool flag);
            bool isActive() const;

            bool _isActive;
            bool _isScissorTestEnabled;

            glm::vec4 _clearColor;
            GLclampf _clearDepth;
            GLint _clearStencil;

            GLint _pixelPackAlignment;
            GLint _pixelUnpackAlignment;

            glm::ivec2 _viewportSize;
            glm::ivec2 _viewportPosition;
            GLUL::Rectangle _scissorBox;

            GLUL::Window* _window;
    };

}
