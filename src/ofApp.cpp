#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    instagram.setup("1700247.32b0b80.919c867a6b794dde8400a32d87339ba5","self");
    instagram.setCertFileLocation(ofToDataPath("ca-bundle.crt",false));
//    instagram.getUserRecentMedia("self");


    bool bNewData = false;
    bool bShowGui = false;

    avgImage.allocate(640, 640, OF_IMAGE_COLOR);
    avgImage.setColor(ofColor(0));
    avgImage.update();

//    averager.startThread(true, true);

}

//--------------------------------------------------------------
void ofApp::update(){
    if (!images.empty() && bNewData) {
//        for (int i = 0; i < images.size(); i++) {
//            ofSetColor(255, 255, 255);
//            if (images[i].isAllocated()) {
//                if(i <= 3) {
//                    images[i].draw(5+(i*255), 5, 250,250);
//                }
//                else if(i >= 4 && i <= 7) {
//                    images[i].draw(5-(4*255)+(i*255), 5+255, 250,250);
//                }
//                else if(i >= 8 && i <= 11) {
//                    images[i].draw(5-(8*255)+(i*255), 5+2*255, 250,250);
//                }
//            }
//        }

        unsigned char * pixels = avgImage.getPixels();
        for(int i = 0; i < 640*640*3; i++) {
            int avg = 0;
            for(int j=0; j < images.size(); j++) {
                if(images[j].isAllocated()) {
                    cout << "IMAGE " << ofToString(j) << " ALLOCATED" << endl;
                    avg += images[j].getPixels()[i];
//                    pixels[i] = images[j].getPixels()[i];
                } else {
                    cout << "IMAGE " << ofToString(j) << " NOT ALLOCATED" << endl;
                }
            }
            
            avg = avg / images.size();
            pixels[i] = avg;
        }
        
//        averager.lock();
//            avgImage = averager.getAverageImage();
//        averager.unlock();
//
        avgImage.update();
     }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    instagram.drawJSON(10);

    ofSetColor(255, 255, 255);
    avgImage.draw(0, 0);


    if(bShowGui) {
        stringstream info;
        info << "Press 'c' to clear the Images" << endl;
        info << "Press 'r' to Get Recent Images" << endl;
        info << "Press 'l' to Get Liked Media" << endl;
        info << "Press 'f' to Get Your User Feed" << endl;
        
        ofDrawBitmapStringHighlight(info.str(), 5,ofGetHeight()-50);
    }
}

void ofApp::exit()
{
    getImages.stopThread();
//    averager.stopThread();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case 'r':
            images.clear();
            images.resize(5);
            // @richkidsofinstagram 217946015
            // @dronestagram 241657822
            instagram.getUserRecentMedia("self", 5);
            if (!instagram.getImageURL().empty())
            {
                bNewData = true;
                for ( int i = 0; i < instagram.getImageURL().size(); i++)
                {
                    getImages.loadFromURL(images[i], instagram.getImageURL()[i]);
                }
//                averager.setImages(images);
            }
            break;
        case 'l':
            images.clear();
            images.resize(12);
            instagram.getUserLikedMedia(12);
            if (!instagram.getImageURL().empty())
            {
                bNewData = true;
                for ( int i = 0; i < instagram.getImageURL().size(); i++)
                {
                    getImages.loadFromURL(images[i], instagram.getImageURL()[i]);
                }
//                averager.setImages(images);
            }
            break;
        case 'f':
            images.clear();
            images.resize(12);
            instagram.getUserFeed(12);
            if (!instagram.getImageURL().empty())
            {
                bNewData = true;
                for ( int i = 0; i < instagram.getImageURL().size(); i++)
                {
                    getImages.loadFromURL(images[i], instagram.getImageURL()[i]);
                }
//                averager.setImages(images);
            }
            break;
        case 'c':
            images.clear();
            break;
        case 'h':
            bShowGui = !bShowGui;
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
