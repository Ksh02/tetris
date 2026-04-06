1. 클래스 (Class)
class Tetris
* 테트리스 게임 전체를 하나의 객체로 설계
* 데이터와 기능을 하나로 묶음

2. 캡슐화 (Encapsulation)
ptivate:
  GridSquare grid[[GRID_W][GRID_H];
* 데이터(grid, piece 등)를 private으로 보호
* 외부에서 직접 접근 불가능

3. 생성자 (Constructor)
Tetris() { Init();}
* 객체 생성 시 자동으로 초기화 함수 호출
* 코드 간결화

4. 멤버 함수 (Member Function)
void Update();
void Draw();
void Move();
* 클래스 내부에서ㅔ 동작하는 함수들
* 객체 상태를 직접 제어

5. 접근 지정자 (Access Specifier)
private:
public:
* private: 내부 데이터 보호
* public: 외부에서 접근 가능

6. 객체 생성 및 사용
Tetris game;
game.Update();
game.Draw();
* 객체를 생성하여 프로그램 실행
* 함수 호출이 객체 중심으로 이루어짐

7. 열거형 (enum)
enum GridSquare { EMPTY, MOVING, FULL, BLOCK };
* 상태를 의미있는 이름으로 표현
* 코드 가독성 향상

8. 배열을 이용한 자료구조
GridSquare grid[GRID_W][GRID_H];
* 2차원 배열로 게임 맵 구성
* 블럭 상태 저장

9. 함수 재사용성 (Modularity)
* 기능별 함수 분리
* Move()
* Rotate()
* ClearLines()

이번 과제를 통해 C로 작성된 프로그램을 C++의 클래스 기반 구조로 변환하면서 객체지향 프로그래밍의 개념을 직접 적용해볼 수 있었다. 특히 데이터와 기능을 하나의 클래스로 묶는 캡슐화의 중요성을 이해하게 되었고, 코드의 구조가 더 체계적으로 정리되는 것을 느낄 수 있었다. 또한 블록의 이동, 회전, 라인 삭제 기능을 구현하며 게임 로직에 대한 이해도도 높일 수 있었다.
