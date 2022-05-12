#version 410

// 이전 파이프라인인 버텍스 셰이더에서 out 키워드로 전송해 준 변수명과 동일하게 맞춰줘야,
// gpu 가 두 변수를 연결해줄 수 있음.
in vec4 fragCol; 

// gl_FragColor 는 deprecated 되었고,
// 대신 out 키워드를 사용해서 최종 계산된 프래그먼트 색상값을 할당해서
// 다음 파이프라인으로 넘겨줘야 한다고 했지?
out vec4 outColor;

void main(){
  outColor = fragCol;
}