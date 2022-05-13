#version 410

/*
  ofApp.cpp 의 draw() 함수에서
  setUniformTexture() 에서 지정해줬듯이,
  텍스쳐를 담는 변수인 parrotTex 를 프래그먼트 셰이더의 uniform 변수로 지정해줘야 함.

  이 때, 데이터타입을 sampler2D로 받고 있음.
  glsl 은 여러 종류이 샘플러 타입을 지원하지만,
  그 중 압도적으로 많이 지원하는 게 2D 이미지, 즉 sampler2D 임.
  여기서도 2d 이미지를 받아오는 작업이니 sampler2D 로 지정하는 게 맞겠지.
*/
uniform sampler2D parrotTex;

// 이전 파이프라인인 버텍스 셰이더에서 out 키워드로 전송해 준 변수명과 동일하게 맞춰줘야,
// gpu 가 두 변수를 연결해줄 수 있음.
// in vec4 fragCol; 
in vec2 fragUV; // 버텍스 셰이더에서 out 키워드로 전송해 준 uv좌표 데이터가 담긴 변수명과 동일하게 맞춰줌.

// gl_FragColor 는 deprecated 되었고,
// 대신 out 키워드를 사용해서 최종 계산된 프래그먼트 색상값을 할당해서
// 다음 파이프라인으로 넘겨줘야 한다고 했지?
out vec4 outColor;

void main(){
  // outColor = fragCol;
  // outColor = vec4(fragUV, 0.0, 1.0); // uv좌표는 vec2 값이므로, 프래그먼트 색상값의 r, g 채널만 uv좌표의 u, v값으로 각각 할당해 줌. -> uv좌표값을 색상값으로 할당해서 시각화하여 확인할 수 있도록 한 것!
  
  // texture(샘플러, uv좌표) 함수는 샘플러로부터 uv좌표가 가리키는 위치의 색상값(텍셀값)을 리턴해주는 glsl 내장함수임.
  // 이 내장함수를 이용해서 uv좌표로 유니폼 변수에 담긴 이미지를 텍스쳐 샘플링하는 것임! 
  outColor = texture(parrotTex, fragUV);
}