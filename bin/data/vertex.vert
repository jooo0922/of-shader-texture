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
  // fragUV = uv;

  /*
    그냥 uv좌표 데이터를 날것으로
    프래그먼트 셰이더에 전송해줘버리면, 텍스쳐 샘플링 결과
    뒤집어진 이미지가 렌더링될거임.

    이게 왜 그러냐면,
    OpenGL 은 이미지 데이터가 이미지의 하단부터 저장된다고 가정하지만,
    .png 를 비롯한 대부분의 이미지 파일은 실제로 상단부터 이미지 데이터를 저장하고 있음.

    근데 OpenGL 은 사실 uv좌표계에 맞춰서 좌하단을 (0, 0)으로 시작한 것 밖에는 없음.
    다만 이미지 파일들은 다른 순서로 이미지 데이터를 저장하고 있으므로,
    이럴 땐, uv좌표값 자체를 수직으로 뒤집는 방법이 있음.

    방법은 간단한데,
    그냥 uv.y 컴포넌트 값, 즉, v좌표를
    1에서 뺀 값으로 전달해주면 됨.
    그럼 받아온 uv의 y컴포넌트가 1이면, 전달하는 v좌표는 0이고,
    받아온 y컴포넌트가 0이면 전달하는 v좌표는 1이 되겠지
    -> 이런 식을 uv좌표의 v좌표값 자체를 역순으로 뒤집어줌으로써 

    그러니까 이 뒤집어진 uv좌표값을 통해서 샘플링해오는 텍셀들이
    전부 역순으로 뒤바뀔테니 최종적으로 렌더되는 이미지도 
    제대로 된 방향으로 다시 뒤집어지는 것이지!
  */
  fragUV = vec2(uv.x, 1.0 - uv.y);
}