#include "llc_view.h"

#ifndef TNO_VERSION_INFO_H
#define TNO_VERSION_INFO_H

namespace tno
{
    using ::llc::vcst_c;
    stxp ::llc::u3_c    TNO_VERSION_TIME       = 1749599747;
    stxp ::llc::u1_c    TNO_VERSION_YEAR       = 2025;
    stxp ::llc::u0_c    TNO_VERSION_MONTH      = 6;
    stxp ::llc::u0_c    TNO_VERSION_MDAY       = 10;
    stxp ::llc::u1_c    TNO_VERSION_HOUR       = 23;
    stxp ::llc::u0_c    TNO_VERSION_MINUTE     = 55;
    stxp ::llc::vcst_c  TNO_VERSION_STRING     = LLC_CXS("202506102355");
    stxp ::llc::vcst_c  TNO_VERSION_BRANCH     = LLC_CXS("master");
    stxp ::llc::vcst_c  TNO_VERSION_COMMIT     = LLC_CXS("8096ef1b7b1741e7b84d6f6f8f5da87ec372494c");
    stxp ::llc::vcst_c  TNO_VERSION_FILENAME   = LLC_CXS("tno.202506102355.bin");
    stxp ::llc::vcst_c  TNO_VERSION_FILESYSTEM = LLC_CXS("./assets");
}

#endif // TNO_VERSION_INFO_H
