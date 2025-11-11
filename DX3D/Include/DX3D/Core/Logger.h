#pragma once

namespace dx3d{

	class Logger final
	{
	public:
		enum class LogLevel
		{
			Error = 0,
			Warning,
			Info,
		};
		// --- explicit �뵵 ---
		// �ùٸ� ȣ�� (������ ��ü ����)
		//processLogger(dx3d::Logger(dx3d::Logger::LogLevel::Info)); // [O] OK
		// ���� �ʱ�ȭ (Direct-initialization)
		//dx3d::Logger myLog(dx3d::Logger::LogLevel::Warning); // [O] OK
		// �Ͻ��� ��ȯ�� �����ϹǷ� �ڵ��� ���� ������ �����ϰ� �������� ������� ����ȭ ��Ŵ.

		explicit Logger(LogLevel logLevel = LogLevel::Error);
		void log(LogLevel level, const char* message) const;

	private:
		LogLevel m_logLevel = LogLevel::Error;

	};

// 아래 매크로들은 getLogger() 함수를 통해 로거 인스턴스에 접근하여
// 간편하게 로그를 기록할 수 있도록 도와주는 헬퍼(helper) 매크로입니다.

// 정보(Info) 레벨의 로그를 기록하는 매크로입니다.
#define DX3DLogInfo(message)\
	getLogger().log(Logger::LogLevel::Info, message);

// 경고(Warning) 레벨의 로그를 기록하는 매크로입니다.
#define DX3DLogWarning(message)\
	getLogger().log(Logger::LogLevel::Warning, message);

// 오류(Error) 레벨의 로그를 기록하는 매크로입니다.
#define DX3DLogError(message)\
	getLogger().log(Logger::LogLevel::Error, message);

// 오류 로그를 기록하고, 즉시 std::runtime_error 예외를 발생시키는 매크로입니다.
// 프로그램 실행 중 복구 불가능한 심각한 오류가 발생했을 때 사용됩니다.
#define DX3DLogErrorAndThrow(message)\
	{\
	DX3DLogError(message);\
	throw std::runtime_error(message);\
	}

}
