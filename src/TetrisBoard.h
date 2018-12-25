#pragma once
#include "Util.h"

enum TetrisClusterType {
    None,
    S,
    Z,
    L,
    RevL,
    Sqaure,
    Line
};


struct TetrisBlock {
    int offset_x;
    int offset_y;
    bool is_center;
};

struct TetrisCluster {
    int center_x;
    int center_y;
    TetrisClusterType tetrisClusterType;
    TetrisBlock blocks[4];
};

static constexpr Color BLOCK_COLORS[6] = {Color{255, 0, 0}, Color{0, 255, 0}, Color{0, 0, 255}, Color{255, 0, 255}, Color{255, 255, 0}, Color{0, 255, 255}};

class TetrisBoard {
    public:

        void init();
        //returns true if the board state was updated, false otherwise
        bool update();
        TetrisClusterType getIndex(int x, int y);

    private:
        void generateNextCluster();
        bool checkForOverlapAndAtEdge();

        //we can copy a random element from this array and have our new block!
        TetrisCluster preBuiltClusters[6];
        TetrisClusterType currentBoard[28][10];
        TetrisCluster currentCluster;
        int frame_count;
        int frame_threshold;
};