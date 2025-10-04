#include "log.h"

#include <stdio.h>
#include <stdarg.h>

static FILE* LOG  = NULL;
static Level targerLevel = INFO;

FileError openLog(const char* fileName) {
    if (fileName == NULL)
        return OPEN_ERROR;
    LOG = fopen(fileName, "w");
    
    if (LOG == NULL)
        return OPEN_ERROR;
    return All_IS_OK;
}

FileError logWrite(Level level, const char* text, ...) {
    if (text == NULL) 
        return WRITE_ERROR;

    va_list args;
    va_start(args, text);
    if (level <= targerLevel) {
        fprintf(LOG, "%s\t", levelToStr(level));
        vfprintf(LOG, text, args);
    }

    va_end(args);

    return All_IS_OK;
}

FileError closeLog() {
    if (LOG == NULL) 
        return CLOSE_ERROR;
    
    fclose(LOG);

    return All_IS_OK;
}

const char* levelToStr(Level level) {
    switch (level) {
        case INFO: return "INFO";
        case DEBUG: return "DEBUG";
        case WARNING: return "WARNING";
        case ERROR: return "ERROR";
        case CRITICAL: return "CRITICAL";
        default: return "RAZRAB DAUN";
    }
}