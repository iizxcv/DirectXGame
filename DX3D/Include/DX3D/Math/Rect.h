#pragma once
#include <DX3D/Core/Core.h>


namespace dx3d
{
	// 2D 사각형을 표현하는 클래스입니다.
	// 주로 창의 크기, UI 요소의 위치와 크기 등을 나타내는 데 사용됩니다.
	class Rect {

	public:
		// 기본 생성자: 모든 값을 0으로 초기화합니다.
		Rect() = default;
		// 너비와 높이만으로 사각형을 생성하는 생성자. left와 top은 0으로 설정됩니다.
		Rect(i32 width, i32 height): left(0), top(0),width(width), height(height){}
		// left, top, width, height 값을 모두 지정하여 사각형을 생성하는 생성자입니다.
		Rect(i32 left, i32 top, i32 width, i32 height) : left(left), top(top), width(width), height(height) {}

	public:
		// 사각형의 왼쪽 상단 x 좌표
		i32 left{};
		// 사각형의 왼쪽 상단 y 좌표
		i32 top{};
		// 사각형의 너비
		i32 width{};
		// 사각형의 높이
		i32 height{};
	};
}
