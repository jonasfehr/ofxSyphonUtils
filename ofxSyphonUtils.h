//
//  ofxSyphonUtils.h
//  WAVE_POV
//
//  Created by Jonas Fehr on 16/01/2017.
//
//
#include "ofxSyphon.h"

#ifndef ofxSyphonUtils_h
#define ofxSyphonUtils_h
class SyphonClientDir : public ofxSyphonClient{
public:
    ofxSyphonServerDirectory dir;
    int dirIdx;
    
    SyphonClientDir(){

    }
    
    void setup(){
        // Setup Syphon in
        dir.setup();
        ofxSyphonClient::setup();
        
        //register for our directory's callbacks
        ofAddListener(dir.events.serverAnnounced, this, &SyphonClientDir::serverAnnounced);
        ofAddListener(dir.events.serverRetired, this, &SyphonClientDir::serverRetired);
        
        dirIdx = -1;
    }
    
    void next(){
        //press any key to move through all available Syphon servers
        if (dir.size() > 0)
        {
            dirIdx++;
            if(dirIdx > dir.size() - 1)
                dirIdx = 0;
            
            set(dir.getDescription(dirIdx));
            string serverName = getServerName();
            string appName = getApplicationName();
            
            if(serverName == ""){
                serverName = "null";
            }
            if(appName == ""){
                appName = "null";
            }
            ofSetWindowTitle(serverName + ":" + appName);
        }
        else
        {
            ofSetWindowTitle("No Server");
        }

    }
    
    void previous(){
        //press any key to move through all available Syphon servers
        if (dir.size() > 0)
        {
            dirIdx--;
            if(dirIdx < 0)
                dirIdx = dir.size() - 1;
            
            set(dir.getDescription(dirIdx));
            string serverName = getServerName();
            string appName = getApplicationName();
            
            if(serverName == ""){
                serverName = "null";
            }
            if(appName == ""){
                appName = "null";
            }
            ofSetWindowTitle(serverName + ":" + appName);
        }
        else
        {
            ofSetWindowTitle("No Server");
        }
        
    }
    
    void find(string appName, string serverName){
        string server_Name;
        string app_Name;
        for( int i = 0; i < dir.size(); i++){
            set(dir.getDescription(i));
            server_Name = getServerName();
            app_Name = getApplicationName();
            if(appName == app_Name && serverName == server_Name){
                dirIdx = i;
                i = dir.size(); // jump out of the loop
                
                if(serverName == ""){
                    serverName = "null";
                }
                if(appName == ""){
                    appName = "null";
                }
                ofSetWindowTitle(serverName + ":" + appName);
            }
        }
    }
    
    void draw(){
        if(dir.isValidIndex(dirIdx)){
            ofSetColor(255);
            ofFill();
            ofxSyphonClient::draw(0, 0);
        }
    }
    
    // Event handlers
    void serverAnnounced(ofxSyphonServerDirectoryEventArgs &arg){
        for( auto& dir : arg.servers ){
            ofLogNotice("ofxSyphonServerDirectory Server Announced")<<" Server Name: "<<dir.serverName <<" | App Name: "<<dir.appName;
        }
        dirIdx = 0;
    };
    void serverRetired(ofxSyphonServerDirectoryEventArgs &arg){
        for( auto& dir : arg.servers ){
            ofLogNotice("ofxSyphonServerDirectory Server Retired")<<" Server Name: "<<dir.serverName <<" | App Name: "<<dir.appName;
        }
        dirIdx = 0;
    };
};


class SyphonFbo : public ofxSyphonServer{
public:
    ofFbo fbo;    
    ofTexture *texture;
    int mode = 0;
    
    SyphonFbo(){
        
    }
    
    void setup(string name, int width, int height){
        fbo.allocate(width, height, GL_RGBA32F_ARB);
        fbo.begin();
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        fbo.end();
        ofxSyphonServer::setName(name);
        
        mode = 0;
    }
    
    void setup(string name, ofTexture *texture){
        this->texture = texture;
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
        ofFill();
        if(mode == 1){
            ofxSyphonServer::publishTexture(texture);
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


#endif /* ofxSyphonUtils_h */
