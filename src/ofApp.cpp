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
    
    // 오픈프레임웍스 레거시 지원을 비활성화함.
    // 참고로, 이 레거시 기능은 uv좌표 대신 스크린 픽셀 좌표를 사용하는 텍스쳐 유형을 기본으로 함. -> 근데 두 좌표계는 서로 방향이나 구조가 다르니 해당 기능을 비활성화해야 함!
    ofDisableArbTex(); // 레거시 기능 비활성화
    img.load("parrot.png"); // ofShader 와 마찬가지로, bin/data 디렉토리를 기준으로 한 상대경로를 받으므로, 해당 디렉토리에 이미지 파일을 저장했다면 파일명만 인자로 넣어주면 됨.
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){ // draw() 는 렌더링루프 함수라고 했지?
    // setup() 함수에서 로드한 셰이더 객체 ofShader 를 바인딩함 (어떤 셰이더를 사용해서 메쉬를 그릴건지 알려주는 작업)
    // 이제 이 아래부터 드로우콜을 호출한 메쉬들은 바인딩된 ofShader 객체의 셰이더로 화면에 렌더링됨.
    shader.begin();
    
    /**
     프래그먼트 셰이더에 텍스쳐 이미지 전송하기
     
     setup() 함수에서 ofImage 객체에 텍스쳐를 로드했다면,
     그 텍스쳐를 사용할 셰이더에게 로드한 텍스쳐를 전달해줘야 함.
     
     이 작업을 해주는 shader 객체 내장 함수가 setUniformTexture() 임.
    
     이걸 호출하면 어떤 일이 발생하냐면,
     1. 인자로 전달받은 ofImage 객체를 ofTexture 객체로 자동 변환함.
     2. 인자로 전달받은 이름을 갖는 유니폼 변수를 프래그먼트 셰이더에서 찾아 텍스처 이미지를 전달해 줌.
     3. 만약, 여러 개의 텍스쳐를 사용할 경우, 인자로 전달받은 텍스쳐 로케이션 값으로 여러 개의 텍스쳐 변수들을 구분해 줌.
     
     참고로, 텍스쳐를 왜 uniform 변수에 담아서 사용하는 이유는,
     프래그먼트 셰이더에서 텍스쳐 샘픞링 작업을 해줄 때,
     각 프래그먼트마다 uv좌표값은 계속 변하지만,
     그 uv좌표값으로 텍셀값을 채취해오는 텍스쳐 자체는 변하지 않음.
     
     따라서 텍스쳐 이미지는 모든 프래그먼트 셰이더에서 동일한 uniform 변수로 받는 것임!
     */
    shader.setUniformTexture("parrotTex", img, 0);
    
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
