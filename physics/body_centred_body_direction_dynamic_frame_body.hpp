﻿
#pragma once

#include "physics/body_centred_body_direction_dynamic_frame.hpp"

#include "geometry/named_quantities.hpp"
#include "geometry/r3x3_matrix.hpp"
#include "quantities/quantities.hpp"
#include "quantities/si.hpp"

namespace principia {
namespace physics {
namespace internal_body_centred_body_direction_dynamic_frame {

using geometry::Bivector;
using geometry::Displacement;
using geometry::R3x3Matrix;
using geometry::Velocity;
using geometry::Wedge;
using quantities::GravitationalParameter;
using quantities::Length;
using quantities::Pow;
using quantities::Product;
using quantities::Speed;
using quantities::Variation;
using quantities::si::Radian;

template<typename InertialFrame, typename ThisFrame>
BodyCentredBodyDirectionDynamicFrame<InertialFrame, ThisFrame>::
BodyCentredBodyDirectionDynamicFrame(
    not_null<Ephemeris<InertialFrame> const*> const ephemeris,
    not_null<MassiveBody const*> const primary,
    not_null<MassiveBody const*> const secondary)
    : ephemeris_(ephemeris),
      primary_(primary),
      secondary_(secondary),
      primary_trajectory_(ephemeris_->trajectory(primary_)),
      secondary_trajectory_(ephemeris_->trajectory(secondary_)) {}

template<typename InertialFrame, typename ThisFrame>
RigidMotion<InertialFrame, ThisFrame>
BodyCentredBodyDirectionDynamicFrame<InertialFrame, ThisFrame>::
    ToThisFrameAtTime(Instant const& t) const {
  DegreesOfFreedom<InertialFrame> const primary_degrees_of_freedom =
      primary_trajectory_->EvaluateDegreesOfFreedom(t, &primary_hint_);
  DegreesOfFreedom<InertialFrame> const secondary_degrees_of_freedom =
      secondary_trajectory_->EvaluateDegreesOfFreedom(t, &secondary_hint_);

  Rotation<InertialFrame, ThisFrame> rotation =
      Rotation<InertialFrame, ThisFrame>::Identity();
  AngularVelocity<InertialFrame> angular_velocity;
  ComputeAngularDegreesOfFreedom(primary_degrees_of_freedom,
                                 secondary_degrees_of_freedom,
                                 rotation,
                                 angular_velocity);

  RigidTransformation<InertialFrame, ThisFrame> const
      rigid_transformation(primary_degrees_of_freedom.position(),
                           ThisFrame::origin,
                           rotation.Forget());
  return RigidMotion<InertialFrame, ThisFrame>(
             rigid_transformation,
             angular_velocity,
             primary_degrees_of_freedom.velocity());
}

template<typename InertialFrame, typename ThisFrame>
void BodyCentredBodyDirectionDynamicFrame<InertialFrame, ThisFrame>::
WriteToMessage(not_null<serialization::DynamicFrame*> const message) const {
  auto* const extension =
      message->MutableExtension(
          serialization::BodyCentredBodyDirectionDynamicFrame::extension);
  extension->set_primary(ephemeris_->serialization_index_for_body(primary_));
  extension->set_secondary(
      ephemeris_->serialization_index_for_body(secondary_));
}

template<typename InertialFrame, typename ThisFrame>
not_null<std::unique_ptr<
    BodyCentredBodyDirectionDynamicFrame<InertialFrame, ThisFrame>>>
BodyCentredBodyDirectionDynamicFrame<InertialFrame, ThisFrame>::ReadFromMessage(
    not_null<Ephemeris<InertialFrame> const*> const ephemeris,
    serialization::BodyCentredBodyDirectionDynamicFrame const & message) {
  return std::make_unique<BodyCentredBodyDirectionDynamicFrame>(
      ephemeris,
      ephemeris->body_for_serialization_index(message.primary()),
      ephemeris->body_for_serialization_index(message.secondary()));
}

template<typename InertialFrame, typename ThisFrame>
Vector<Acceleration, InertialFrame>
BodyCentredBodyDirectionDynamicFrame<InertialFrame, ThisFrame>::
GravitationalAcceleration(Instant const& t,
                          Position<InertialFrame> const& q) const {
  return ephemeris_->ComputeGravitationalAccelerationOnMasslessBody(q, t);
}

template<typename InertialFrame, typename ThisFrame>
AcceleratedRigidMotion<InertialFrame, ThisFrame>
BodyCentredBodyDirectionDynamicFrame<InertialFrame, ThisFrame>::
MotionOfThisFrame(Instant const& t) const {
  DegreesOfFreedom<InertialFrame> const primary_degrees_of_freedom =
      primary_trajectory_->EvaluateDegreesOfFreedom(t, &primary_hint_);
  DegreesOfFreedom<InertialFrame> const secondary_degrees_of_freedom =
      secondary_trajectory_->EvaluateDegreesOfFreedom(t, &secondary_hint_);

  Vector<Acceleration, InertialFrame> const primary_acceleration =
      ephemeris_->ComputeGravitationalAccelerationOnMassiveBody(primary_, t);
  Vector<Acceleration, InertialFrame> const secondary_acceleration =
      ephemeris_->ComputeGravitationalAccelerationOnMassiveBody(secondary_, t);

  auto const to_this_frame = ToThisFrameAtTime(t);

  // TODO(egg): TeX and reference.
  RelativeDegreesOfFreedom<InertialFrame> const secondary_primary =
      secondary_degrees_of_freedom - primary_degrees_of_freedom;
  Displacement<InertialFrame> const& r = secondary_primary.displacement();
  Velocity<InertialFrame> const& ṙ = secondary_primary.velocity();
  Vector<Acceleration, InertialFrame> const r̈ =
      secondary_acceleration - primary_acceleration;
  AngularVelocity<InertialFrame> const& ω =
      to_this_frame.angular_velocity_of_to_frame();
  Variation<AngularVelocity<InertialFrame>> const
      angular_acceleration_of_to_frame =
          (Wedge(r, r̈) * Radian - 2 * ω * InnerProduct(r, ṙ)) /
          InnerProduct(r, r);

  Vector<Acceleration, InertialFrame> const& acceleration_of_to_frame_origin =
      primary_acceleration;
  return AcceleratedRigidMotion<InertialFrame, ThisFrame>(
             to_this_frame,
             angular_acceleration_of_to_frame,
             acceleration_of_to_frame_origin);
}

template<typename InertialFrame, typename ThisFrame>
void BodyCentredBodyDirectionDynamicFrame<InertialFrame, ThisFrame>::
ComputeAngularDegreesOfFreedom(
    DegreesOfFreedom<InertialFrame> const& primary_degrees_of_freedom,
    DegreesOfFreedom<InertialFrame> const& secondary_degrees_of_freedom,
    Rotation<InertialFrame, ThisFrame>& rotation,
    AngularVelocity<InertialFrame>& angular_velocity) {
  RelativeDegreesOfFreedom<InertialFrame> const reference =
       secondary_degrees_of_freedom - primary_degrees_of_freedom;
  Displacement<InertialFrame> const& reference_direction =
      reference.displacement();
  Velocity<InertialFrame> const reference_normal =
      reference.velocity().OrthogonalizationAgainst(reference_direction);
  Bivector<Product<Length, Speed>, InertialFrame> const reference_binormal =
      Wedge(reference_direction, reference_normal);
  rotation = Rotation<InertialFrame, ThisFrame>(Normalize(reference_direction),
                                                Normalize(reference_normal),
                                                Normalize(reference_binormal));
  angular_velocity = reference_binormal * Radian /
                     InnerProduct(reference_direction, reference_direction);
}

}  // namespace internal_body_centred_body_direction_dynamic_frame
}  // namespace physics
}  // namespace principia
