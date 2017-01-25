#ifndef LANG_HPP
#define LANG_HPP

#include <string>

enum class ELang {
    English
};

enum class EString {
    None, Ok, Cancel, Start, InstrumentType, String, Wind, Percussion, Violin,
    Viola, Cello, Bass, Flute, Oboe, Bassoon, Trumpet, Drum, Cymbal, Tambourine,
    Test
};

class CLang {
  //static const wchar_t *English[];
  const wchar_t **mStrings;
public:
    CLang();
    std::wstring String(EString str);
};

#endif // LANG_HPP
