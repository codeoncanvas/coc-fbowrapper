#pragma once

#include "cinder/gl/Fbo.h"
#include "cinder/Camera.h"

using namespace ci;

namespace coc {
    class FboWrapper {

    public:

        gl::FboRef  fbo;
        Area        fboArea;
        CameraOrtho fboCam;
        bool        isInit;


        FboWrapper() : isInit(false) {}

        gl::FboRef getRef() { return fbo; }

        void setup( Area _fboArea, bool _isOrtho = true, bool _hasAlpha = false )
        {
            fboArea = _fboArea;
            fbo = gl::Fbo::create( fboArea.getWidth(), fboArea.getHeight(), _hasAlpha );
            if (_isOrtho) fboCam.setOrtho( 0, fboArea.getWidth(), fboArea.getHeight(), 0, -1, 1 );
            isInit = true;
        }

        void setup( Area _fboArea, gl::Fbo::Format _fmt, bool _isOrtho = true )
        {
            fboArea = _fboArea;
            fbo = gl::Fbo::create( fboArea.getWidth(), fboArea.getHeight(), _fmt );
            if (_isOrtho) fboCam.setOrtho( 0, fboArea.getWidth(), fboArea.getHeight(), 0, -1, 1 );
            isInit = true;
        }

        void draw() {
            if (fbo) gl::draw( fbo->getColorTexture());//, fboArea );
        }

        void draw( vec2 pos ) {
            if (fbo)
            {
                gl::draw( fbo->getColorTexture(), Rectf( pos.x, pos.y, fboArea.getWidth(), fboArea.getHeight() ) );
            }
        }

        void draw( Rectf bounds ) {
            if (fbo)
            {
                gl::draw( fbo->getColorTexture(), bounds );
            }
        }

        void reset() {
            fbo.reset();
            isInit = false;
        }

        gl::TextureRef getTextureRef() {
            return fbo->getColorTexture();
        }

        void bind() {
            fbo->bindFramebuffer();
            gl::pushViewport();
            gl::viewport( fbo->getSize() );
            gl::pushMatrices();
            gl::setMatricesWindowPersp( fbo->getSize() );
            gl::setMatrices(fboCam);
        }

        void unbind() {
            gl::popMatrices();
            gl::popViewport();
            fbo->unbindFramebuffer();
        }

        bool getInit() { return isInit; }


    };//class FboWrapper
};//namespace coc

