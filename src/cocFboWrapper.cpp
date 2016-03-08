//
//  cocFboWrapper.cpp
//  Rutherford
//
//  Created by Lukasz Karluk on 8/03/2016.
//
//

#include "cocFboWrapper.h"

namespace coc {
  
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
  
};