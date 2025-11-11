#pragma once
#include <DX3D/Core/Logger.h>

namespace dx3d
{
// DirectX/그래픽스 관련 API 호출의 오류를 처리하기 위한 전용 매크로입니다.
// HRESULT를 반환하는 함수 호출의 결과를 검사하여, 실패(FAILED) 시
// 지정된 메시지로 로그를 남기고 예외를 던집니다.
#define DX3DGraphicsLogErrorAndThow(hr,message)
	{
		/* API 호출(hr)을 실행하고 그 결과를 res 변수에 저장합니다. */
		auto res = (hr);
		/* FAILED 매크로를 사용하여 HRESULT 값이 실패 코드인지 확인합니다. */
		if(FAILED(res))
			/* 실패했다면, 일반 오류 처리 매크로를 호출하여 로그 및 예외 처리를 합니다. */
			DX3DLogErrorAndThrow(message);
	}
}
