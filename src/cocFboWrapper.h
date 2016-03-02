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

FboWrapper::FboWrapper() : isSetup(false) {}

ci::gl::FboRef FboWrapper::getFboRef() { return fbo; }

void FboWrapper::setup( glm::vec2 _size, bool _isOrtho, bool _hasAlpha )
{
    size = _size;
    fbo = ci::gl::Fbo::create( size.x, size.y, _hasAlpha );
    if (_isOrtho) fboCam.setOrtho( 0, size.x, size.y, 0, -1, 1 );
    isSetup = true;
}

void FboWrapper::setup( glm::vec2 _size, ci::gl::Fbo::Format _fmt, bool _isOrtho )
{
    size = _size;
    fbo = ci::gl::Fbo::create( size.x, size.y, _fmt );
    if (_isOrtho) fboCam.setOrtho( 0, size.x, size.y, 0, -1, 1 );
    isSetup = true;
}

void FboWrapper::draw() {
    if (fbo) ci::gl::draw( fbo->getColorTexture());//, fboArea );
}

void FboWrapper::draw( glm::vec2 pos ) {
    if (fbo)
    {
        ci::gl::draw( fbo->getColorTexture(), ci::Rectf( pos.x, pos.y, size.x, size.y ) );
    }
}

void FboWrapper::draw( ci::Rectf bounds ) {
    if (fbo)
    {
        ci::gl::draw( fbo->getColorTexture(), bounds );
    }
}

void FboWrapper::reset() {
    fbo.reset();
    isSetup = false;
}

ci::gl::TextureRef FboWrapper::getTextureRef() {
    return fbo->getColorTexture();
}

void FboWrapper::bind() {
    fbo->bindFramebuffer();
    ci::gl::pushViewport();
    ci::gl::viewport( fbo->getSize() );
    ci::gl::pushMatrices();
    ci::gl::setMatricesWindowPersp( fbo->getSize() );
    ci::gl::setMatrices(fboCam);
}

void FboWrapper::unbind() {
    ci::gl::popMatrices();
    ci::gl::popViewport();
    fbo->unbindFramebuffer();
}

bool FboWrapper::getIsSetup() { return isSetup; }

};//namespace coc

