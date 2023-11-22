#pragma once

#include<stdlib.h>
#include<math.h>
#include<time.h>

// Khởi tạo giá trị seed cho hàm rand() bằng thời gian hiện tại

inline void _Random()
{
    srand((unsigned int)time(NULL));
}

// trả về giá trị từ 0 -> a
inline int _rand(int a)
{
    return rand() % a;
}
