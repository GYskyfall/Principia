﻿
#pragma once

#include "geometry/point.hpp"
#include "geometry/grassmann.hpp"
#include "serialization/geometry.pb.h"

namespace principia {
namespace geometry {
namespace internal_affine_map {

using base::not_null;

template<typename FromFrame, typename ToFrame, typename Scalar,
         template<typename, typename> class LinearMap>
class AffineMap final {
 public:
  using FromVector = Vector<Scalar, FromFrame>;
  using ToVector = Vector<Scalar, ToFrame>;

  AffineMap(Point<FromVector> const& from_origin,
            Point<ToVector> const& to_origin,
            LinearMap<FromFrame, ToFrame> const& linear_map);

  AffineMap(AffineMap const&) = default;

  AffineMap<ToFrame, FromFrame, Scalar, LinearMap> Inverse() const;
  Point<ToVector> operator()(Point<FromVector> const& point) const;

  static AffineMap Identity();

  LinearMap<FromFrame, ToFrame> const& linear_map() const;

  void WriteToMessage(not_null<serialization::AffineMap*> message) const;
  static AffineMap ReadFromMessage(serialization::AffineMap const& message);

 private:
  Point<FromVector> from_origin_;
  Point<ToVector> to_origin_;
  LinearMap<FromFrame, ToFrame> linear_map_;

  template<typename From, typename Through, typename To, typename S,
           template<typename, typename> class Map>
  friend AffineMap<From, To, S, Map> operator*(
      AffineMap<Through, To, S, Map> const& left,
      AffineMap<From, Through, S, Map> const& right);
};

template<typename FromFrame, typename ThroughFrame, typename ToFrame,
         typename Scalar, template<typename, typename> class LinearMap>
AffineMap<FromFrame, ToFrame, Scalar, LinearMap> operator*(
    AffineMap<ThroughFrame, ToFrame, Scalar, LinearMap> const& left,
    AffineMap<FromFrame, ThroughFrame, Scalar, LinearMap> const& right);

}  // namespace internal_affine_map

using internal_affine_map::AffineMap;

}  // namespace geometry
}  // namespace principia

#include "geometry/affine_map_body.hpp"
