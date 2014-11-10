#pragma once

#include <vector>

#include "geometry/grassmann.hpp"
#include "geometry/named_quantities.hpp"
#include "geometry/point.hpp"
#include "quantities/named_quantities.hpp"

using principia::geometry::Position;
using principia::geometry::Velocity;
using principia::quantities::Length;
using principia::quantities::Speed;

namespace principia {
namespace physics {

template<typename Frame>
struct DegreesOfFreedom {
  DegreesOfFreedom(Position<Frame> const& position,
                   Velocity<Frame> const& velocity);
  Position<Frame> const position;
  Velocity<Frame> const velocity;
};

template<typename Frame>
bool operator==(DegreesOfFreedom<Frame> const& left,
                DegreesOfFreedom<Frame> const& right);

template<typename Frame, typename Weight>
DegreesOfFreedom<Frame> Barycentre(
    std::vector<DegreesOfFreedom<Frame>> const& degrees_of_freedom,
    std::vector<Weight> const& weights);

}  // namespace physics
}  // namespace principia

#include "physics/degrees_of_freedom_body.hpp"
