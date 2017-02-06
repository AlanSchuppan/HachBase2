#include <stdexcept>

#include "Lang.hpp"

//#define STR_PTRS

static const wchar_t *English[] = {
    L"", L"Ok", L"Cancel", L"Start", L"InstrumentType", L"String", L"Wind",
    L"Percussion", L"Violin", L"Viola", L"Cello", L"Bass", L"Flute", L"Oboe",
    L"Bassoon", L"Trumpet", L"Drum", L"Cymbal", L"Tambourine", L"Test"
};
static const int EnglishCount =
    sizeof(English) / sizeof(*English);

CLang::CLang() : mMessages(English) {
}

std::wstring CLang::Message(EMsg msg) {
    int Ix = static_cast<int>(msg);
    return (Ix >= 0 && Ix < EnglishCount) ? mMessages[Ix] : L"???";
}

// Bytes | Bits | First  |  Last  |  Byte 1  |  Byte 2  |  Byte 3
//-------+------+--------+--------+----------+----------+---------
//   1   |   7  | U+0000 | U+007F | 0xxxxxxx |          |
//   2   |  11  | U+0080 | U+07FF | 110xxxxx | 10xxxxxx |
//   3   |  16  | U+0800 | U+FFFF | 1110xxxx | 10xxxxxx | 10xxxxxx

#ifdef STR_PTRS

std::wstring CLang::UTF8ToWStr(const std::string &utf8) {
    std::wstring Result;
    const char *pCh = utf8.c_str();
    while (*pCh != '\0') {
        uint32_t NChars = 0;
        wchar_t WCh = 0x0000;
        if ((*pCh & 0x80) == 0x00) {
            WCh = static_cast<wchar_t>(*pCh);
        }
        else if ((*pCh & 0xe0) == 0xc0) {
            WCh = static_cast<wchar_t>(*pCh & 0x1f);
            NChars = 1;
        }
        else if ((*pCh & 0xf0) == 0xe0) {
            WCh = static_cast<wchar_t>(*pCh & 0x0f);
            NChars = 2;
        }
        else {
            throw std::runtime_error("UTF8ToWStr(); Invalid UTF8 string");
        }
        ++pCh;

        while (NChars-- > 0) {
            if ((*pCh & 0xc0) != 0x80)
                throw std::runtime_error("UTF8ToWStr(): Invalid UTF8 string");
            WCh <<= 6;
            WCh |= static_cast<wchar_t>(*pCh++ & 0x3f);
        }

        Result.append(1, WCh);
    }
    return Result;
}

#else // !STR_PTRS

std::wstring CLang::UTF8ToWStr(const std::string &utf8) {
    std::wstring Result;
    auto It = utf8.begin();
    while (*It != '\0') {
        uint32_t NChars = 0;
        wchar_t WCh = 0x0000;
        if ((*It & 0x80) == 0x00) {
            WCh = static_cast<wchar_t>(*It);
        }
        else if ((*It & 0xe0) == 0xc0) {
            WCh = static_cast<wchar_t>(*It & 0x1f);
            NChars = 1;
        }
        else if ((*It & 0xf0) == 0xe0) {
            WCh = static_cast<wchar_t>(*It & 0x0f);
            NChars = 2;
        }
        else {
            throw std::runtime_error("UTF8ToWStr(); Invalid UTF8 string");
        }
        ++It;

        while (NChars-- > 0) {
            if ((*It & 0xc0) != 0x80)
                throw std::runtime_error("UTF8ToWStr(): Invalid UTF8 string");
            WCh <<= 6;
            WCh |= static_cast<wchar_t>(*It++ & 0x3f);
        }

        Result.append(1, WCh);
    }
    return Result;
}

#endif // STR_PTRS

#ifdef STR_PTRS

std::string CLang::WStrToUTF8(const std::wstring &wstr) {
    std::string Result;
    for (wchar_t Ch : wstr) {
        if (Ch < 0x0080) {
            Result.append(1, static_cast<char>(Ch));
        }
        else if (Ch < 0x0800) {
            char Buf[3];
            char *pBuf = Buf + sizeof(Buf) - 1;
            *pBuf-- = '\0';
            *pBuf-- = static_cast<char>((Ch & 0x003f) | 0x0080);
            Ch >>= 6;
            *pBuf-- = static_cast<char>((Ch & 0x001f) | 0x00c0);
            Result.append(Buf);
        }
        else { // Ch <= 0xffff
            char Buf[4];
            char *pBuf = Buf + sizeof(Buf) - 1;
            *pBuf-- = '\0';
            *pBuf-- = static_cast<char>((Ch & 0x003f) | 0x0080);
            Ch >>= 6;
            *pBuf-- = static_cast<char>((Ch & 0x003f) | 0x0080);
            Ch >>= 6;
            *pBuf-- = static_cast<char>((Ch & 0x000f) | 0x00e0);
            Result.append(Buf);
        }
    }
    return Result;
}

#else // !STR_PTRS

std::string CLang::WStrToUTF8(const std::wstring &wstr) {
    std::string Result;
    for (wchar_t Ch : wstr) {
        if (Ch < 0x0080) {
            Result.append(1, static_cast<char>(Ch));
        }
        else if (Ch < 0x0800) {
            std::string Buf(2, ' ');
            auto It = Buf.rbegin();
            *It++ = static_cast<char>((Ch & 0x003f) | 0x0080);
            Ch >>= 6;
            *It++ = static_cast<char>((Ch & 0x001f) | 0x00c0);
            Result.append(Buf);
        }
        else { // Ch <= 0xffff
            std::string Buf(3, ' ');
            auto It = Buf.rbegin();
            *It++ = static_cast<char>((Ch & 0x003f) | 0x0080);
            Ch >>= 6;
            *It++ = static_cast<char>((Ch & 0x003f) | 0x0080);
            Ch >>= 6;
            *It++ = static_cast<char>((Ch & 0x000f) | 0x00e0);
            Result.append(Buf);
        }
    }
    return Result;
}

#endif // STR_PTRS
