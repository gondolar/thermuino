#include "llc_view.h"

#ifndef TNO_VERSION_INFO_H
#define TNO_VERSION_INFO_H

namespace tno
{
    using ::llc::vcst_c;
    stxp ::llc::u3_c    TNO_VERSION_TIME       = 1749327996;
    stxp ::llc::u1_c    TNO_VERSION_YEAR       = 2025;
    stxp ::llc::u0_c    TNO_VERSION_MONTH      = 6;
    stxp ::llc::u0_c    TNO_VERSION_MDAY       = 7;
    stxp ::llc::u1_c    TNO_VERSION_HOUR       = 20;
    stxp ::llc::u0_c    TNO_VERSION_MINUTE     = 26;
    stxp ::llc::vcst_c  TNO_VERSION_STRING     = LLC_CXS("202506072026");
    stxp ::llc::vcst_c  TNO_VERSION_BRANCH     = LLC_CXS("master");
    stxp ::llc::vcst_c  TNO_VERSION_COMMIT     = LLC_CXS("293d80fed9f0b1e5c35f9053802879a215dd932f");
    stxp ::llc::vcst_c  TNO_VERSION_FILENAME   = LLC_CXS("tno.202506072026.bin");
    stxp ::llc::vcst_c  TNO_VERSION_FILESYSTEM = LLC_CXS("./assets");
}

#endif // TNO_VERSION_INFO_H
