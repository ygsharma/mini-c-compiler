#ifndef SOURCE_BUFFER_H
#define SOURCE_BUFFER_H

#include <string>
#include <vector>


class SourceBuffer {
public:
    SourceBuffer(const std::string& file);
    char peekChar();
    char getChar();
    bool eof();
    
    // getters
    int getLine() const { return line + 1; }
    int getColumn() const { return column + 1; }
    const std::string& getFilename() const { return filename; }
    const std::string& getLineText(int lineNumber) const;

private:
    std::string filename;
    std::vector<std::string> lines;
    std::string src;
    
    size_t pos;
    int line;
    int column;
};

#endif