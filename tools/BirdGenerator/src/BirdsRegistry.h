#pragma once
#include "BirdFactory.h"
#include "BirdDefines.h"

namespace BirdsRegistry {
    inline std::shared_ptr<Bird> Bodine() {
        return BirdFactory::getInstance().getBird(BIRD_BODINE);
    }
    inline std::shared_ptr<Bird> Default() {
        return BirdFactory::getInstance().getBird(BIRD_DEFAULT);
    }
    inline std::shared_ptr<Bird> Robin() {
        return BirdFactory::getInstance().getBird(BIRD_ROBIN);
    }
}
