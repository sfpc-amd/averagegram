#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    instagram.setup("1700247.32b0b80.919c867a6b794dde8400a32d87339ba5","self");
    instagram.setCertFileLocation(ofToDataPath("ca-bundle.crt",false));

    imageHeight = 640;
    imageWidth = 640;
    imageCount = 20;

    bool bNewData = false;
    bool bShowGui = false;
    bool bImagesAlloc = false;

    avgImage.allocate(imageWidth, imageHeight, OF_IMAGE_COLOR);
    avgImage.setColor(ofColor(0));
    avgImage.update();

}

//--------------------------------------------------------------
void ofApp::update(){

    // only update when there is new data
    if(bNewData) {

        // ignore if images are already allocated
        if(!bImagesAlloc) {
            // do the check
            bImagesAlloc = imagesAllocated(images);
        }

        // if allocated, go ahead
        if (bImagesAlloc) {
            cout << "Go!" << endl;
            
            // get the pixels from our source image
            unsigned char * pixels = avgImage.getPixels();
            // get the number of pixels in our source image
            int nPix = imageWidth*imageHeight*3;
            // store our averaged pixel values
            int avg = 0;

            for(int i = 0; i < nPix; i++) {
                avg = 0;
                
                for(int j=0; j < images.size(); j++) {
                
                    avg += images[j].getPixels()[i];
                }
                
                avg = floor(avg / images.size());
                pixels[i] = char(avg);
            }

            avgImage.update();
            bNewData = false;
         }
     }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
//    instagram.drawJSON(10);

    ofSetColor(255, 255, 255);
    
    
    if(bImagesAlloc && bShowScrubber) {
        int i = floor(ofMap(mouseX, ofGetWidth(), 0, 0, images.size()-1, true));
        cout << ofToString(i) << endl;
        images[i].draw(0, 0);
        ofLine(mouseX, 0, mouseX, ofGetHeight());
    } else {
        avgImage.draw(0, 0);
    }

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
}

bool ofApp::imagesAllocated(deque<ofImage>& images){
    bool alloc = false;
    
    if(!images.empty()) {
        alloc = true;
        // counting down -- just a guess but maybe
        // tha later ones in the array will load last?
        for(int i=images.size()-1; i>=0; i--) {
            // if we find an image that isn't allocated,
            // set to false and break out of the loop
            if(!images[i].isAllocated()) {
                alloc = false;
                break;
            }
            
            if(images[i].getWidth() < imageWidth || images[i].getHeight() < imageHeight) {
                images[i].resize(imageWidth, imageHeight);
            }
        }
    }
    
    cout << "Images Allocated? " << ofToString(alloc) << endl;
    
    return alloc;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case 'r':
            images.clear();
            // @richkidsofinstagram 217946015
            // @dronestagram 241657822
            instagram.getUserRecentMedia("self", imageCount);
            if (!instagram.getImageURL().empty())
            {
                images.resize(instagram.getImageURL().size());
                bNewData = true;
                for ( int i = 0; i < instagram.getImageURL().size(); i++)
                {
                    getImages.loadFromURL(images[i], instagram.getImageURL()[i]);
                }
            }
            break;
        case 'l':
            images.clear();
            instagram.getUserLikedMedia(imageCount);
            if (!instagram.getImageURL().empty())
            {
                images.resize(instagram.getImageURL().size());
                bNewData = true;
                for ( int i = 0; i < instagram.getImageURL().size(); i++)
                {
                    getImages.loadFromURL(images[i], instagram.getImageURL()[i]);
                }
            }
            break;
        case 'f':
            images.clear();
            instagram.getUserFeed(imageCount);
            if (!instagram.getImageURL().empty())
            {
                images.resize(instagram.getImageURL().size());
                bNewData = true;
                for ( int i = 0; i < instagram.getImageURL().size(); i++)
                {
                    getImages.loadFromURL(images[i], instagram.getImageURL()[i]);
                }
            }
            break;
        case 's':
            images.clear();
            instagram.getListOfTaggedObjectsNormal("selfie", imageCount);
            if (!instagram.getImageURL().empty())
            {
                images.resize(instagram.getImageURL().size());
                bNewData = true;
                for ( int i = 0; i < instagram.getImageURL().size(); i++)
                {
                    getImages.loadFromURL(images[i], instagram.getImageURL()[i]);
                }
            }
            break;
        case 'p':
            images.clear();
            instagram.getPopularMedia();
            if (!instagram.getImageURL().empty())
            {
                images.resize(instagram.getImageURL().size());
                bNewData = true;
                for ( int i = 0; i < instagram.getImageURL().size(); i++)
                {
                    getImages.loadFromURL(images[i], instagram.getImageURL()[i]);
                }
            }
            break;
        case 'g':
            images.clear();
            instagram.searchMedia("40.7365685", "-74.0114881");
            if (!instagram.getImageURL().empty())
            {
                images.resize(instagram.getImageURL().size());
                bNewData = true;
                for ( int i = 0; i < instagram.getImageURL().size(); i++)
                {
                    getImages.loadFromURL(images[i], instagram.getImageURL()[i]);
                }
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
    bShowScrubber = true;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    bShowScrubber = false;
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
