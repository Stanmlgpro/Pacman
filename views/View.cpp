//
// Created by stan1 on 06/11/2025.
//

#include "View.h"

#include <utility>
namespace views {
View::View(std::weak_ptr<entities::Entity> entity, std::shared_ptr<Camera> camera) {
    // initiate variables
    this->entity = std::move(entity);
    this->camera = std::move(camera);
}
} // namespace views