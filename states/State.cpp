//
// Created by stan on 10/14/25.
//

#include "State.h"

namespace states {
    State::State(std::weak_ptr<StateManager> statemanager) {
        this->statemanager = std::move(statemanager);
    }

}