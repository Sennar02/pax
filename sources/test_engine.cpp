#include "demo/Main_State.hpp"

void
test_engine()
{
    Main_State state;
    Engine     engine;

    engine.loop(state, 128.0);
}
