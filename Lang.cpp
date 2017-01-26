#include "Lang.hpp"

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
