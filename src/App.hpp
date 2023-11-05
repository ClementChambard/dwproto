#include <Engine.hpp>

#define WINDOW_WIDTH (/*384 * 2 */1920)
#define WINDOW_HEIGHT (/*448 * 2 */1080)

class App : public NSEngine::IEngine {
public:
    App() : IEngine(WINDOW_WIDTH, WINDOW_HEIGHT, "ecl viewer") {}
    ~App() override {}

    void on_create() override;
    void on_update() override;
    void on_render() override;
    void on_destroy() override;
};
