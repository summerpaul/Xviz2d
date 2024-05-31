/**
 * @Author: Xia Yunkai
 * @Date:   2024-05-29 18:27:36
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-05-31 16:41:06
 */
#include <iostream>
#include "app/app.h"
#include "basis/logger.h"
#include "demo_draw.h"
#include <thread>
using namespace std;

int main(int argc, char const *argv[])
{
    auto app = app::App::GetInstance();
    CHECK_RETURN_RET_LOG(!app->Init("DEMO"), -1, LOG_LEVEL_ERROR, "failed to initialize");
    const auto scene = app->GetSceneManager();
    bool running = true;
    std::thread demo_thread([&]()
                            {
			while (running)
			{
				SceneDemo(scene);
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
			} });

    app->Run();

    app->Shutdown();
    running = false;

    return 0;
}
