#include "cache.h"


#define GHB_SIZE 256
#define IT_SIZE 256
#define look_head 1
#define degree 20
#define NLL 256

uint64_t cur_idx = 0;

struct IT_entry {
    uint32_t ghb_ptr = NLL;
} IT[IT_SIZE];

struct GHB_entry {
    uint64_t addr;
    uint32_t prev = NLL;
} GHB[GHB_SIZE];

void ghb_init(uint64_t addr, uint64_t ip) {
    if(IT[ip % IT_SIZE].ghb_ptr == NLL)
        GHB[cur_idx].prev = NLL;
    else
        GHB[cur_idx].prev = IT[ip % IT_SIZE].ghb_ptr;

    GHB[cur_idx].addr = addr >> LOG2_BLOCK_SIZE;
    IT[ip % IT_SIZE].ghb_ptr = cur_idx;
}

bool find3miss() {
    uint64_t second_idx = GHB[cur_idx].prev;
    if(second_idx != NLL && GHB[second_idx].prev != NLL) 
        return 1;
    return 0;
}

uint64_t check_stride() {
    uint64_t second_idx = GHB[cur_idx].prev;
    uint64_t third_idx = GHB[second_idx].prev;
    uint64_t s1 = GHB[cur_idx].addr - GHB[second_idx].addr;
    uint64_t s2 = GHB[second_idx].addr - GHB[third_idx].addr;
    if(s1 == s2)
        return s1;
    return 0;
}