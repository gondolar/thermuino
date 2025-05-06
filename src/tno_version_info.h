#include "llc_view.h"

#ifndef TNO_VERSION_INFO_H
#define TNO_VERSION_INFO_H

namespace tno
{
    using ::llc::vcst_c;
    stxp ::llc::u3_c    TNO_VERSION_TIME       = 1746509999;
    stxp ::llc::u1_c    TNO_VERSION_YEAR       = 2025;
    stxp ::llc::u0_c    TNO_VERSION_MONTH      = 5;
    stxp ::llc::u0_c    TNO_VERSION_MDAY       = 6;
    stxp ::llc::u1_c    TNO_VERSION_HOUR       = 5;
    stxp ::llc::u0_c    TNO_VERSION_MINUTE     = 39;
    stxp ::llc::vcst_c  TNO_VERSION_STRING     = LLC_CXS("202505060539");
    stxp ::llc::vcst_c  TNO_VERSION_BRANCH     = LLC_CXS("master");
    stxp ::llc::vcst_c  TNO_VERSION_COMMIT     = LLC_CXS("3324a236779ec8dca1c9be5d976ee0dad5a9fe4f");
    stxp ::llc::vcst_c  TNO_VERSION_FILENAME   = LLC_CXS("tno.202505060539.bin");
    stxp ::llc::vcst_c  TNO_VERSION_FILESYSTEM = LLC_CXS("./assets");
}

#endif // TNO_VERSION_INFO_H
