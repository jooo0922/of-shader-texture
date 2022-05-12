#version 410 // 셰이더 코드는 항상 glsl 버전을 명시하고서 시작해야 함.

// ofApp.cpp 의 setup() 함수에서 위치와 색상, 즉 여러 개의 vertex attribute 를 지정했으므로, layout 으로 받아오는 키워드들의 종류를 구분할 것!
layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;

out vec4 fragCol; // 버텍스에 지정한 색상데이터를 받아왔으므로, out 키워드를 이용해서 다음 파이프라인인 프래그먼트 셰이더로 넘겨줄 변수를 지정함.

void main() {
  gl_Position = vec4(position, 1.0);
  fragCol = color;
}