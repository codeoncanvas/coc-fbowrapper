#pragma once

#include "cinder/gl/Fbo.h"
#include "cinder/Camera.h"


namespace coc {

class FboWrapper {

public:

    FboWrapper();

    void setup( glm::vec2 _size, bool _isOrtho = true, bool _hasAlpha = false );
    void setup( glm::vec2 _size, ci::gl::Fbo::Format _fmt, bool _isOrtho = true );

    void draw();
    void draw( glm::vec2 pos );
    void draw( ci::Rectf bounds );

    void bind();
    void unbind();
    void reset();

    ci::gl::FboRef getFboRef();
    ci::gl::TextureRef getTextureRef();
    bool getIsSetup();

private:

    ci::gl::FboRef      fbo;
    glm::vec2           size;
    ci::CameraOrtho     fboCam;
    bool                isSetup;


};//class FboWrapper

};//namespace coc

