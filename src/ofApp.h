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
        ofImage img; // bin/data 디렉토리에 저장한 텍스쳐 이미지 파일을 로드 및 프래그먼트 셰이더의 유니폼 변수로 전송하기 위해 헤드파일에 ofImage 객체 변수를 선언함.
        float brightness; // draw() 루프 함수에서 셰이더로 밝기값 조절 유니폼 변수인 brightness 에 값을 전송하기 위해 만든 변수를 헤드파일에 선언함.
};
