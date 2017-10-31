#include "Logger.h"

	Log Log::instance;

	Log::Log() {

		openFile();

	}

	Log::~Log() {

		closeFile();

	}

	// Open the log file with <date>_fileName.log or <date>.log

	void Log::openFile() {
		if(inFile){

			fileName = "log.txt";
			std::cout << "__________________________________________________\n" <<
				"\n[ Starting GAME ]\n" <<
				"--> Arquivo de Log: " << fileName << std::endl << std::endl;

			logFile.open(fileName);

			std::string border =
				"==============================================================\n";
			std::string logMessage = "Begin Logging\n";

			logFile << border << logMessage << border;
			logFile.flush();
		}
	}

	// Close the currently open log file

	void Log::closeFile() {

		if(inFile){
			if( logFile.is_open() ) {
				std::cout << "[ Encerrando GAME ]\n" <<
					"<-- Para eventuais mensagens de sistema,\nconferir arquivo: " <<
					fileName << std::endl <<
					"__________________________________________________\n" << std::endl;

				std::string border =
					"==============================================================\n";
				std::string logMessage = "End Logging\n";

				logFile << border << logMessage << border;
				logFile.flush();
				logFile.close();
			}
		}
	}

	// Debug message

	void Log::debug(std::string msg) {

		if(inFile){
			if( DEBUG ) {
				logFile << "[DEBUG] ";
				logFile << msg << std::endl;
				logFile.flush();
			}

		}
		if(console){
			std::cout << "[DEBUG]" + msg << std::endl; 
		}
	}

	// Warning message

	void Log::warning(std::string msg) {

		if(inFile){
			logFile << "[WARN] ";
			logFile << msg << std::endl;
			logFile.flush();

		}
		if(console){
			std::cout << "[WARN]" + msg << std::endl; 
		}
	}

	// Error message

	void Log::error(std::string msg) {

		if(inFile){
			logFile << "[ERROR] ";
			logFile << msg << std::endl;
			logFile.flush();
		}
		if(console){
			std::cout << "[ERROR]" + msg << std::endl; 
		}
	}

	void Log::info(std::string msg) {

		if(inFile){
			logFile << "[INFO] ";
			logFile << msg << std::endl;
			logFile.flush();
		}
		if(console){
			std::cout << "[INFO]" + msg << std::endl; 
		}
	}

	void Log::jumpLine(std::string msg) {

		if(inFile){
			logFile << "\n[->]";
			logFile << msg << std::endl;
			logFile.flush();
		}
		if(console){
			std::cout << "[ jumpLine ]" + msg << std::endl; 
		}
	}
