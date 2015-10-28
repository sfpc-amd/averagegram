//
//  imageAverager.h
//  instasum
//
//  Created by Andrew Dayton on 10/23/15.
//
//
#include "ofMain.h"

class imageAverager : public ofThread {
 
    public:
        void setImages(deque<ofImage>& images) {
            lock();
                imageSet = images;
                bNewImage = true;
                average.clear();
                // allocate image from first image in set
                //                average.allocate(imageSet[0].getWidth(), imageSet[0].getHeight(),imageSet[0].getPixelsRef().getImageType() );
                average.allocate(640, 640, OF_IMAGE_COLOR);
            unlock();
        }
    
        ofImage getAverageImage() {
            return average;
        }
    
        // the thread function
        void threadedFunction() {
     
            // start
     
            while(isThreadRunning()) {

                if(bNewImage) {
                    
                    cout << "Update image average" << endl;

                    lock();
                    
                    unsigned char * pixels = average.getPixels();
                    for(int i = 0; i < average.getPixelsRef().size(); i++) {
                        int avg = 0;
                        for(int j=0; j < imageSet.size()-8; j++) {
                            if(imageSet[j].isAllocated()) {
                                avg += int(imageSet[j].getPixels()[i]);
                            }
                        }
                        avg = char(avg / imageSet.size());
                        pixels[i] = avg;
                    }
                    
                    bNewImage = false;
                    
//                    average.update();

                    unlock();
                    

                }
            }
     
        }
   
   

     private:
        deque<ofImage> imageSet;
        ofImage average;
        bool bNewImage;

};