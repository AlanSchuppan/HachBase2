#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <string>

#include "Singleton.hpp"
#include "Lang.hpp"

//##############################################################################
// CSettings
//##############################################################################
//##############################################################################

class CSettings : public CSingleton {
    EMsg mInstrument;
public:
    static CSingleton *CreateMe(std::string &name);
    CSettings(const std::string &name);
    EMsg Instrument() const;
    void    Instrument(EMsg instrument);
};

inline EMsg CSettings::Instrument() const {
    return mInstrument;
}

inline void CSettings::Instrument(EMsg instrument) {
    mInstrument = instrument;
}

extern TSingletonHost<CSettings> Settings;

//##############################################################################

#endif // SETTINGS_HPP
