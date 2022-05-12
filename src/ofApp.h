#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
        ofMesh quad; // ofApp의 draw() 함수에서도 quad 에 접근하려고 헤더파일에 해당 변수를 선언함.
        ofShader shader; // bin/data 디렉토리에서 작성한 셰이더 파일을 로드 및 바인딩하기 위해 헤드파일에 셰이더 객체 변수를 선언함.
};
