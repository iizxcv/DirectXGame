# C++ 3D 게임 튜토리얼 시리즈 - 에피소드 2: 그래픽스 엔진과 DirectX 11

이 문서는 C++와 DirectX 11을 사용하여 3D 게임 엔진을 구축하는 튜토리얼 시리즈의 두 번째 에피소드 내용을 요약합니다. 주요 목표는 3D 그래픽을 렌더링할 수 있는 그래픽스 엔진의 기초를 다지는 것입니다.

## 1. 학습 목표

- DirectX 11 API를 사용하여 3D 그래픽스 엔진을 생성합니다.
- 엔진의 핵심 컴포넌트와 아키텍처를 설계합니다.
- 의존성 주입(Dependency Injection)과 같은 주요 디자인 패턴을 적용합니다.
- C++의 "Rule of Five" 개념을 이해하고 적용합니다.

## 2. 개발 환경 요구사항

- **C++ IDE**: Visual Studio 2022 Community
- **플랫폼**: Windows
- **그래픽스 API**: DirectX 11
- **사전 지식**: C++ 프로그래밍 언어에 대한 깊은 이해

## 3. 엔진 아키텍처 및 설계

### 3.1. DX3D 게임 엔진 구조

엔진은 여러 하위 시스템으로 구성된 모듈식 구조를 가집니다.

- **`Game`**: 엔진의 주 진입점(Entry Point)으로, 여러 하위 시스템을 관리하고 조정합니다.
- **`Window`**: 게임 윈도우의 생성 및 관리를 담당합니다.
- **`GraphicsEngine`**: 게임 엔진의 렌더링 계층을 제공하는 하위 시스템입니다.
- **`RenderSystem`**: `GraphicsEngine` 내에서 DirectX 11과 같은 그래픽스 API의 초기화 및 리소스 관리를 전담하는 컴포넌트입니다.

### 3.2. 로거(Logger) 모듈

- 정보, 경고, 오류 메시지를 콘솔에 일관된 형식으로 출력하는 중앙 집중식 로깅 시스템입니다.
- 디버깅과 엔진 동작 모니터링에 필수적이며, 여러 상세도 레벨(Verbosity Level)을 지원합니다.

### 3.3. 디자인 패턴

- **의존성 주입 (Dependency Injection)**: 싱글톤(Singleton) 패턴의 단점을 피하고 클래스 간의 결합도를 낮추기 위해 사용합니다. 외부에서 의존성을 주입받는 **생성자 주입(Constructor Injection)** 방식을 채택합니다.
- **의존성 집합 (Dependency Aggregation)**: 여러 의존성을 하나의 구조체(Descriptor)로 묶어 생성자에 전달함으로써, 생성자 파라미터가 많아지는 것을 방지하고 코드를 깔끔하게 유지합니다.

## 4. C++ 핵심 개념: Rule of Five

- **문제**: 클래스의 얕은 복사(Shallow Copy)는 리소스(예: 윈도우 핸들)를 여러 객체가 공유하게 만들어 이중 해제와 같은 문제를 일으킬 수 있습니다.
- **해결책**: 리소스를 직접 관리하는 클래스에 "Rule of Five"를 적용하여 복사 및 이동을 제어합니다.
- **구현**: `Base` 클래스에서 다음 5가지 특별 멤버 함수를 `= delete`로 명시하여 복사와 이동을 금지합니다.
  1.  소멸자 (Destructor)
  2.  복사 생성자 (Copy Constructor)
  3.  이동 생성자 (Move Constructor)
  4.  복사 대입 연산자 (Copy Assignment Operator)
  5.  이동 대입 연산자 (Move Assignment Operator)
- **결과**: `Base`를 상속하는 모든 클래스는 복사/이동이 불가능해져 리소스의 단일 소유권을 보장합니다.

## 5. 구현 단계

### 5.1. `GraphicsEngine` 및 `RenderSystem` 클래스 생성

- `Base` 클래스를 상속하고, 추가 상속을 막기 위해 `final` 키워드를 사용합니다.
- `RenderSystem`의 소스 파일은 DirectX 헤더가 외부에 노출되지 않도록 엔진 내부에 캡슐화합니다.

### 5.2. DirectX 11 통합

1.  **링커 설정**: 프로젝트 속성에서 `D3D11.lib` 라이브러리를 추가합니다.
2.  **헤더 포함**: `RenderSystem.cpp`에 `<d3d11.h>`를 포함합니다.
3.  **디바이스 생성**: `D3D11CreateDevice` 함수를 호출하여 D3D11 디바이스(가상 GPU)와 디바이스 컨텍스트를 생성합니다.
4.  **리소스 관리**: DirectX의 COM 객체는 참조 카운팅(Reference Counting)으로 관리되므로, `Microsoft::WRL::ComPtr` 스마트 포인터를 사용하여 메모리를 안전하게 자동 관리합니다.

### 5.3. `Logger` 클래스 생성

- `LogLevel` 열거형(`Information`, `Warning`, `Error`)을 정의합니다.
- 특별한 리소스를 관리하지 않으므로 "Rule of Zero"를 따릅니다. (특별 멤버 함수를 작성하지 않음)
- `log` 메서드는 설정된 로그 레벨에 따라 `std::clog`를 통해 메시지를 출력합니다.

### 5.4. 의존성 주입 적용

1.  **Descriptor 구조체 생성**: `Common.h` 파일에 `Logger&`를 포함하는 `BaseDescriptor`를 정의합니다. 다른 클래스들(`Window`, `GraphicsEngine` 등)을 위한 Descriptor는 이 `BaseDescriptor`를 상속받아 확장합니다.
2.  **생성자 수정**: 모든 주요 클래스의 생성자가 각각의 Descriptor를 참조(`&`)로 받도록 수정하고, 이를 통해 `Base` 클래스에 `Logger` 의존성을 전달합니다.
3.  **`Game` 클래스에서의 관리**: `Game` 클래스에서 `Logger`의 유일한 인스턴스를 `std::unique_ptr`로 생성 및 소유합니다. 다른 컴포넌트를 생성할 때 이 `Logger`의 참조를 주입합니다.

## 6. 디버깅 및 검증

- `D3D11CreateDevice` 함수 호출이 성공하는지 확인합니다.
- 프로그램 종료 시 출력 창에서 GPU 드라이버 관련 DLL이 언로드되는 것을 보고 DirectX 리소스가 정상적으로 해제되었음을 간접적으로 확인합니다.
- `D3D11CreateDevice`에 의도적으로 잘못된 값을 전달하여 로거가 오류 메시지를 정상적으로 출력하는지 테스트합니다.
- 로그 레벨(`Information`, `Error`)을 변경하며 메시지 필터링이 올바르게 동작하는지 확인합니다.

## 7. 결론

- DirectX 11 API의 초기화를 완료하고 `GraphicsEngine` 및 `RenderSystem`의 기초를 마련했습니다.
- 의존성 주입 패턴을 사용하여 확장 가능하고 유지보수하기 좋은 `Logger` 시스템을 통합했습니다.

## 8. 다음 단계

다음 에피소드에서는 렌더링 파이프라인의 핵심 요소 중 하나인 **스왑 체인(Swap Chain)**에 대해 다룰 예정입니다.
