#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include "Lang.hpp"

//##############################################################################
// CSettings
//##############################################################################
//##############################################################################

class CSettings {
    EMsg mInstrument;
public:
    CSettings();
    EMsg Instrument() const;
    void    Instrument(EMsg instrument);
};

inline EMsg CSettings::Instrument() const {
    return mInstrument;
}

inline void CSettings::Instrument(EMsg instrument) {
    mInstrument = instrument;
}

extern CSettings Settings;

//##############################################################################

#endif // SETTINGS_HPP
