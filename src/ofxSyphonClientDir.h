//
//  ofxSyphonClientDir.h
//  texturedlight
//
//  Created by Jonas Fehr on 22/05/2017.
//
//

#ifndef ofxSyphonClientDir_h
#define ofxSyphonClientDir_h

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

#endif /* ofxSyphonClientDir_h */
