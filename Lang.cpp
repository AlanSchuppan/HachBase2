#include "Lang.hpp"

static const wchar_t *English[] = {
    L"", L"Ok", L"Cancel", L"Start", L"InstrumentType", L"String", L"Wind",
    L"Percussion", L"Violin", L"Viola", L"Cello", L"Bass", L"Flute", L"Oboe",
    L"Bassoon", L"Trumpet", L"Drum", L"Cymbal", L"Tambourine", L"Test"
};
static const int EnglishCount =
    sizeof(English) / sizeof(*English);

CLang::CLang() : mStrings(English) {
}

std::wstring CLang::String(EString stringID) {
    int Ix = static_cast<int>(stringID);
    return (Ix >= 0 && Ix < EnglishCount) ? mStrings[Ix] : L"???";
}
