#include "llc_view.h"

#ifndef TNO_VERSION_INFO_H
#define TNO_VERSION_INFO_H

namespace tno
{
    using ::llc::vcst_c;
    stxp ::llc::u3_c    TNO_VERSION_TIME       = 1746213324;
    stxp ::llc::u1_c    TNO_VERSION_YEAR       = 2025;
    stxp ::llc::u0_c    TNO_VERSION_MONTH      = 5;
    stxp ::llc::u0_c    TNO_VERSION_MDAY       = 2;
    stxp ::llc::u1_c    TNO_VERSION_HOUR       = 19;
    stxp ::llc::u0_c    TNO_VERSION_MINUTE     = 15;
    stxp ::llc::vcst_c  TNO_VERSION_STRING     = LLC_CXS("202505021915");
    stxp ::llc::vcst_c  TNO_VERSION_BRANCH     = LLC_CXS("master");
    stxp ::llc::vcst_c  TNO_VERSION_COMMIT     = LLC_CXS("fee3a8e057276328101e1465546178265cb8ec23");
    stxp ::llc::vcst_c  TNO_VERSION_FILENAME   = LLC_CXS("tno.202505021915.bin");
    stxp ::llc::vcst_c  TNO_VERSION_FILESYSTEM = LLC_CXS("./assets");
}

#endif // TNO_VERSION_INFO_H
