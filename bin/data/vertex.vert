#version 410 // 셰이더 코드는 항상 glsl 버전을 명시하고서 시작해야 함.

// ofApp.cpp 의 setup() 함수에서 위치와 색상, 즉 여러 개의 vertex attribute 를 지정했으므로, layout 으로 받아오는 키워드들의 종류를 구분할 것!
layout(location = 0) in vec3 position;
// layout(location = 1) in vec4 color;
layout(location = 3) in vec2 uv; // setup() 함수에서 추가해 준 uv좌표 데이터를 받아올 변수!

/*
  참고로 layout 으로 vertex attribute 구분할 때,
  location 번호 매기는 방식이 따로 있음.

  오픈프레임웍스에서는 기본적으로
  위치는 0번
  색상은 1번
  노말은 2번
  uv는 3번
  이런 식으로 각 버텍스 속성에 location 번호를 매기고 있음.

  이거는 엔진이나 그래픽 라이브러리마다 조금씩 다를 수 있는데,
  어쨋든 지금 예제에서 사용하는 오픈프레임웍스에서는
  이런 식으로 버텍스 속성들을 구분하기 위해 
  location 번호를 매긴다고 함. 
*/

// out vec4 fragCol; // 버텍스에 지정한 색상데이터를 받아왔으므로, out 키워드를 이용해서 다음 파이프라인인 프래그먼트 셰이더로 넘겨줄 변수를 지정함.
out vec2 fragUV; // 이번에는 uv좌표 데이터를 out 키워드를 이용해 프로그먼트 셰이더로 넘겨줄 변수를 지정함.

void main() {
  gl_Position = vec4(position, 1.0);
  // fragCol = color;
  fragUV = uv;
}