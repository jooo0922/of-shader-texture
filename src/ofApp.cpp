#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // 각 버텍스의 위치 좌표값을 NDC 좌표계를 기준으로 버텍스에 저장함.
    quad.addVertex(glm::vec3(-1.0, -1.0, 0.0));
    quad.addVertex(glm::vec3(-1.0, 1.0, 0.0));
    quad.addVertex(glm::vec3(1.0, 1.0, 0.0));
    quad.addVertex(glm::vec3(1.0, -1.0, 0.0));
    
    // 각 버텍스에 색상데이터도 저장해 줌.
    quad.addColor(ofFloatColor(1.0, 0.0, 0.0, 1.0)); // 빨간색
    quad.addColor(ofFloatColor(0.0, 1.0, 0.0, 1.0)); // 초록색
    quad.addColor(ofFloatColor(0.0, 0.0, 1.0, 1.0)); // 파랑색
    quad.addColor(ofFloatColor(1.0, 1.0, 1.0, 1.0)); // 흰색
    
    // 각 버텍스에 uv좌표 데이터도 저장해 줌. (텍스쳐를 quad 에 씌우기 위해!)
    // uv 좌표계는 NDC 좌표계랑 다르기 때문에 addVertex 에 넣어주는 좌표의 x, y 값이랑은 다를거임!
    quad.addTexCoord(glm::vec2(0.0, 0.0));
    quad.addTexCoord(glm::vec2(0.0, 1.0));
    quad.addTexCoord(glm::vec2(1.0, 1.0));
    quad.addTexCoord(glm::vec2(1.0, 0.0));
    
    // 인덱스 버퍼 배열을 quad 메쉬에 추가해 줌.
    // 즉, 앞서 4개의 버텍스들을 추가했는데, 이 버텍스들을 어떤 순서로 사용해서 메쉬를 그릴 것인지에 대한 데이터 구조를 추가해준 것!
    // 왜냐면, 버텍스 4개를 이용해서 2개의 삼각형을 그려 quad(즉, 사각형 평면)을 그릴 거니까, 삼각형 2개를 4개의 버텍스로 그리려면
    // 몇 개의 버텍스들은 재사용이 되어야하니, 몇번째 버텍스를 몇 번째 순서에 사용할 것인지 인덱스 버퍼로 지정해 준 것임!
    ofIndexType indices[6] = {0, 1, 2, 2, 3, 0};
    quad.addIndices(indices, 6);
    
    // ofShader 객체에 bin/data 폴더에 작성한 셰이더 파일들을 불러와서 로드함.
    // bin/data 디렉토리를 기준으로 한 상대경로이므로, 파일명만 인자로 넣어주면 됨.
    shader.load("vertex.vert", "fragment.frag");
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){ // draw() 는 렌더링루프 함수라고 했지?
    // setup() 함수에서 로드한 셰이더 객체 ofShader 를 바인딩함 (어떤 셰이더를 사용해서 메쉬를 그릴건지 알려주는 작업)
    // 이제 이 아래부터 드로우콜을 호출한 메쉬들은 바인딩된 ofShader 객체의 셰이더로 화면에 렌더링됨.
    shader.begin();
    
    
    // quad 메쉬를 그려달라고 gpu에 지시하는 명령 -> 드로우콜이라고 했지?
    // draw() 및 setup() 함수 모두에 접근하기 위해 ofApp.h 헤더파일에 quad 변수를 선언한 것!
    quad.draw();
    
    // 메쉬를 다 그렸거나, 다른 셰이더를 쓰려면 ofShader.end() 로 현재 바인딩된 셰이더 사용을 중단하는 명령 gpu 에게 내림.
    shader.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
