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
    shader.load("vertex.vert", "blendTextures.frag");
    
    // 오픈프레임웍스 레거시 지원을 비활성화함.
    // 참고로, 이 레거시 기능은 uv좌표 대신 스크린 픽셀 좌표를 사용하는 텍스쳐 유형을 기본으로 함. -> 근데 두 좌표계는 서로 방향이나 구조가 다르니 해당 기능을 비활성화해야 함!
    ofDisableArbTex(); // 레거시 기능 비활성화
    parrotImg.load("parrot.png"); // ofShader 와 마찬가지로, bin/data 디렉토리를 기준으로 한 상대경로를 받으므로, 해당 디렉토리에 이미지 파일을 저장했다면 파일명만 인자로 넣어주면 됨.
    checkerImg.load("checker.jpeg"); // 텍스쳐 혼합에 사용할 두 번째 텍스쳐인 체크무늬 텍스쳐도 마찬가지로 bin/data 경로에 저장해두고, 파일명만 인자로 넣어서 로드해주면 됨.
    
    /**
     scrolling_uv.vert 라는 버텍스 셰이더 코드에서
     0.0 ~ 1.0 사이의 유효범위를 벗어나는 uv좌표값을 전달하도록 처리해줬을 때,
     gpu 는 기본적으로 '고정 랩 모드(clamp)' 로 텍스쳐 샘플링을 처리해줬음.
     
     그러나, 여기서 만들고자 하는 것은 광고판처럼 움직이는 텍스쳐 스크롤링을 구현하고 싶은거임.
     그렇다면, 0.0 ~ 1.0 사이를 넘어가는 텍스쳐 좌표에 대해서 '반복 랩 모드(repeat)' 처리를 해줘야 함!
     
     즉, (1.25, 0.0) 라는 uv좌표로 텍스쳐 샘플링을 시도한다면,
     gpu는 이 uv좌표를 (0.25, 0.0) 으로 변환해서 텍스쳐 샘플링을 해줘야 한다는 뜻임.
     이렇게 돼야 0.0 ~ 1.0 사이의 uv좌표로 동일한 텍셀값을 반복해서 샘플링해올 수 있으니까!
     
     이거를 설정해주려면 오픈프레임웍스의 ofImage 객체에서,
     로드한 텍스쳐를 가져오는 ofImage.getTexture() 를 먼저 호출하고,
     여기서 .setTextureWrap(가로방향 랩모드, 세로방향 랩모드) 로 설정해주면 됨.
     
     위에서 말한 것처럼 '반복 랩 모드' 를 지정하고 싶다면, GL_REPEAT,
     '고정 랩 모드'를 지정하고 싶다면, GL_CLAMP 로 지정해주면 되고,
     방향마다 텍스쳐 샘플리 처리 모드를 다르게 지정해줄 수 있음.
     
     이때, 눈여겨볼 만한 사항은,
     draw() 함수에서는 프래그먼트 셰이더의 유니폼 변수에 텍스쳐 이미지를 전달해줄 때,
     shader.setUniformTexture(유니폼변수명, ofImage, 로케이션 번호) 이런 식으로
     ofImage 객체 자체를 바로 인자로 전달해서 ofTexture 객체로 자동변환해줬다면,
     
     이렇게 텍스쳐의 랩모드를 설정할 때에는
     텍스쳐를 직접 수정해줘야 하므로, getTexture() 함수로 ofTexture 객체를
     직접 가져와서 사용했다는 점!
     */
    parrotImg.getTexture().setTextureWrap(GL_REPEAT, GL_REPEAT);
    checkerImg.getTexture().setTextureWrap(GL_REPEAT, GL_REPEAT); // 텍스쳐 혼합을 위해 추가한 두 번째 텍스쳐인 체크무늬 텍스쳐도 랩 모드를 '랩 반복 모드' 로 지정해 줌.
    
    /**
     아래와 같이 brightness 값을 0.5 로 줄 경우,
     또는 1보다 작은 값으로 할당할 경우,
     우리가 예상하는 화면의 모습은 기존 앵무새 텍스쳐 이미지보다
     훨씬 어둡게 나와야 하는 게 정상이지.
     
     왜냐면, 밝기값을 조절하는 brightness 변수는
     값이 0에 가까울수록 그 값을 텍셀값에 곱한 결과가 (0, 0, 0, 0) 에 가까워질테니,
     텍스쳐 색상도 검정색에 가까워야 하잖아.
     
     그런데, 예상과 다르게 화면이 회색빛이 비춰지면서 나온다는 것.
     
     왜냐? brightness 는 r, g, b 뿐만 아니라, a, 즉 알파채널에도 곱해지므로,
     값이 0에 가까울수록 알파값도 0에 가까워짐.
     
     이 말은, 해당 색상값의 투명도도 0에 가까워진다는 소리이기 때문에
     brightness 가 0에 가까워지면 결과적으로 앵무새 텍스쳐의 투명도도 0에 가까워져서
     텍스쳐 밑에 있는 실행창의 기본색인 회색이 더 잘 비춰지게 되고,
     
     그래서 화면이 어두워지기 보다는 회색에 가까운 때깔이 나오게 된다는 것.
     
     이는 오픈프레임웍스가 기본적으로
     '알파 블렌딩' 기능을 활성화하기 때문임.
     그래서 알파채널 값이 바뀌면 바뀐 그대로 적용하려고 하기 때문에
     순전히 r, g, b 값의 일률적인 변화에 의한 밝기 변화를 관찰하기 어려운 것.
     
     이럴 경우, ofDisableAlphaBlending() 라는 오픈프레임웍스 함수를 호출해서
     '알파 블렌딩' 기능을 비활성화하면 됨.
     */
    ofDisableAlphaBlending();
    brightness = 1.0;
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
    shader.setUniformTexture("parrotTex", parrotImg, 0);
    
    // 앵무새 텍스쳐와 동일한 방식으로 체크무늬 텍스쳐도 셰이더의 해당 유니폼 변수에 전송해 줌.
    // 이때, 서로 다른 두 개의 텍스쳐를 하나의 셰이더에서 사용하고 있기 때문에, 마지막 인자인 텍스쳐 로케이션값을 다르게 전달해줘야
    // 각 텍스쳐를 서로 다른 텍스쳐 로케이션에 배정할 수 있음.
    shader.setUniformTexture("checkerboardTex", checkerImg, 1);
    
    /**
     scroll_uv.vert 파일에서 설명해놓았듯이,
     cpp 단 언어에서, 즉 오픈프레임웍스 함수를 통해서
     변화하는 시간값을 셰이더에 전송해줘야 함.
     
     ofGetElapsedTimef() 는 프로그램 실행 이후
     경과된 초단위의 시간값을 리턴해주는 오픈프레임웍스 함수임.
     
     이 함수로 리턴받은 경과된 시간값을
     setUniform1f() 함수를 이용해서
     버텍스 셰이더에 선언해놓은 'time' 이라는 유니폼 변수에
     매 프레임마다 전송해주는 원리인 것이지.
     
     또, time 유니폼 변수는 데이터 타입이 float 1개 이기 때문에
     setUniform1f 를 사용하는 것임,
     
     이처럼, 경과된 시간값을 셰이더로 쏴줘서
     시간에 따라 uv좌표를 조작하는 기법은 수많은 이펙트 셰이더의
     기본 기법이므로 잘 알아두는 게 좋음.
     */
    shader.setUniform1f("time", ofGetElapsedTimef());
    
    /**
     텍스쳐로부터 샘플링해온 텍셀값의
     r, g, b, a 각 채널에 동일하게 곱해주는 밝기 조절용 값으로 사용할
     brightness 의 값을 setup() 함수에서 할당한 뒤,
     
     draw() 루프 함수에서 shader의 유니폼 변수 brightness 에
     전송해주는 것임.
     */
    shader.setUniform1f("brightness", brightness);
    
    
    /**
     아래부터 작성한 코드들은
     프래그먼트 셰이더에서 벡터에 기반한 색상 연산을 하기 위해
     
     텍셀값에 더해줄 vec4 유니폼 변수인 add 와
     텍셀값에 곱해줄 vec4 유니폼 변수인 multiply 에
     각각 전송해 줄 glm vec4 값을 setUniform4f() 함수로 쏴주는 거임.
     
     현재 colormath.frag 프래그먼트 셰이더에서는
     곱한 다음 더해주는 MAD 연산 순서에 따라 텍셀값에 두 유니폼 변수를
     모두 연산해주고 있기 때문에
     
     특정 색상값 벡터를 더해줄 것인지 곱해줄 것인지에 따라
     연산 방식이 달라짐.
     
     빼거나 더하고자 한다면, multiply 변수를 (1, 1, 1, 1) 로 전송해서
     곱셈 연산의 영향이 없도록 하고,
     
     곱하고자 한다면, add 변수를 (0, 0, 0, 0) 로 전송해서
     덧셈 연산의 영향이 없도록 코드를 작성했음.
     */
    // 회색을 뺄 때
//    shader.setUniform4f("multiply", glm::vec4(1.0, 1.0, 1.0, 1.0));
//    shader.setUniform4f("add", glm::vec4(-0.5, -0.5, -0.5, -1.0));
    
    // 회색을 더할 때
//    shader.setUniform4f("multiply", glm::vec4(1.0, 1.0, 1.0, 1.0));
//    shader.setUniform4f("add", glm::vec4(0.5, 0.5, 0.5, 1.0));
    
    // 파랑색을 더할 때
//    shader.setUniform4f("multiply", glm::vec4(1.0, 1.0, 1.0, 1.0));
//    shader.setUniform4f("add", glm::vec4(0.25, 0.25, 1.0, 1.0));
    
    // 빨강색을 더할 때
//    shader.setUniform4f("multiply", glm::vec4(1.0, 1.0, 1.0, 1.0));
//    shader.setUniform4f("add", glm::vec4(1.0, 0.0, 0.0, 1.0));
    
    // -회색을 곱할 때
//    shader.setUniform4f("multiply", glm::vec4(-0.5, -0.5, -0.5, -1.0));
//    shader.setUniform4f("add", glm::vec4(0.0, 0.0, 0.0, 0.0));
    
    // 그냥 회색을 곱할 때
//    shader.setUniform4f("multiply", glm::vec4(0.5, 0.5, 0.5, 1.0));
//    shader.setUniform4f("add", glm::vec4(0.0, 0.0, 0.0, 0.0));
    
    // 파랑색을 곱할 때
//    shader.setUniform4f("multiply", glm::vec4(0.25, 0.25, 1.0, 1.0));
//    shader.setUniform4f("add", glm::vec4(0.0, 0.0, 0.0, 0.0));
    
    // 빨강색을 곱할 때
//    shader.setUniform4f("multiply", glm::vec4(1.0, 0.0, 0.0, 1.0));
//    shader.setUniform4f("add", glm::vec4(0.0, 0.0, 0.0, 0.0));

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
