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
		// --- explicit 용도 ---
		// 올바른 호출 (명시적 객체 생성)
		//processLogger(dx3d::Logger(dx3d::Logger::LogLevel::Info)); // [O] OK
		// 직접 초기화 (Direct-initialization)
		//dx3d::Logger myLog(dx3d::Logger::LogLevel::Warning); // [O] OK
		// 암시적 변환을 방지하므로 코드의 예외 사항을 제한하고 직관적인 사용으로 통일화 시킴.

		explicit Logger(LogLevel logLevel = LogLevel::Error);
		void log(LogLevel level, const char* message) const;

	private:
		LogLevel m_logLevel = LogLevel::Error;

	};

}
