#version 410

uniform sampler2D parrotTex;
uniform sampler2D checkerboardTex;

in vec2 fragUV;
out vec4 outColor;

void main(){
  vec4 parrot = texture(parrotTex, fragUV);
  vec4 checker = texture(checkerboardTex, fragUV);
  // outColor = mix(parrot, checker, 0.5);

  /*
    이번에는 mix() 함수의 세 번째 인자값을
    checker 텍스쳐의 색상값으로 지정하는 기법을 사용해 볼 것임.

    이 기법은 텍스쳐를 활용한 시각 이펙트를 구현할 때
    정말 많이 사용하는 핵심적인 기법임. 

    유니티 셰이더 스타트업에서도 해당 내용이 중복해서
    나왔을 만큼 많이 사용되고 중요한 기법이므로
    잘 익혀두어야 함.

    지금 현재 체크무늬 텍스쳐의 텍셀값인 checker 는
    흰색 부분이라면 텍셀값이 (1, 1, 1, 1) 일거고,
    검은색 부분이라면 텍셀값이 (0, 0, 0, 1) 이겠지.

    그렇다면, checker.r 값을 mix() 함수의 세 번째 인자,
    즉 섞어주는 비율로 사용한다면 어떻게 될까?

    checker.r 이 1인 부분, 즉, 흰색 부분은
    혼합비율이 1이므로, 두 번째 인자인 parrot 텍셀값이 100% 보일거고,
    checker.r 이 0인 부분, 즉, 검은색 부분은
    혼합비율이 0이므로, 첫 번째 인자인 checker 텍셀값이 100% 보일거임.

    즉, 흰색 부분은 앵무새 텍스쳐가,
    검은색 부분은 검은색 체크무늬 텍스쳐가 보일 것이라는 뜻.

    이런 식으로 특정 노이즈 텍스쳐의 텍셀값을 mix() 함수의
    세 번째 인자로 사용하는 방식으로 다양한 시각효과를 만들어낼 수도 있음.

    그리고, checker.r 이 아니라, g, b 를 사용해도
    동일한 결과가 나오겠지. 왜냐면 체크무늬, 노이즈 텍스쳐 같은
    흑백 텍스쳐들은 r, g, b 채널의 값들이 모두 동일할테니까!
  */
  outColor = mix(checker, parrot, checker.r);
}