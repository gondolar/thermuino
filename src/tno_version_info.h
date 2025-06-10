#include "llc_view.h"

#ifndef TNO_VERSION_INFO_H
#define TNO_VERSION_INFO_H

namespace tno
{
    using ::llc::vcst_c;
    stxp ::llc::u3_c    TNO_VERSION_TIME       = 1749552916;
    stxp ::llc::u1_c    TNO_VERSION_YEAR       = 2025;
    stxp ::llc::u0_c    TNO_VERSION_MONTH      = 6;
    stxp ::llc::u0_c    TNO_VERSION_MDAY       = 10;
    stxp ::llc::u1_c    TNO_VERSION_HOUR       = 10;
    stxp ::llc::u0_c    TNO_VERSION_MINUTE     = 55;
    stxp ::llc::vcst_c  TNO_VERSION_STRING     = LLC_CXS("202506101055");
    stxp ::llc::vcst_c  TNO_VERSION_BRANCH     = LLC_CXS("master");
    stxp ::llc::vcst_c  TNO_VERSION_COMMIT     = LLC_CXS("2fb9d102f25ef1a0f6ee126d7146ddb6bea69cdb");
    stxp ::llc::vcst_c  TNO_VERSION_FILENAME   = LLC_CXS("tno.202506101055.bin");
    stxp ::llc::vcst_c  TNO_VERSION_FILESYSTEM = LLC_CXS("./assets");
}

#endif // TNO_VERSION_INFO_H
