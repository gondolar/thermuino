#include "llc_view.h"

#ifndef TNO_VERSION_INFO_H
#define TNO_VERSION_INFO_H

namespace tno
{
    using ::llc::vcst_c;
    stxp ::llc::u3_c    TNO_VERSION_TIME       = 1755140816;
    stxp ::llc::u1_c    TNO_VERSION_YEAR       = 2025;
    stxp ::llc::u0_c    TNO_VERSION_MONTH      = 8;
    stxp ::llc::u0_c    TNO_VERSION_MDAY       = 14;
    stxp ::llc::u1_c    TNO_VERSION_HOUR       = 3;
    stxp ::llc::u0_c    TNO_VERSION_MINUTE     = 6;
    stxp ::llc::vcst_c  TNO_VERSION_STRING     = LLC_CXS("202508140306");
    stxp ::llc::vcst_c  TNO_VERSION_BRANCH     = LLC_CXS("master");
    stxp ::llc::vcst_c  TNO_VERSION_COMMIT     = LLC_CXS("77681db3bfefa9b991df2f2018529c6a8a5c6eeb");
    stxp ::llc::vcst_c  TNO_VERSION_FILENAME   = LLC_CXS("tno.202508140306.bin");
    stxp ::llc::vcst_c  TNO_VERSION_FILESYSTEM = LLC_CXS("./assets");
}

#endif // TNO_VERSION_INFO_H
