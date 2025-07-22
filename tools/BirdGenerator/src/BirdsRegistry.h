#pragma once
#include "BirdFactory.h"
#include "BirdDefines.h"

namespace BirdsRegistry {
    inline std::shared_ptr<Bird> Goose() {
        return BirdFactory::getInstance().getBird(BIRD_GOOSE);
    }
    inline std::shared_ptr<Bird> RobinBlue() {
        return BirdFactory::getInstance().getBird(BIRD_ROBINBLUE);
    }
    inline std::shared_ptr<Bird> Robin() {
        return BirdFactory::getInstance().getBird(BIRD_ROBIN);
    }
    inline std::shared_ptr<Bird> Capsule() {
        return BirdFactory::getInstance().getBird(BIRD_CAPSULE);
    }
}
