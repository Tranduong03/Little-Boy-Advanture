// thư viện này dùng để thực hiện random số ngẫu nhiên mỗi khi gọi
#pragma once
#include<stdlib.h>
#include<math.h>
#include<time.h>

// Khởi tạo giá trị seed cho hàm rand() bằng thời gian hiện tại
void _Random() 
{
    srand((unsigned int)time(NULL));
}

// trả về giá trị từ 0 -> a
int _rand(int a)
{
    return rand() % a;
}  