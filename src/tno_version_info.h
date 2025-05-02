#include "llc_view.h"

#ifndef TNO_VERSION_INFO_H
#define TNO_VERSION_INFO_H

namespace tno
{
    using ::llc::vcst_c;
    stxp ::llc::u3_c    TNO_VERSION_TIME       = 1746201611;
    stxp ::llc::u1_c    TNO_VERSION_YEAR       = 2025;
    stxp ::llc::u0_c    TNO_VERSION_MONTH      = 5;
    stxp ::llc::u0_c    TNO_VERSION_MDAY       = 2;
    stxp ::llc::u1_c    TNO_VERSION_HOUR       = 16;
    stxp ::llc::u0_c    TNO_VERSION_MINUTE     = 0;
    stxp ::llc::vcst_c  TNO_VERSION_STRING     = LLC_CXS("202505021600");
    stxp ::llc::vcst_c  TNO_VERSION_BRANCH     = LLC_CXS("master");
    stxp ::llc::vcst_c  TNO_VERSION_COMMIT     = LLC_CXS("6db801ad3e4f4470612caa95c499ea73a525f1b1");
    stxp ::llc::vcst_c  TNO_VERSION_FILENAME   = LLC_CXS("tno.202505021600.bin");
    stxp ::llc::vcst_c  TNO_VERSION_FILESYSTEM = LLC_CXS("./assets");
}

#endif // TNO_VERSION_INFO_H
