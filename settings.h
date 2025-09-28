#ifndef SETTINGS_H_
#define SETTINGS_H_

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

#endif // SETTINGS_H_