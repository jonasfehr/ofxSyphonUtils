//
//  ofxSyphonClientDir.h
//  texturedlight
//
//  Created by Jonas Fehr on 22/05/2017.
//
//

#pragma once


class ofxSyphonClientDir : public ofxSyphonClient{
public:
    ofxSyphonServerDirectory dir;
    int dirIdx;
    
    ofxSyphonClientDir(){
        
    }
    
    void setup(){
        // Setup Syphon in
        dir.setup();
        ofxSyphonClient::setup();
        
        //register for our directory's callbacks
        ofAddListener(dir.events.serverAnnounced, this, &ofxSyphonClientDir::serverAnnounced);
        ofAddListener(dir.events.serverRetired, this, &ofxSyphonClientDir::serverRetired);
        
        dirIdx = -1;
    }
    
    void setup(string serverName, string appName){
        setup();
        find(serverName, appName);
    }
    
    void next(){
        //press any key to move through all available Syphon servers
        if (dir.size() > 0)
        {
            dirIdx++;
            if(dirIdx > dir.size() - 1)
                dirIdx = 0;
            
            set(dir.getDescription(dirIdx));
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
            
        
        }
        
        //setSyphonAsWindowTitle();
        
    }
    
    void find(string serverName, string appName){

        for( int i = 0; i < dir.size(); i++){
            set(dir.getDescription(i));
            string server_Name = getServerName();
            string app_Name = getApplicationName();
            if(appName == app_Name && serverName == server_Name){
                dirIdx = i;
                i = dir.size(); // jump out of the loop
                set(dir.getDescription(dirIdx));
                ofLogNotice("ofxSyphonServerDirectory found: "+serverName+" | "+appName);
            } else {
                ofLogNotice("ofxSyphonServerDirectory coudn't find: "+serverName+" | "+appName);
            }
        }
    }
    
    void setByIndex(int index){
        if(dirIdx < 0)
            dirIdx = dir.size() - 1;
        
        set(dir.getDescription(dirIdx));
    }
    
    void draw(){
        this->draw(0,0);
    }
    
    void draw(int x, int y){
        if(dir.isValidIndex(dirIdx)){
            ofSetColor(255);
            ofFill();
            ofxSyphonClient::draw(x, y);
        }
    }
    
    void draw(int x, int y, int width, int height){
        if(dir.isValidIndex(dirIdx)){
            ofSetColor(255);
            ofFill();
            ofxSyphonClient::draw(x, y, width, height);
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
    
    string getName(){
        string name = "No Server";
        if (dir.size() > 0)
        {
            
            string serverName = getServerName();
            string appName = getApplicationName();
            
            if(serverName == ""){
                serverName = "null";
            }
            if(appName == ""){
                appName = "null";
            }
            name = serverName + " - " + appName;
        }
        return name;
    };
    
    int getNumOfClients(){
        return dir.size();
    };
};

