/**
 * @Author: Xia Yunkai
 * @Date:   2024-05-28 19:53:28
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-05-29 18:15:27
 */
#include <iostream>
#include "basis/logger.h"

using namespace std;

int main(int argc, char const *argv[])
{

    LOG_INFO("HAHA");
    int data = 3;
    LOG_LEVEL_PRINT(LOG_LEVEL_DEBUG, "haha %d", data);

    return 0;
}
