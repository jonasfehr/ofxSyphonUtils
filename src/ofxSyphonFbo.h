//
//  ofxSyphonFbo.h
//  texturedlight
//
//  Created by Jonas Fehr on 22/05/2017.
//
//
#pragma once

class ofxSyphonFbo : public ofxSyphonServer{
public:
    ofFbo fbo;
    ofTexture * pTexture;
    int mode = 0;
    
    ofxSyphonFbo(){
        
    }
    
    void setup(string name, int width, int height){
        fbo.allocate(width, height, GL_RGBA32F_ARB);
        fbo.begin();
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        
        fbo.end();
        ofxSyphonServer::setName(name);
        
//        fbo.draw(0,0,0,0); // hack to connect fbo with syphon...
        
        mode = 0;
    }
    
    void setup(string name, ofTexture * pointerTexture){
        this->pTexture = pointerTexture;
        ofxSyphonServer::setName(name);
        
        mode = 1;
    }
    
    
    void draw(){
        fbo.draw(0,0);
    }
    
    void begin(){
        fbo.begin();
    }
    
    void end(){
        fbo.end();
    }
    
    ofTexture getTexture(){
        return fbo.getTexture();
    }
    
    void publish(){
        ofSetColor(255);
        ofFill();
        if(mode == 1){
            ofxSyphonServer::publishTexture(pTexture);
        }else {
            ofxSyphonServer::publishTexture(&fbo.getTexture());
        }
    }
    
    float getWidth(){
        return fbo.getWidth();
    }
    
    float getHeight(){
        return fbo.getHeight();
    }
    
    ofFbo* getFboPtr(){
        return &fbo;
    }
};
