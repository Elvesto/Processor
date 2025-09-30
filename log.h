#ifndef LOG_H_
#define LOG_H_

enum FileError {
    All_IS_OK,
    OPEN_ERROR,
    CLOSE_ERROR,
    WRITE_ERROR
};

enum Level {
    CRITICAL,
    ERROR,
    WARNING,
    DEBUG,
    INFO
};

FileError openLog(const char* fileName);

FileError logWrite(Level level, const char* text, ...);

FileError closeLog();

const char* levelToStr(Level level);

#endif // LOG_H_