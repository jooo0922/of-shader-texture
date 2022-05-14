#version 410

uniform sampler2D parrotTex; // 오픈프레임웍스의 draw() 루프에서 전송해 준 텍스쳐 이미지를 저장할 유니폼 변수

uniform vec4 multiply; // 색상 연산 중 곱셈 연산에 사용할 vec4 유니폼 변수
uniform vec4 add; // 색상 연산 중 덧셈 및 뺄셈 연산에 사용할 vec4 유니폼 변수

in vec2 fragUV; // 버텍스 셰이더에서 out 키워드로 전송해 준 uv좌표 데이터(각 프래그먼트마다 보간되서 넘어옴)
out vec4 outColor; // 결과값으로 계산된 프래그먼트 색상을 다음 파이프라인으러 넘겨주는 변수

void main(){
  /*
    앵무새 텍스쳐로부터 보간된 uv좌표값을 이용해 샘플링해온 텍셀값에
    특정 색상값(vec4) 를 덧셈/뺄셈 하거나 곱셈해주는 색상연산을 수행함.

    이 때, 연산의 순서가 중요한데,
    셰이더 코드에서 주로 볼 수 있는 최적화기법 중 하나로,
    
    모든 GPU 에서 처리하는 연산은
    곱한 다음 더한다(multiply, then add) 를 의미하는
    MAD 연산의 순서대로 해주는 게 좋음.

    gpu의 MAD 명령어는, 곱한 뒤 더하는 연산을
    한번에 처리할 수 있게 해주는데,

    지금 그 명령어를 사용하고 있지는 않으니
    가급적 이 순서를 지켜서 색상연산을 해주는 게 좋음.
  */
  outColor = texture(parrotTex, fragUV) * multiply + add;
}