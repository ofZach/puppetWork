





#include "testApp.h"







//--------------------------------------------------------------
void testApp::setup(){

    
    puppet.createSquareMesh(ofRectangle(50,50,400,400), 6, 7);
}

//--------------------------------------------------------------
void testApp::update(){

    puppet.update();
}

//--------------------------------------------------------------
void testApp::draw(){
    
    
    //puppet.deformedMesh.drawWireframe();
    
    puppet.draw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
    puppet.mouseDragged(x, y, button);
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
    puppet.mousePressed(x, y, button);
    
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    
    puppet.mouseReleased(x, y, button);;

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}












	



