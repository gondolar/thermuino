#include "llc_view.h"

#ifndef TNO_VERSION_INFO_H
#define TNO_VERSION_INFO_H

namespace tno
{
    using ::llc::vcst_c;
    stxp ::llc::u3_c    TNO_VERSION_TIME       = 1749289546;
    stxp ::llc::u1_c    TNO_VERSION_YEAR       = 2025;
    stxp ::llc::u0_c    TNO_VERSION_MONTH      = 6;
    stxp ::llc::u0_c    TNO_VERSION_MDAY       = 7;
    stxp ::llc::u1_c    TNO_VERSION_HOUR       = 9;
    stxp ::llc::u0_c    TNO_VERSION_MINUTE     = 45;
    stxp ::llc::vcst_c  TNO_VERSION_STRING     = LLC_CXS("202506070945");
    stxp ::llc::vcst_c  TNO_VERSION_BRANCH     = LLC_CXS("master");
    stxp ::llc::vcst_c  TNO_VERSION_COMMIT     = LLC_CXS("cf8d271ad280fc05d1efa2df857bc8ba2c9fc80c");
    stxp ::llc::vcst_c  TNO_VERSION_FILENAME   = LLC_CXS("tno.202506070945.bin");
    stxp ::llc::vcst_c  TNO_VERSION_FILESYSTEM = LLC_CXS("./assets");
}

#endif // TNO_VERSION_INFO_H
