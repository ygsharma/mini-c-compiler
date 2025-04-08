#include "source_buffer.h"

#include <iostream>
#include <stdexcept>
#include <fstream>
#include <sstream>


// constructor which reads the file content and copies in lines and src (buffer)
SourceBuffer::SourceBuffer( const std::string& filename) : filename(filename), pos(0), line(0), column(0) {
    
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    std::ostringstream ss;
    std::string lineText;
    while (std::getline(file, lineText)) {
        // store in 'lines' vector to show error messages
        lines.push_back(lineText);
        ss << lineText << '\n';
    }
    src = ss.str();
}

// peek the next character from the src buffer
char SourceBuffer::peekChar() {
    return pos < src.size() ? src[pos] : '\0';
}

// get the next character of the src buffer
char SourceBuffer::getChar() {
    if (pos >= src.size()) return '\0';

    char ch = src[pos++];

    if (ch == '\n') {
        line++;
        column = 0;
    } else {
        column++;
    }
    return ch;
}

// checks if the current pointer is at end of src buffer
bool SourceBuffer::eof() {
    return pos >= src.size();
}

// get content of the next line in the src buffer
const std::string& SourceBuffer::getLineText(int lineNumber) const {
    if (lineNumber - 1 < lines.size()) {
        return lines[lineNumber - 1];
    }
    static std::string empty = "";
    return empty;
}
