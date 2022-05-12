#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
    // 아래 5줄은 초기의 main() 함수에서 원하는 버전의 OpenGL 을 사용하기 위해 수정해줘야 하는 부분들
    ofGLWindowSettings glSettings;
    glSettings.setSize(1024, 768);
    glSettings.windowMode = OF_WINDOW;
    glSettings.setGLVersion(4, 1);
    ofCreateWindow(glSettings); // 얘는 실행창만 열어주는 것.
    
    // 얘는 ofApp.h 에 선언된 ofApp 객체를 생성해주는 것. -> 그래야 오픈프레임웍스 앱이 실행되니까
	ofRunApp(new ofApp());

}
