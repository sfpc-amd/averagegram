#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    instagram.setup("1700247.32b0b80.919c867a6b794dde8400a32d87339ba5","self");
    instagram.setCertFileLocation(ofToDataPath("ca-bundle.crt",false));

    imageHeight = 640;
    imageWidth = 640;
    imageCount = 20;

    bNewData = false;
    bShowGui = true;
    bImagesAlloc = false;
    
    // @richkidsofinstagram 217946015
    // @dronestagram 241657822
    userId = "self";

    // allocate empty black image
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
            bShowGui = false;
            
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
    ofSetColor(255);

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
        info << "INSTA-AVERAGE" << endl;
        info << "=============" << endl;
        info << endl;
        info << "Press 'h' to show/hide this message." << endl;
        info << "Press 'c' to clear the Images" << endl;
        info << endl;
        info << "Press 's' to get #selfie images" << endl;
        info << "Press 'p' to get popular images" << endl;
        info << "Press 'g' to get local images" << endl;
        info << "Press 'n' to get #nsfw images" << endl;

        info << endl;
        info << "For current user:" << endl;
        info << "Press 'r' to Get Recent Images" << endl;
        info << "Press 'l' to Get Liked Media" << endl;
        info << "Press 'f' to Get Your User Feed" << endl;
        
        info << "Press '1' to set user to @andyinabox" << endl;
        info << "Press '2' to set user to @dronestagram" << endl;
        info << "Press '3' to set user to @richkidsofinstagram" << endl;
        info << "Press '4' to set user to @sfpc_school" << endl;
        info << "Press '5' to set user to @gridpaper" << endl;
       
        ofDrawBitmapStringHighlight(info.str(), ofGetWidth()/4, ofGetHeight()/3);
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
    
    return alloc;
}


void ofApp::updateResults() {
    if (!instagram.getImageURL().empty())
    {
        images.resize(instagram.getImageURL().size());
        bNewData = true;
        bImagesAlloc = false;
        for ( int i = 0; i < instagram.getImageURL().size(); i++)
        {
            getImages.loadFromURL(images[i], instagram.getImageURL()[i]);
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case 'r':
            images.clear();
            instagram.getUserRecentMedia(userId, imageCount);
            updateResults();
            break;
        case 'l':
            images.clear();
            instagram.getUserLikedMedia(userId, imageCount);
            updateResults();
            break;
        case 'f':
            images.clear();
            instagram.getUserFeed(userId, imageCount);
            updateResults();
            break;
        case 's':
            images.clear();
            instagram.getListOfTaggedObjectsNormal("selfie", imageCount);
            updateResults();
            break;
        case 'n':
            images.clear();
            instagram.getListOfTaggedObjectsNormal("nsfw", imageCount);
            updateResults();
            break;
        case 'p':
            images.clear();
            instagram.getPopularMedia();
            updateResults();
            break;
        case 'g':
            images.clear();
            instagram.searchMedia("40.7365685", "-74.0114881");
            updateResults();
            break;
        case 'c':
            images.clear();
            bNewData = true;
            bImagesAlloc = false;
            break;
    // @richkidsofinstagram 217946015
    // @dronestagram 241657822
        case '1':
            userId = "self";
            break;
        case '2':
            userId = "241657822";
            break;
        case '3':
            userId = "217946015";
            break;
        case '4':
            userId = "1766757231";
            break;
        case '5':
            userId = "13826540";
            break;
        case 'h':
            bShowGui = !bShowGui;
            break;
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
