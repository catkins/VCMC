#ifndef __have__ChordInversions_h__
#define __have__ChordInversions_h__

/** @addtogroup MIDI
 *  @{
 */

/**
 *  \file ChordInversions.h
 *  \brief Music Chord Inversions definition
 */

enum
{
    NO_INVDROP = 0,
    INV1_INVDROP,
    INV2_INVDROP,
    INV3_INVDROP,
    DROP2ROOT_INVDROP,
    DROP2INV1_INVDROP,
    DROP2INV2_INVDROP,
    DROP2INV3_INVDROP,
    DROP3ROOT_INVDROP,
    DROP3INV1_INVDROP,
    DROP3INV2_INVDROP,
    DROP3INV3_INVDROP,

    OPEN2ROOT_INVDROP,
    OPEN2INV1_INVDROP,
    OPEN2INV2_INVDROP,
    OPEN2INV3_INVDROP,
    OPEN3ROOT_INVDROP,
    OPEN3INV1_INVDROP,
    OPEN3INV2_INVDROP,
    OPEN3INV3_INVDROP,
    
    LAST_INVDROP,
    DEF_INVDROP
};

static const char *const InvDropShortNames[] =
{
    "Root",
    "1st Inv",
    "2nd Inv",
    "3rd Inv",
    "Drop 2 root",
    "Drop 2 Inv 1",
    "Drop 2 Inv 2",
    "Drop 2 Inv 3",
    "Drop 3 root",
    "Drop 3 Inv 1",
    "Drop 3 Inv 2",
    "Drop 3 Inv 3",

    "Open 2 root",
    "Open 2 Inv 1",
    "Open 2 Inv 2",
    "Open 2 Inv 3",
    "Open 3 root",
    "Open 3 Inv 1",
    "Open 3 Inv 2",
    "Open 3 Inv 3",

    "Invalid Inv",
    "Default"
};

const int8_t InversionDrop4[][4] __attribute__((unused)) = {
    {0, 0, 0, 0},    // root (close voicing)
    {12, 0, 0, 0},   // 1st inv
    {12, 12, 0, 0},  // 2nd inv
    {12, 12, 12, 0}, //{ 0, 0, 0, -12 },   // 3rd inv

    {0, 0, -12, 0},  // root drop 2
    {12, 0, 0, -12}, // 1st inv drop 2
    {0, 12, 0, 0},   // 2nd inv drop 2
    {12, 0, 12, 0},  // 3rd inv drop 2

    {0, -12, 0, 0},   // root drop 3
    {12, 0, -12, 0},  // 1st inv drop 3
    {12, 12, 0, -12}, // 2nd inv drop 3
    {0, 12, 12, 0},    // 3rd inv drop 3

    {0, 0, 12, 0},  // root open 2
    {12, 0, 0, 12}, // 1st inv open 2
    {24, 12, 0, 0},   // 2nd inv open 2
    {12, 24, 12, 0},  // 3rd inv open 2

    {0, 12, 0, 0},   // root open 3
    {12, 0, 12, 0},  // 1st inv open 3
    {12, 12, 0, 12}, // 2nd inv open 3
    {24, 12, 12, 0},    // 3rd inv open 3

    {0, 0, 0, 0},    // Invalid, do not use
    {0, 0, 0, 0}    // Defauly == root
};

const int8_t InversionDrop3[][3] __attribute__((unused)) = {
    {0, 0, 0}, //close voicing
    {12, 0, 0},
    {12, 12, 0},
    {0, 0, 0}, //close voicing

    {0, -12, 0}, // drop 2
    {12, 0, -12},
    {0, 12, 0},
    {0, -12, 0}, // drop 2

    {-12, 0, 0}, // drop 3
    {12, -12, 0},
    {12, 12, -12},
    {-12, 0, 0}, // drop 3

    {0, 12, 0}, // open 2
    {12, 0, 12},
    {24, 12, 0},
    {0, 12, 0}, // open 2

    {12, 0, 0}, // open 3 (TODO check sense for triads)
    {12, 12, 0},
    {12, 12, 12},
    {12, 0, 0}, // open 3

    {0, 0, 0}, //Invalid, do noy use
    {0, 0, 0}  //default = root
};

/** @} */

#endif
