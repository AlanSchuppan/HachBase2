#ifndef LANG_HPP
#define LANG_HPP

#include <string>

enum class ELang {
    English
};

enum class EMsg {
    None, Ok, Cancel, Start, InstrumentType, String, Wind, Percussion, Violin,
    Viola, Cello, Bass, Flute, Oboe, Bassoon, Trumpet, Drum, Cymbal, Tambourine,
    Test
};

class CLang {
  //static const wchar_t *English[];
  const wchar_t **mMessages;
public:
    static std::wstring UTF8ToWStr(const std::string &utf8);
    static std::string WStrToUTF8(const std::wstring &wstr);

    CLang();
    std::wstring Message(EMsg msg);
};

#endif // LANG_HPP
