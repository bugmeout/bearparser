#include "Util.h"

using namespace pe_util;

bool pe_util::isStrLonger(const char *inp, int maxLen)
{
    for (int i = 0; i < maxLen; i++ ) {
        if (inp[i] == '\0') return false;
    }
    return true;
}

/*
QString pe_util::getString(const char *inp, size_t maxInp, size_t maxBuf)
{
    if (maxInp < maxBuf) maxBuf = maxInp;
    if (!inp) return "";
    size_t asciiLen = pe_util::getAsciiLen(inp, maxBuf);
    return QString::fromUtf8(inp, asciiLen);
}*/

size_t pe_util::getAsciiLen(const char *inp, size_t maxInp, bool acceptNotTerminated)
{
    size_t i = 0;
    for (; i < maxInp; i++) {
        const char c = inp[i];
        if (c == '\0') return i; //end of string
        if (!IS_PRINTABLE(c) && !IS_ENDLINE(c)) return 0;
    }
    if (acceptNotTerminated) return i;
    return 0;
}

size_t pe_util::getAsciiLenW(const WORD *inp, size_t maxInp, bool acceptNotTerminated)
{
    size_t i = 0;
    for (; i < maxInp; i++) {
        const WORD w = inp[i];
        if (w == 0) return i; //end of string
        if (!IS_PRINTABLE(w) && !IS_ENDLINE(w)) return 0;
    }
    if (acceptNotTerminated) return i;
    return 0;
}

bool pe_util::hasNonPrintable(const char *inp, size_t maxInp)
{
    unsigned int i = 0;
    for ( i = 0; i < maxInp; i++) {
        char c = inp[i];
        if (c == '\0') break; //end of string
        if (!IS_PRINTABLE(c)) return true;
    }
    return false;
}

size_t pe_util::noWhiteCount(char *buf, size_t bufSize) {
    size_t cntr = 0;
    unsigned int i = 0;
    for (i = 0; i < bufSize; i++) {
        if (IS_PRINTABLE(buf[i]) && buf[i] != ' ')
            cntr++;
    }
    return cntr;
}

size_t pe_util::noWhiteCount(std::string s)
{
    size_t bufSize = s.length();
    size_t cntr = 0;
    unsigned int i = 0;
    for (i = 0; i < bufSize; i++) {
        if (IS_PRINTABLE(s[i]) && s[i] != ' ')
            cntr++;
    }
    return cntr;
}

bool pe_util::isSpaceClear(void* ptr, uint64_t size)
{
    BYTE* testblock = (BYTE*) calloc(size, sizeof(BYTE));
    bool isClear = true;
    if (memcmp (testblock, ptr, size)) {
        isClear = false;
    }
    free(testblock);
    return isClear;
}

bool pe_util::isHexChar(char c)
{
    if (isdigit(c)) return true;
    if (c >= 'A' && c <= 'F') return true;
    if (c >= 'a' && c <= 'f') return true;
    return false;
}

void pe_util::hexdump(BYTE *buf, size_t bufSize, size_t pad)
{
    if (buf == NULL) return;
    printf("\n---\n");
    for (int i = 0; i < bufSize; i++) {
        if (i % pad == 0) printf("\n");
        printf("0x%02X ", buf[i]);
    }
    printf("\n---\n");
}

bool pe_util::endsWith(std::string str, std::string endStr)
{
    size_t sepPos = str.find_last_of(endStr);
    if ( sepPos == (str.length() - 1)) {
        return true;
    }
    return false;
}
