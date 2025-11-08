#include <DX3D/Core/Logger.h>
#include <iostream>

dx3d::Logger::Logger(LogLevel logLevel)
	: m_logLevel(logLevel)
{
	std::clog << "JooCode | c++ 3D Game Tutorial Series" << "\n";
	std::clog << "------------------------------------" << "\n";
}

void dx3d::Logger::log(LogLevel level, const char* message) const
{
	auto logLevelToString = [](LogLevel level) {
		switch (level)
		{
		case dx3d::Logger::LogLevel::Error:
			return "Error";
		case dx3d::Logger::LogLevel::Warning:
			return "Warning";
		case dx3d::Logger::LogLevel::Info:
			return "Info";
		default:
			return "Unknown";
		}
		};

	if (level > m_logLevel) return;
	std::clog << "[DX3D" << logLevelToString(level) << "]: " << message << "\n";
} 
