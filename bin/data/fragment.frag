#version 410

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
  outColor = vec4(fragUV, 0.0, 1.0); // uv좌표는 vec2 값이므로, 프래그먼트 색상값의 r, g 채널만 uv좌표의 u, v값으로 각각 할당해 줌. -> uv좌표값을 색상값으로 할당해서 시각화하여 확인할 수 있도록 한 것!
}