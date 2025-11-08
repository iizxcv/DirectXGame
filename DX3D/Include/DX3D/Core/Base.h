//MIT License
//
//C++ 3D Game Tutorial Series(https://github.com/PardCode/CPP-3D-Game-Tutorial-Series)
//
//Copyright(c) 2019 - 2025, PardCode
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files(the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions :
//
//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.


#pragma once
#include <DX3D/Core/Common.h>


namespace dx3d
{
	// Base 클래스 정의
	class Base
	{
	public:
		// 기본 생성자 선언 (가능한 기본 생성)
		Base(const BaseDesc& desc);
		// 가상 소멸자 선언 (상속받는 클래스들이 안전하게 소멸하도록 처리)
		virtual ~Base();

		virtual Logger& getLogger() const noexcept final;

	protected:
		// 복사 생성자 삭제. Base 객체를 복사해 생성하는 것을 금지
		Base(const Base&) = delete;
		// 이동 생성자 삭제. Base 객체를 이동해 생성하는 것을 금지
		Base(Base&&) = delete;
		// 복사 대입 연산자 삭제. Base 객체에 다른 Base 객체를 복사 대입하는 것을 금지
		Base& operator = (const Base&) = delete;
		// 이동 대입 연산자 삭제. Base 객체에 다른 Base 객체를 이동 대입하는 것을 금지
		Base& operator = (Base&&) = delete;

	protected:
		Logger& m_logger;
	};
}

