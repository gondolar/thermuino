#include "llc_view.h"

#ifndef TNO_VERSION_INFO_H
#define TNO_VERSION_INFO_H

namespace tno
{
    using ::llc::vcst_c;
    stxp ::llc::u3_c    TNO_VERSION_TIME       = 1746578112;
    stxp ::llc::u1_c    TNO_VERSION_YEAR       = 2025;
    stxp ::llc::u0_c    TNO_VERSION_MONTH      = 5;
    stxp ::llc::u0_c    TNO_VERSION_MDAY       = 7;
    stxp ::llc::u1_c    TNO_VERSION_HOUR       = 0;
    stxp ::llc::u0_c    TNO_VERSION_MINUTE     = 35;
    stxp ::llc::vcst_c  TNO_VERSION_STRING     = LLC_CXS("202505070035");
    stxp ::llc::vcst_c  TNO_VERSION_BRANCH     = LLC_CXS("master");
    stxp ::llc::vcst_c  TNO_VERSION_COMMIT     = LLC_CXS("561b864ba58f8d877ef9d93cbac056616f95df8b");
    stxp ::llc::vcst_c  TNO_VERSION_FILENAME   = LLC_CXS("tno.202505070035.bin");
    stxp ::llc::vcst_c  TNO_VERSION_FILESYSTEM = LLC_CXS("./assets");
}

#endif // TNO_VERSION_INFO_H
