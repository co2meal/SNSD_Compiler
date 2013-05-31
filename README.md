SNSD_Compiler
=============

2013 1학기 컴파일러 과제


------

과제 문서

i-lang은 간단한 interpreter형 언어이다. i-lang의 문법은 기본적으로 C언어와 유사하나 몇몇 구문은 차이가 있다. i-lang의 문법에 대해서는 2절에서 자세하게 설명한다. 본 과제에서는 i-lang을 위한 interpreter를 개발한다. 인터프리터는 두 단계로 실행되는데, 일단 단위(문장 또는 함수)별로 코드를 syntax tree로 변경한 후,  즉시 인터프리트하여 그 결과를 보여준다.

과제는 아래와 같이 쉬운 내용부터 점진적으로 복잡한 문법을 포함시켜 나간다. 
  단계 1. 변수, 상수, 지정문, 수식
  단계 2. 제어문(if, while)
  단계 3. 함수를 지원하지만 recursion을 지원하지 않는 경우
  단계 4. recursive function을 지원하는 경우

2. i-lang 언어

i-lang이 지원하는 언어적 요소는 아래와 같다. i-lang은 명시되지 않은 부분은 기본적으로 C언어의 문법을 따른다.

2.1 상수
- 정수형 상수(int)와 실수형 상수(double)를 지원함 
- double은 normal한 형태만 지원해도 됨. 즉, 지수형은 지원하지 않음.

2.2 변수
- 변수는 선언하지 않고 사용한다.
- 변수의 type은 저장되는 값에 의해 결정된다. 실행시 변경도 가능하다.

2.3 수식(expression)과 연산자
- 가감승제 연산자(+,-,*,/)
- 비교 연산 (>, >=, <, <=, ==, !=)
- assignment operator(=)
- 정수, 실수 혼합식은 실수로 형을 변환함

2.4 문장
1) 기본 문장은 수식에 ‘;’를 넣어 문장을 만든다. 단, 하나의 문장이 여러 라인에 걸쳐 있을 수는 있지만, 두개의 문장이 하나의 라인에 놓일 수 없다.
- if 문 
   if ( exp ) 
      statement list
   else
     statement list
   end
- while문
   while ( exp )
     statement list
   end

2.5 함수

- def로 시작하고 end로 끝남
- parameter의 type이나 return type을 명시하지 않음
- parameter passing은 call by value 방식을 사용함
- local variable을 선언할 수 있음
  예, local a, b, c ;

  함수의 정의 예)
  def f(a, b) 
    local max
    if(a > b)
       max = a;
    else
      max = b;
    end
    return max;
  end 
 
3. i-lang 인터프리터의 실행 양식

“?-”는 문장이나 함수를 받아들이는 i-lang 의 인터프리터의 prompt이다.

?- 3;  		<- 수식의 입력
3			<- 결과를 출력
?- 3 * 5;		<- 수식의 입력
15			<- 결과를 출력
?- a = 3;	
3
?- b = a+2;
5
?- a+b;
8
?- if ( a > b )  	<- if의 시작
>    max = a;		<- ‘>’는 보조 prompt, if의 end를 만날때까지 보조 prompt이용
>  else
>    max = b;
> end
if			<- if문의 결과는 if라고 출력 (if문은 수식이 아님)
?- max
5
?- def f(a,b)
>      if(a>b)		<- '>'는 함수의 부분이 입력되고 있음을 나타내는 보조 prompt
>         return a;
>      else
>         return b;
>   end
f defined		<- 함수가 정의되었음을 알려주는 prompt
?- f(3, 5);		<- 함수의 호출
5
?-

4. 조건

1. lex 및 yacc을 이용 (LALR parsing기법을 사용)
2. error 메시지 출력
  lexical error
  syntax error
3. error recovery
  문장단위로 오류를 한정시켜 계속해서 컴파일을 할 수 있도록 한다.
  
5. 보고서 구조
1. 서론
   - 소개, 실제로 구현한 내용 등 기술
2. 분석 및 설계
   - lexical analyzer, parser, interpreter 등에 대한 분석/설계 작업 내용
3. 결과
   - 예제 실행 화면 
4. 결론  
별첨. 소스 코드
   - lex & yacc spec, 기타 program modules

6. 제출방법 및 제출일
   - e-class에 소스코드( .c, .l, .y, .h, input file 등 ) 및 보고서 파일을 압축하여 올릴 것. (파일명: 홍길동-interpreter.zip)
   - 제출일:  2013년 6월 17일(월) (e-class: 자정, 출력본: 수업시간에 제출)
   - 보고서 출력본은 출력하여 6월 17일 오후 6시까지 팔달관705호로 제출
   - 주의: 제출 기일 엄수(delay 없음)
