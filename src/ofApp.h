#pragma once

#include "ofMain.h"
#include "ofxInstagram.h"
#include "ofxJSON.h"
#include "ofxThreadedImageLoader.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void exit();
    
        bool imagesAllocated(deque<ofImage>& images);

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        
    
//        imageAverager averager;
    
    
        float imageHeight;
        float imageWidth;
        int imageCount;
        bool bShowScrubber;
        bool bNewData;
        bool bShowGui;
        bool bImagesAlloc;
        ofxInstagram instagram;
        ofxThreadedImageLoader  getImages;
        deque<ofImage> images;
        ofImage avgImage;
//        unsigned char * pixels;
    
};
