//
// Created by morten on 07/08/14.
//

#include "touch_input.h"

#include <vector>
#include <iostream>
#include "glm/gtx/string_cast.hpp"

using namespace std;
using namespace glm;

namespace kick{
    std::map<int64_t,Touch> TouchInput::touches;

    void TouchInput::setTouchStarted(int64_t fingerid, glm::ivec2 pos, float pressure) {
        Touch touch;
        touch.down = true;
        touch.up   = false;
        touch.fingerId   = fingerid;
        touch.pos   = pos;
        touch.delta   = {0,0};
        touch.pressure   = pressure;
        touches[fingerid] = touch;
    }

    void TouchInput::setTouchMoved(int64_t fingerid, glm::ivec2 pos, float pressure) {
        auto & touch = touches[fingerid];

        touch.delta = pos - touch.pos;
        touch.pos = pos;
        touch.pressure = pressure;
    }

    void TouchInput::setTouchEnded(int64_t fingerid, glm::ivec2 pos) {
        auto & touch = touches[fingerid];
        touch.delta = pos - touch.pos;
        touch.pos = pos;
        touch.pressure = 0;
        touch.up = true;
    }

    void TouchInput::reset() {
        vector<long> deleteKeys;
        for (auto keyVal : touches){
            keyVal.second.down = false;
            keyVal.second.delta = ivec2{0};
            if (keyVal.second.up){
                deleteKeys.push_back(keyVal.first);
            }
        }

        for (long del : deleteKeys){
            touches.erase(del);
        }
    }

    std::map<int64_t, Touch>::const_iterator TouchInput::begin() {
        return touches.begin();
    }

    map<int64_t, Touch>::const_iterator TouchInput::end() {
        return touches.end();
    }
}