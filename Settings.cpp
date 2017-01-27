#include "Settings.hpp"

//##############################################################################
// CSettings
//##############################################################################
//##############################################################################

CSingleton *CSettings::CreateMe(std::string &name) {
    name = "Settings";
    return new CSettings(name);
}

CSettings::CSettings(const std::string &name) :
    CSingleton(name), mInstrument(EMsg::Violin) {
}

TSingletonHost<CSettings> Settings(CSettings::CreateMe);

//##############################################################################
