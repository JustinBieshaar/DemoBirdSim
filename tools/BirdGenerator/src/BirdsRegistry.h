#pragma once
#include "BirdFactory.h"
#include "BirdDefines.h"

namespace BirdsRegistry {
    inline std::shared_ptr<Bird> Goose() {
        return BirdFactory::getInstance().getBird(BIRD_GOOSE);
    }
    inline std::shared_ptr<Bird> Gull() {
        return BirdFactory::getInstance().getBird(BIRD_GULL);
    }
    inline std::shared_ptr<Bird> Robin() {
        return BirdFactory::getInstance().getBird(BIRD_ROBIN);
    }
}
