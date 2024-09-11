#include <stdio.h>
#include <stdlib.h>



int64_t calc_max_size(int64_t block_size,
        int64_t block_num_size, int64_t inode_direct_block_count)
{
    long long res1, res2;

    while (1) {
        long long cur_size = block_size/block_num_size;
        res2 = cur_size;
        if (__builtin_saddll_overflow(inode_direct_block_count,
                cur_size, &res1) == 1) {;
            res1 = -1;
            break;
        }
        if (__builtin_smulll_overflow(cur_size,
                cur_size, &cur_size) == 1) {
            res1 = -1;
            break;
        }
        if (__builtin_saddll_overflow(res1,
                cur_size, &res1) == 1) {
            res1 = -1;
            break;
        }
        if (__builtin_smulll_overflow(cur_size,
                res2, &cur_size) == 1) {
            res1 = -1;
            break;
        }
        if (__builtin_saddll_overflow(res1,
                cur_size, &res1) == 1) {
            res1 = -1;
            break;
        }

        if (__builtin_smulll_overflow(res1,
                block_size, &res1) == 1) {
            res1 = -1;
            break;
        }
        break;
    }

    res2 = -1;
    if (block_num_size < 8) {
        res2 = 1LL<<(block_num_size * __CHAR_BIT__);
        if (__builtin_smulll_overflow(res2,
                block_size, &res2) == 1) {
            return res1;
        }
    }

    if (res1 == -1) {
        return res2;
    } else if (res2 == -1) {
        return res1;
    } else if (res1 <= res2) {
        return res1;
    }
    return res2;
}


int main(void)
{
    long long block_size, block_num_size,
            inode_direct_block_count;

    scanf("%lld %lld %lld", &block_size,
          &block_num_size, &inode_direct_block_count);

    long long res = calc_max_size(block_size,
            block_num_size, inode_direct_block_count);
    printf("%lld\n", res);


    long long val = 1;
    res = calc_max_size(block_size, val,
        inode_direct_block_count);
    long long n_val = 2;
    long long n_res = calc_max_size(block_size, n_val,
        inode_direct_block_count);
    while (1) {
        if (n_val >= 8) {
            printf("%lld %lld\n", val, res);
            exit(EXIT_SUCCESS);
        } else if (n_res == -1) {
            printf("%lld %lld\n", n_val, n_res);
            exit(EXIT_SUCCESS);
        } else if (n_res <= res) {
            printf("%lld %lld\n", val, res);
            exit(EXIT_SUCCESS);
        }
        val = n_val;
        res = n_res;
        ++n_val;
        n_res = calc_max_size(block_size, n_val,
            inode_direct_block_count);
    }
}