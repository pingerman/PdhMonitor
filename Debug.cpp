#include "Debug.h"

namespace Debug
{
	//Funtion taken from stackoverflow
	LPWSTR Debuger::ConvertString(const std::string& instr) 
	{
		// Assumes std::string is encoded in the current Windows ANSI codepage
		int bufferlen = ::MultiByteToWideChar(CP_ACP, 0, instr.c_str(), instr.size(), NULL, 0);

		if (bufferlen == 0)
		{
			// Something went wrong. Perhaps, check GetLastError() and log.
			return 0;
		}

		// Allocate new LPWSTR - must deallocate it later
		LPWSTR widestr = new WCHAR[bufferlen + 1];

		::MultiByteToWideChar(CP_ACP, 0, instr.c_str(), instr.size(), widestr, bufferlen);

		// Ensure wide string is null terminated
		widestr[bufferlen] = 0;

		// Do something with widestr
		return widestr;
	}

	const TCHAR* Debuger::PdhConvert(PDH_STATUS status)
	{
		if (status == ERROR_SUCCESS) return L"ERROR_SUCCESS";
		if (status == PDH_CSTATUS_VALID_DATA) return L"PDH_CSTATUS_VALID_DATA";
		if (status == PDH_CSTATUS_NEW_DATA) return L"PDH_CSTATUS_NEW_DATA";
		if (status == PDH_CSTATUS_NO_MACHINE) return L"PDH_CSTATUS_NO_MACHINE";
		if (status == PDH_CSTATUS_NO_INSTANCE) return L"PDH_CSTATUS_NO_INSTANCE";
		if (status == PDH_MORE_DATA) return L"PDH_MORE_DATA";
		if (status == PDH_CSTATUS_ITEM_NOT_VALIDATED) return L"PDH_CSTATUS_ITEM_NOT_VALIDATED";
		if (status == PDH_RETRY) return L"PDH_RETRY";
		if (status == PDH_NO_DATA) return L"PDH_NO_DATA";
		if (status == PDH_CALC_NEGATIVE_DENOMINATOR) return L"PDH_CALC_NEGATIVE_DENOMINATOR";
		if (status == PDH_CALC_NEGATIVE_TIMEBASE) return L"PDH_CALC_NEGATIVE_TIMEBASE";
		if (status == PDH_CALC_NEGATIVE_VALUE) return L"PDH_CALC_NEGATIVE_VALUE";
		if (status == PDH_DIALOG_CANCELLED) return L"PDH_DIALOG_CANCELLED";
		if (status == PDH_END_OF_LOG_FILE) return L"PDH_END_OF_LOG_FILE";
		if (status == PDH_ASYNC_QUERY_TIMEOUT) return L"PDH_ASYNC_QUERY_TIMEOUT";
		if (status == PDH_CANNOT_SET_DEFAULT_REALTIME_DATASOURCE) return L"PDH_CANNOT_SET_DEFAULT_REALTIME_DATASOURCE";
		if (status == PDH_UNABLE_MAP_NAME_FILES) return L"PDH_UNABLE_MAP_NAME_FILES";
		if (status == PDH_PLA_VALIDATION_WARNING) return L"PDH_PLA_VALIDATION_WARNING";
		if (status == PDH_CSTATUS_NO_OBJECT) return L"PDH_CSTATUS_NO_OBJECT";
		if (status == PDH_CSTATUS_NO_COUNTER) return L"PDH_CSTATUS_NO_COUNTER";
		if (status == PDH_CSTATUS_INVALID_DATA) return L"PDH_CSTATUS_INVALID_DATA";
		if (status == PDH_MEMORY_ALLOCATION_FAILURE) return L"PDH_MEMORY_ALLOCATION_FAILURE";
		if (status == PDH_INVALID_HANDLE) return L"PDH_INVALID_HANDLE";
		if (status == PDH_INVALID_ARGUMENT) return L"PDH_INVALID_ARGUMENT";
		if (status == PDH_FUNCTION_NOT_FOUND) return L"PDH_FUNCTION_NOT_FOUND";
		if (status == PDH_CSTATUS_NO_COUNTERNAME) return L"PDH_CSTATUS_NO_COUNTERNAME";
		if (status == PDH_CSTATUS_BAD_COUNTERNAME) return L"PDH_CSTATUS_BAD_COUNTERNAME";
		if (status == PDH_INVALID_BUFFER) return L"PDH_INVALID_BUFFER";
		if (status == PDH_INSUFFICIENT_BUFFER) return L"PDH_INSUFFICIENT_BUFFER";
		if (status == PDH_CANNOT_CONNECT_MACHINE) return L"PDH_CANNOT_CONNECT_MACHINE";
		if (status == PDH_INVALID_PATH) return L"PDH_INVALID_PATH";
		if (status == PDH_INVALID_INSTANCE) return L"PDH_INVALID_INSTANCE";
		if (status == PDH_INVALID_DATA) return L"PDH_INVALID_DATA";
		if (status == PDH_NO_DIALOG_DATA) return L"PDH_NO_DIALOG_DATA";
		if (status == PDH_CANNOT_READ_NAME_STRINGS) return L"PDH_CANNOT_READ_NAME_STRINGS";
		if (status == PDH_LOG_FILE_CREATE_ERROR) return L"PDH_LOG_FILE_CREATE_ERROR";
		if (status == PDH_LOG_FILE_OPEN_ERROR) return L"PDH_LOG_FILE_OPEN_ERROR";
		if (status == PDH_LOG_TYPE_NOT_FOUND) return L"PDH_LOG_TYPE_NOT_FOUND";
		if (status == PDH_NO_MORE_DATA) return L"PDH_NO_MORE_DATA";
		if (status == PDH_ENTRY_NOT_IN_LOG_FILE) return L"PDH_ENTRY_NOT_IN_LOG_FILE";
		if (status == PDH_DATA_SOURCE_IS_LOG_FILE) return L"PDH_DATA_SOURCE_IS_LOG_FILE";
		if (status == PDH_DATA_SOURCE_IS_REAL_TIME) return L"PDH_DATA_SOURCE_IS_REAL_TIME";
		if (status == PDH_UNABLE_READ_LOG_HEADER) return L"PDH_UNABLE_READ_LOG_HEADER";
		if (status == PDH_FILE_NOT_FOUND) return L"PDH_FILE_NOT_FOUND";
		if (status == PDH_FILE_ALREADY_EXISTS) return L"PDH_FILE_ALREADY_EXISTS";
		if (status == PDH_NOT_IMPLEMENTED) return L"PDH_NOT_IMPLEMENTED";
		if (status == PDH_STRING_NOT_FOUND) return L"PDH_STRING_NOT_FOUND";
		if (status == PDH_UNKNOWN_LOG_FORMAT) return L"PDH_UNKNOWN_LOG_FORMAT";
		if (status == PDH_UNKNOWN_LOGSVC_COMMAND) return L"PDH_UNKNOWN_LOGSVC_COMMAND";
		if (status == PDH_LOGSVC_QUERY_NOT_FOUND) return L"PDH_LOGSVC_QUERY_NOT_FOUND";
		if (status == PDH_LOGSVC_NOT_OPENED) return L"PDH_LOGSVC_NOT_OPENED";
		if (status == PDH_WBEM_ERROR) return L"PDH_WBEM_ERROR";
		if (status == PDH_ACCESS_DENIED) return L"PDH_ACCESS_DENIED";
		if (status == PDH_LOG_FILE_TOO_SMALL) return L"PDH_LOG_FILE_TOO_SMALL";
		if (status == PDH_INVALID_DATASOURCE) return L"PDH_INVALID_DATASOURCE";
		if (status == PDH_INVALID_SQLDB) return L"PDH_INVALID_SQLDB";
		if (status == PDH_NO_COUNTERS) return L"PDH_NO_COUNTERS";
		if (status == PDH_SQL_ALLOC_FAILED) return L"PDH_SQL_ALLOC_FAILED";
		if (status == PDH_SQL_ALLOCCON_FAILED) return L"PDH_SQL_ALLOCCON_FAILED";
		if (status == PDH_SQL_EXEC_DIRECT_FAILED) return L"PDH_SQL_EXEC_DIRECT_FAILED";
		if (status == PDH_SQL_FETCH_FAILED) return L"PDH_SQL_FETCH_FAILED";
		if (status == PDH_SQL_ROWCOUNT_FAILED) return L"PDH_SQL_ROWCOUNT_FAILED";
		if (status == PDH_SQL_MORE_RESULTS_FAILED) return L"PDH_SQL_MORE_RESULTS_FAILED";
		if (status == PDH_SQL_CONNECT_FAILED) return L"PDH_SQL_CONNECT_FAILED";
		if (status == PDH_SQL_BIND_FAILED) return L"PDH_SQL_BIND_FAILED";
		if (status == PDH_CANNOT_CONNECT_WMI_SERVER) return L"PDH_CANNOT_CONNECT_WMI_SERVER";
		if (status == PDH_PLA_COLLECTION_ALREADY_RUNNING) return L"PDH_PLA_COLLECTION_ALREADY_RUNNING";
		if (status == PDH_PLA_ERROR_SCHEDULE_OVERLAP) return L"PDH_PLA_ERROR_SCHEDULE_OVERLAP";
		if (status == PDH_PLA_COLLECTION_NOT_FOUND) return L"PDH_PLA_COLLECTION_NOT_FOUND";
		if (status == PDH_PLA_ERROR_SCHEDULE_ELAPSED) return L"PDH_PLA_ERROR_SCHEDULE_ELAPSED";
		if (status == PDH_PLA_ERROR_NOSTART) return L"PDH_PLA_ERROR_NOSTART";
		if (status == PDH_PLA_ERROR_ALREADY_EXISTS) return L"PDH_PLA_ERROR_ALREADY_EXISTS";
		if (status == PDH_PLA_ERROR_TYPE_MISMATCH) return L"PDH_PLA_ERROR_TYPE_MISMATCH";
		if (status == PDH_PLA_ERROR_FILEPATH) return L"PDH_PLA_ERROR_FILEPATH";
		if (status == PDH_PLA_SERVICE_ERROR) return L"PDH_PLA_SERVICE_ERROR";
		if (status == PDH_PLA_VALIDATION_ERROR) return L"PDH_PLA_VALIDATION_ERROR";
		if (status == PDH_PLA_ERROR_NAME_TOO_LONG) return L"PDH_PLA_ERROR_NAME_TOO_LONG";
		if (status == PDH_INVALID_SQL_LOG_FORMAT) return L"PDH_INVALID_SQL_LOG_FORMAT";
		if (status == PDH_COUNTER_ALREADY_IN_QUERY) return L"PDH_COUNTER_ALREADY_IN_QUERY";
		if (status == PDH_BINARY_LOG_CORRUPT) return L"PDH_BINARY_LOG_CORRUPT";
		if (status == PDH_LOG_SAMPLE_TOO_SMALL) return L"PDH_LOG_SAMPLE_TOO_SMALL";
		if (status == PDH_OS_LATER_VERSION) return L"PDH_OS_LATER_VERSION";
		if (status == PDH_OS_EARLIER_VERSION) return L"PDH_OS_EARLIER_VERSION";
		if (status == PDH_INCORRECT_APPEND_TIME) return L"PDH_INCORRECT_APPEND_TIME";
		if (status == PDH_UNMATCHED_APPEND_COUNTER) return L"PDH_UNMATCHED_APPEND_COUNTER";
		if (status == PDH_SQL_ALTER_DETAIL_FAILED) return L"PDH_SQL_ALTER_DETAIL_FAILED";
		if (status == PDH_QUERY_PERF_DATA_TIMEOUT) return L"PDH_QUERY_PERF_DATA_TIMEOUT";
	}

	void Debuger::OutputMessage(const TCHAR* title, const TCHAR* msg)
	{
		std::wstring w0(L"\n");
		std::wstring w1(title);
		std::wstring w2(msg);
		std::wstring w3(w0 + w1 + w2);
		OutputDebugString(w3.c_str());
	}

	void Debuger::OutputMessage(const TCHAR* msg)
	{
		std::wstring w0(L"\n");
		std::wstring w1(msg);
		std::wstring w3(w0 + w1);
		OutputDebugString(w3.c_str());
	}

	void Debuger::CheckPdhStatus(const TCHAR* title, PDH_STATUS status)
	{
		LPCWSTR wstatus = PdhConvert(status);
		OutputMessage(title, wstatus);
	}

	void APIENTRY Debuger::GLDebugMessageCallback(GLenum source, GLenum type, GLuint id,
		GLenum severity, GLsizei length,
		const GLchar *msg, const void *data)
	{
		const char* _source = " ";
		const char* _type = " ";
		const char* _severity = " ";


		std::string outputS = "\nID: ";
		outputS += id;
		outputS = "\nsource: ";

		switch (source) {
		case GL_DEBUG_SOURCE_API:
			_source = "API";
			break;

		case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
			_source = "WINDOW SYSTEM";
			break;

		case GL_DEBUG_SOURCE_SHADER_COMPILER:
			_source = "SHADER COMPILER";
			break;

		case GL_DEBUG_SOURCE_THIRD_PARTY:
			_source = "THIRD PARTY";
			break;

		case GL_DEBUG_SOURCE_APPLICATION:
			_source = "APPLICATION";
			break;

		case GL_DEBUG_SOURCE_OTHER:
			_source = "UNKNOWN";
			break;

		default:
			_source = "UNKNOWN";
			break;
		}

		outputS += _source;
		outputS += "\n type: ";

		switch (type) {
		case GL_DEBUG_TYPE_ERROR:
			_type = "ERROR";
			break;

		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
			_type = "DEPRECATED BEHAVIOR";
			break;

		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
			_type = "UDEFINED BEHAVIOR";
			break;

		case GL_DEBUG_TYPE_PORTABILITY:
			_type = "PORTABILITY";
			break;

		case GL_DEBUG_TYPE_PERFORMANCE:
			_type = "PERFORMANCE";
			break;

		case GL_DEBUG_TYPE_OTHER:
			_type = "OTHER";
			break;

		case GL_DEBUG_TYPE_MARKER:
			_type = "MARKER";
			break;

		default:
			_type = "UNKNOWN";
			break;
		}

		outputS += _type;
		outputS += "\n severity: ";

		switch (severity) {
		case GL_DEBUG_SEVERITY_HIGH:
			_severity = "HIGH";
			break;

		case GL_DEBUG_SEVERITY_MEDIUM:
			_severity = "MEDIUM";
			break;

		case GL_DEBUG_SEVERITY_LOW:
			_severity = "LOW";
			break;

		case GL_DEBUG_SEVERITY_NOTIFICATION:
			_severity = "NOTIFICATION";
			break;

		default:
			_severity = "UNKNOWN";
			break;
		}

		outputS += _severity;
		outputS += "\nMessage: ";
		outputS += msg;

		std::wstring stemp = std::wstring(outputS.begin(), outputS.end());

		OutputDebugString(stemp.c_str());
	}

	void Debuger::CheckGLError(std::string comment, GLenum format)
	{
		std::string outputS = "\nGL Error: ";
		outputS += convertGLErrorToString(format);
		outputS += " from: ";
		outputS += comment;

		std::wstring stemp = std::wstring(outputS.begin(), outputS.end());

		OutputDebugString(stemp.c_str());
	}

	std::string Debuger::convertGLErrorToString(GLenum format)
	{
		std::string formatName;

		switch (format)
		{

		case GL_NO_ERROR:
			formatName = "GL_NO_ERROR";
			break;
		case GL_INVALID_ENUM:
			formatName = "GL_INVALID_ENUM";
			break;
		case GL_INVALID_VALUE:
			formatName = "GL_INVALID_VALUE";
			break;
		case GL_INVALID_OPERATION:
			formatName = "GL_INVALID_OPERATION";
			break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			formatName = "GL_INVALID_FRAMEBUFFER_OPERATION";
			break;
		case GL_OUT_OF_MEMORY:
			formatName = "GL_OUT_OF_MEMORY";
			break;
		case GL_STACK_UNDERFLOW:
			formatName = "GL_STACK_UNDERFLOW";
			break;
		case GL_STACK_OVERFLOW:
			formatName = "GL_STACK_OVERFLOW";
			break;
		default:
			formatName = "Unknown Format";
			break;
		}

		return formatName;
	}
}