#ifndef COORDCUBE_H
#define COORDCUBE_H

#include <sys/types.h>
#include <stdio.h>
#include "prunetable_helpers.h"
#include "cubiecube.h"

// Representation of the cube on the coordinate level

#define N_TWIST     2187
#define N_FLIP      2048
#define N_SLICE1    495
#define N_SLICE2    24
#define N_PARITY    2
#define N_URFtoDLF  20160
#define N_FRtoBR    11880
#define N_URtoUL    1320
#define N_UBtoDF    1320
#define N_URtoDF    20160
#define N_URFtoDLB  40320
#define N_URtoBR    479001600
#define N_MOVE      18

typedef struct {

    // All coordinates are 0 for a solved cube except for UBtoDF, which is 114
    short twist;
    short flip;
    short parity;
    short FRtoBR;
    short URFtoDLF;
    short URtoUL;
    short UBtoDF;
    int URtoDF;
} coordcube_t;

// ******************************************Phase 1 move tables*****************************************************

// Move table for the twists of the corners
// twist < 2187 in phase 2.
// twist = 0 in phase 2.
extern short twistMove[N_TWIST][N_MOVE];

// Move table for the flips of the edges
// flip < 2048 in phase 1
// flip = 0 in phase 2.
extern short flipMove[N_FLIP][N_MOVE];

// Parity of the corner permutation. This is the same as the parity for the edge permutation of a valid cube.
// parity has values 0 and 1
extern short parityMove[2][18];

// ***********************************Phase 1 and 2 movetable********************************************************

// Move table for the four UD-slice edges FR, FL, Bl and BR
// FRtoBRMove < 11880 in phase 1
// FRtoBRMove < 24 in phase 2
// FRtoBRMove = 0 for solved cube
extern short FRtoBR_Move[N_FRtoBR][N_MOVE];

// Move table for permutation of six corners. The positions of the DBL and DRB corners are determined by the parity.
// URFtoDLF < 20160 in phase 1
// URFtoDLF < 20160 in phase 2
// URFtoDLF = 0 for solved cube.
extern short URFtoDLF_Move[N_URFtoDLF][N_MOVE];

// Move table for the permutation of six U-face and D-face edges in phase2. The positions of the DL and DB edges are
// determined by the parity.
// URtoDF < 665280 in phase 1
// URtoDF < 20160 in phase 2
// URtoDF = 0 for solved cube.
extern short URtoDF_Move[N_URtoDF][N_MOVE];

// **************************helper move tables to compute URtoDF for the beginning of phase2************************

// Move table for the three edges UR,UF and UL in phase1.
extern short URtoUL_Move[N_URtoUL][N_MOVE];

// Move table for the three edges UB,DR and DF in phase1.
extern short UBtoDF_Move[N_UBtoDF][N_MOVE];

// Table to merge the coordinates of the UR,UF,UL and UB,DR,DF edges at the beginning of phase2
extern short MergeURtoULandUBtoDF[336][336];

// ****************************************Pruning tables for the search*********************************************

// Pruning table for the permutation of the corners and the UD-slice edges in phase2.
// The pruning table entries give a lower estimation for the number of moves to reach the solved cube.
extern signed char Slice_URFtoDLF_Parity_Prun[N_SLICE2 * N_URFtoDLF * N_PARITY / 2];

// Pruning table for the permutation of the edges in phase2.
// The pruning table entries give a lower estimation for the number of moves to reach the solved cube.
extern signed char Slice_URtoDF_Parity_Prun[N_SLICE2 * N_URtoDF * N_PARITY / 2];

// Pruning table for the twist of the corners and the position (not permutation) of the UD-slice edges in phase1
// The pruning table entries give a lower estimation for the number of moves to reach the H-subgroup.
extern signed char Slice_Twist_Prun[N_SLICE1 * N_TWIST / 2 + 1];

// Pruning table for the flip of the edges and the position (not permutation) of the UD-slice edges in phase1
// The pruning table entries give a lower estimation for the number of moves to reach the H-subgroup.
extern signed char Slice_Flip_Prun[N_SLICE1 * N_FLIP / 2];

extern int PRUNING_INITED;
void initPruning(const char *cache_dir);

// Set pruning value in table. Two values are stored in one char.
void setPruning(signed char *table, int index, signed char value);

// Extract pruning value
signed char getPruning(signed char *table, int index);

coordcube_t* get_coordcube(cubiecube_t* cubiecube);
void move(coordcube_t* coordcube, int m, const char *cache_dir);



short twistMove[N_TWIST][N_MOVE];
short flipMove[N_FLIP][N_MOVE];
short parityMove[2][18] = {
    { 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1 },
    { 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0 }
};
short FRtoBR_Move[N_FRtoBR][N_MOVE];
short URFtoDLF_Move[N_URFtoDLF][N_MOVE] = {{0}};
short URtoDF_Move[N_URtoDF][N_MOVE] = {{0}};
short URtoUL_Move[N_URtoUL][N_MOVE] = {{0}};
short UBtoDF_Move[N_UBtoDF][N_MOVE] = {{0}};
short MergeURtoULandUBtoDF[336][336] = {{0}};
signed char Slice_URFtoDLF_Parity_Prun[N_SLICE2 * N_URFtoDLF * N_PARITY / 2] = {0};
signed char Slice_URtoDF_Parity_Prun[N_SLICE2 * N_URtoDF * N_PARITY / 2] = {0};
signed char Slice_Twist_Prun[N_SLICE1 * N_TWIST / 2 + 1] = {0};
signed char Slice_Flip_Prun[N_SLICE1 * N_FLIP / 2] = {0};

int PRUNING_INITED = 0;

void move(coordcube_t* coordcube, int m, const char *cache_dir)
{
    if (PRUNING_INITED == 0) {
        initPruning(cache_dir);
    }
    coordcube->twist = twistMove[coordcube->twist][m];
    coordcube->flip = flipMove[coordcube->flip][m];
    coordcube->parity = parityMove[coordcube->parity][m];
    coordcube->FRtoBR = FRtoBR_Move[coordcube->FRtoBR][m];
    coordcube->URFtoDLF = URFtoDLF_Move[coordcube->URFtoDLF][m];
    coordcube->URtoUL = URtoUL_Move[coordcube->URtoUL][m];
    coordcube->UBtoDF = UBtoDF_Move[coordcube->UBtoDF][m];
    if (coordcube->URtoUL < 336 && coordcube->UBtoDF < 336)// updated only if UR,UF,UL,UB,DR,DF
        // are not in UD-slice
        coordcube->URtoDF = MergeURtoULandUBtoDF[coordcube->URtoUL][coordcube->UBtoDF];
}

coordcube_t* get_coordcube(cubiecube_t* cubiecube)
{
    coordcube_t* result = (coordcube_t *) calloc(1, sizeof(coordcube_t));

    result->twist       = getTwist(cubiecube);
    result->flip        = getFlip(cubiecube);
    result->parity      = cornerParity(cubiecube);
    result->FRtoBR      = getFRtoBR(cubiecube);
    result->URFtoDLF    = getURFtoDLF(cubiecube);
    result->URtoUL      = getURtoUL(cubiecube);
    result->UBtoDF      = getUBtoDF(cubiecube);
    result->URtoDF      = getURtoDF(cubiecube);// only needed in phase2

    return result;
}

void initPruning(const char *cache_dir)
{
    cubiecube_t* a;
    cubiecube_t* moveCube = get_moveCube();

    if(check_cached_table("twistMove", (void*) twistMove, sizeof(twistMove), cache_dir) != 0) {
        short i;
        int k, j;
        a = get_cubiecube();
        for (i = 0; i < N_TWIST; i++) {
            setTwist(a, i);
            for (j = 0; j < 6; j++) {
                for (k = 0; k < 3; k++) {
                    cornerMultiply(a, &moveCube[j]);
                    twistMove[i][3 * j + k] = getTwist(a);
                }
                cornerMultiply(a, &moveCube[j]);// 4. faceturn restores
            }
        }
        free(a);
        dump_to_file((void*) twistMove, sizeof(twistMove), "twistMove", cache_dir);
    }

    if(check_cached_table("flipMove", (void*) flipMove, sizeof(flipMove), cache_dir) != 0) {
        short i;
        int k, j;
        a = get_cubiecube();
        for (i = 0; i < N_FLIP; i++) {
            setFlip(a, i);
            for (j = 0; j < 6; j++) {
                for (k = 0; k < 3; k++) {
                    edgeMultiply(a, &moveCube[j]);
                    flipMove[i][3 * j + k] = getFlip(a);
                }
                edgeMultiply(a, &moveCube[j]);
            }
        }
        free(a);
        dump_to_file((void*) flipMove, sizeof(flipMove), "flipMove", cache_dir);
    }

    if(check_cached_table("FRtoBR_Move", (void*) FRtoBR_Move, sizeof(FRtoBR_Move), cache_dir) != 0) {
        short i;
        int k, j;
        a = get_cubiecube();
        for (i = 0; i < N_FRtoBR; i++) {
            setFRtoBR(a, i);
            for (j = 0; j < 6; j++) {
                for (k = 0; k < 3; k++) {
                    edgeMultiply(a, &moveCube[j]);
                    FRtoBR_Move[i][3 * j + k] = getFRtoBR(a);
                }
                edgeMultiply(a, &moveCube[j]);
            }
        }
        free(a);
        dump_to_file((void*) FRtoBR_Move, sizeof(FRtoBR_Move), "FRtoBR_Move", cache_dir);
    }

    if(check_cached_table("URFtoDLF_Move", (void*) URFtoDLF_Move, sizeof(URFtoDLF_Move), cache_dir) != 0) {
        short i;
        int k, j;
        a = get_cubiecube();
        for (i = 0; i < N_URFtoDLF; i++) {
            setURFtoDLF(a, i);
            for (j = 0; j < 6; j++) {
                for (k = 0; k < 3; k++) {
                    cornerMultiply(a, &moveCube[j]);
                    URFtoDLF_Move[i][3 * j + k] = getURFtoDLF(a);
                }
                cornerMultiply(a, &moveCube[j]);
            }
        }
        free(a);
        dump_to_file((void*) URFtoDLF_Move, sizeof(URFtoDLF_Move), "URFtoDLF_Move", cache_dir);
    }

    if(check_cached_table("URtoDF_Move", (void*) URtoDF_Move, sizeof(URtoDF_Move), cache_dir) != 0) {
        short i;
        int k, j;
        a = get_cubiecube();
        for (i = 0; i < N_URtoDF; i++) {
            setURtoDF(a, i);
            for (j = 0; j < 6; j++) {
                for (k = 0; k < 3; k++) {
                    edgeMultiply(a, &moveCube[j]);
                    URtoDF_Move[i][3 * j + k] = (short) getURtoDF(a);
                    // Table values are only valid for phase 2 moves!
                    // For phase 1 moves, casting to short is not possible.
                }
                edgeMultiply(a, &moveCube[j]);
            }
        }
        free(a);
        dump_to_file((void*) URtoDF_Move, sizeof(URtoDF_Move), "URtoDF_Move", cache_dir);
    }

    if(check_cached_table("URtoUL_Move", (void*) URtoUL_Move, sizeof(URtoUL_Move), cache_dir) != 0) {
        short i;
        int k, j;
        a = get_cubiecube();
        for (i = 0; i < N_URtoUL; i++) {
            setURtoUL(a, i);
            for (j = 0; j < 6; j++) {
                for (k = 0; k < 3; k++) {
                    edgeMultiply(a, &moveCube[j]);
                    URtoUL_Move[i][3 * j + k] = getURtoUL(a);
                }
                edgeMultiply(a, &moveCube[j]);
            }
        }
        free(a);
        dump_to_file((void*) URtoUL_Move, sizeof(URtoUL_Move), "URtoUL_Move", cache_dir);
    }

    if(check_cached_table("UBtoDF_Move", (void*) UBtoDF_Move, sizeof(UBtoDF_Move), cache_dir) != 0) {
        short i;
        int k, j;
        a = get_cubiecube();
        for (i = 0; i < N_UBtoDF; i++) {
            setUBtoDF(a, i);
            for (j = 0; j < 6; j++) {
                for (k = 0; k < 3; k++) {
                    edgeMultiply(a, &moveCube[j]);
                    UBtoDF_Move[i][3 * j + k] = getUBtoDF(a);
                }
                edgeMultiply(a, &moveCube[j]);
            }
        }
        free(a);
        dump_to_file((void*) UBtoDF_Move, sizeof(UBtoDF_Move), "UBtoDF_Move", cache_dir);
    }

    if(check_cached_table("MergeURtoULandUBtoDF", (void*) MergeURtoULandUBtoDF, sizeof(MergeURtoULandUBtoDF), cache_dir) != 0) {
        // for i, j <336 the six edges UR,UF,UL,UB,DR,DF are not in the
        // UD-slice and the index is <20160
        short uRtoUL, uBtoDF;
        for (uRtoUL = 0; uRtoUL < 336; uRtoUL++) {
            for (uBtoDF = 0; uBtoDF < 336; uBtoDF++) {
                MergeURtoULandUBtoDF[uRtoUL][uBtoDF] = (short) getURtoDF_standalone(uRtoUL, uBtoDF);
            }
        }
        dump_to_file((void*) MergeURtoULandUBtoDF, sizeof(MergeURtoULandUBtoDF), "MergeURtoULandUBtoDF", cache_dir);
    }

    if(check_cached_table("Slice_URFtoDLF_Parity_Prun", (void*) Slice_URFtoDLF_Parity_Prun, sizeof(Slice_URFtoDLF_Parity_Prun), cache_dir) != 0) {
        int depth = 0, done = 1;
        int i, j;
        for (i = 0; i < N_SLICE2 * N_URFtoDLF * N_PARITY / 2; i++)
            Slice_URFtoDLF_Parity_Prun[i] = -1;
        setPruning(Slice_URFtoDLF_Parity_Prun, 0, 0);
        printf("1\n");
        while (done != N_SLICE2 * N_URFtoDLF * N_PARITY) {
            // printf("%d %d %d\n", done, N_SLICE2 * N_URFtoDLF * N_PARITY, depth);
            for (i = 0; i < N_SLICE2 * N_URFtoDLF * N_PARITY; i++) {
                int parity = i % 2;
                int URFtoDLF = (i / 2) / N_SLICE2;
                int slice = (i / 2) % N_SLICE2;
                if (getPruning(Slice_URFtoDLF_Parity_Prun, i) == depth) {
                    for (j = 0; j < 18; j++) {
                        int newSlice;
                        int newURFtoDLF;
                        int newParity;
                        switch (j) {
                        case 3:
                        case 5:
                        case 6:
                        case 8:
                        case 12:
                        case 14:
                        case 15:
                        case 17:
                            continue;
                        default:
                            newSlice = FRtoBR_Move[slice][j];
                            newURFtoDLF = URFtoDLF_Move[URFtoDLF][j];
                            newParity = parityMove[parity][j];
                            if (getPruning(Slice_URFtoDLF_Parity_Prun, (N_SLICE2 * newURFtoDLF + newSlice) * 2 + newParity) == 0x0f) {
                                setPruning(Slice_URFtoDLF_Parity_Prun, (N_SLICE2 * newURFtoDLF + newSlice) * 2 + newParity,
                                        (signed char) (depth + 1));
                                done++;
                            }
                        }
                    }
                }
            }
            depth++;
        }
        printf("2\n");
        dump_to_file((void*) Slice_URFtoDLF_Parity_Prun, sizeof(Slice_URFtoDLF_Parity_Prun), "Slice_URFtoDLF_Parity_Prun", cache_dir);
        printf("3\n");
    }

    if(check_cached_table("Slice_URtoDF_Parity_Prun", (void*) Slice_URtoDF_Parity_Prun, sizeof(Slice_URtoDF_Parity_Prun), cache_dir) != 0) {
        int depth = 0, done = 1;
        int i, j;
        for (i = 0; i < N_SLICE2 * N_URtoDF * N_PARITY / 2; i++)
            Slice_URtoDF_Parity_Prun[i] = -1;
        setPruning(Slice_URtoDF_Parity_Prun, 0, 0);
        while (done != N_SLICE2 * N_URtoDF * N_PARITY) {
            for (i = 0; i < N_SLICE2 * N_URtoDF * N_PARITY; i++) {
                int parity = i % 2;
                int URtoDF = (i / 2) / N_SLICE2;
                int slice = (i / 2) % N_SLICE2;
                if (getPruning(Slice_URtoDF_Parity_Prun, i) == depth) {
                    for (j = 0; j < 18; j++) {
                        int newSlice;
                        int newURtoDF;
                        int newParity;
                        switch (j) {
                        case 3:
                        case 5:
                        case 6:
                        case 8:
                        case 12:
                        case 14:
                        case 15:
                        case 17:
                            continue;
                        default:
                            newSlice = FRtoBR_Move[slice][j];
                            newURtoDF = URtoDF_Move[URtoDF][j];
                            newParity = parityMove[parity][j];
                            if (getPruning(Slice_URtoDF_Parity_Prun, (N_SLICE2 * newURtoDF + newSlice) * 2 + newParity) == 0x0f) {
                                setPruning(Slice_URtoDF_Parity_Prun, (N_SLICE2 * newURtoDF + newSlice) * 2 + newParity,
                                        (signed char) (depth + 1));
                                done++;
                            }
                        }
                    }
                }
            }
            depth++;
        }
        dump_to_file((void*) Slice_URtoDF_Parity_Prun, sizeof(Slice_URtoDF_Parity_Prun), "Slice_URtoDF_Parity_Prun", cache_dir);
    }

    if(check_cached_table("Slice_Twist_Prun", (void*) Slice_Twist_Prun, sizeof(Slice_Twist_Prun), cache_dir) != 0) {
        int depth = 0, done = 1;
        int i, j;
        for (i = 0; i < N_SLICE1 * N_TWIST / 2 + 1; i++)
            Slice_Twist_Prun[i] = -1;
        setPruning(Slice_Twist_Prun, 0, 0);
        while (done != N_SLICE1 * N_TWIST) {
            for (i = 0; i < N_SLICE1 * N_TWIST; i++) {
                int twist = i / N_SLICE1, slice = i % N_SLICE1;
                if (getPruning(Slice_Twist_Prun, i) == depth) {
                    for (j = 0; j < 18; j++) {
                        int newSlice = FRtoBR_Move[slice * 24][j] / 24;
                        int newTwist = twistMove[twist][j];
                        if (getPruning(Slice_Twist_Prun, N_SLICE1 * newTwist + newSlice) == 0x0f) {
                            setPruning(Slice_Twist_Prun, N_SLICE1 * newTwist + newSlice, (signed char) (depth + 1));
                            done++;
                        }
                    }
                }
            }
            depth++;
        }
        dump_to_file((void*) Slice_Twist_Prun, sizeof(Slice_Twist_Prun), "Slice_Twist_Prun", cache_dir);
    }

    if(check_cached_table("Slice_Flip_Prun", (void*) Slice_Flip_Prun, sizeof(Slice_Flip_Prun), cache_dir) != 0) {
        int depth = 0, done = 1;
        int i, j;
        for (i = 0; i < N_SLICE1 * N_FLIP / 2; i++)
            Slice_Flip_Prun[i] = -1;
        setPruning(Slice_Flip_Prun, 0, 0);
        while (done != N_SLICE1 * N_FLIP) {
            for (i = 0; i < N_SLICE1 * N_FLIP; i++) {
                int flip = i / N_SLICE1, slice = i % N_SLICE1;
                if (getPruning(Slice_Flip_Prun, i) == depth) {
                    for (j = 0; j < 18; j++) {
                        int newSlice = FRtoBR_Move[slice * 24][j] / 24;
                        int newFlip = flipMove[flip][j];
                        if (getPruning(Slice_Flip_Prun, N_SLICE1 * newFlip + newSlice) == 0x0f) {
                            setPruning(Slice_Flip_Prun, N_SLICE1 * newFlip + newSlice, (signed char) (depth + 1));
                            done++;
                        }
                    }
                }
            }
            depth++;
        }
        dump_to_file((void*) Slice_Flip_Prun, sizeof(Slice_Flip_Prun), "Slice_Flip_Prun", cache_dir);
    }

    PRUNING_INITED = 1;
}

void setPruning(signed char *table, int index, signed char value) {
    if ((index & 1) == 0)
        table[index / 2] &= 0xf0 | value;
    else
        table[index / 2] &= 0x0f | (value << 4);
}

// Extract pruning value
signed char getPruning(signed char *table, int index) {
    signed char res;

    if ((index & 1) == 0)
        res = (table[index / 2] & 0x0f);
    else
        res = ((table[index / 2] >> 4) & 0x0f);

    return res;
}

#endif
