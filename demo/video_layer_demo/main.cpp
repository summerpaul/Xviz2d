/**
 * @Author: Xia Yunkai
 * @Date:   2024-06-08 17:51:03
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-06-08 18:06:29
 */
#include <iostream>
#include "app/app.h"
#include "video_layer_demo.h"
#include "basis/logger.h"
using namespace std;

int main(int argc, char const *argv[])
{
	setlocale(LC_ALL, ".utf8");
    auto app = app::App::GetInstance();
    CHECK_RETURN_RET_LOG(!app->Init("VideoLayer"), -1, LOG_LEVEL_ERROR, "failed to initialize");
    std::shared_ptr<VideoLayer> layer = std::make_shared<VideoLayer>("VideoLayer");
    CHECK_RETURN_RET_LOG(!layer->Init(), -1, LOG_LEVEL_ERROR, "failed to initialize");
    app->AddLayer(layer);
    app->Run();
    app->Shutdown();
    return 0;
}
