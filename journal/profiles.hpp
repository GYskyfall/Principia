#pragma once

#include "base/not_null.hpp"
#include "journal/player.hpp"
#include "ksp_plugin/interface.hpp"
#include "serialization/journal.pb.h"

namespace principia {

using base::not_null;
using ksp_plugin::KSPPart;
using ksp_plugin::LineAndIterator;
using ksp_plugin::NavigationFrame;
using ksp_plugin::NavigationFrameParameters;
using ksp_plugin::Plugin;
using ksp_plugin::QP;
using ksp_plugin::WXYZ;
using ksp_plugin::XYZ;
using ksp_plugin::XYZSegment;

namespace journal {

struct InitGoogleLogging {
  using Message = serialization::InitGoogleLogging;
  static void Run(Message const& message,
                  not_null<Player::PointerMap*> const pointer_map);
};

struct SetBufferedLogging {
  struct In {
    int const max_severity;
  };

  using Message = serialization::SetBufferedLogging;
  static void Fill(In const& in, not_null<Message*> const message);
  static void Run(Message const& message,
                  not_null<Player::PointerMap*> const pointer_map);
};

struct GetBufferedLogging {
  using Return = int;

  using Message = serialization::GetBufferedLogging;
  static void Fill(Return const& result, not_null<Message*> const message);
  static void Run(Message const& message,
                  not_null<Player::PointerMap*> const pointer_map);
};

struct SetBufferDuration {
  struct In {
    int const seconds;
  };

  using Message = serialization::SetBufferDuration;
  static void Fill(In const& in, not_null<Message*> const message);
  static void Run(Message const& message,
                  not_null<Player::PointerMap*> const pointer_map);
};

struct GetBufferDuration {
  using Return = int;

  using Message = serialization::GetBufferDuration;
  static void Fill(Return const& result, not_null<Message*> const message);
  static void Run(Message const& message,
                  not_null<Player::PointerMap*> const pointer_map);
};

struct SetSuppressedLogging {
  struct In {
    int const min_severity;
  };

  using Message = serialization::SetSuppressedLogging;
  static void Fill(In const& in, not_null<Message*> const message);
  static void Run(Message const& message,
                  not_null<Player::PointerMap*> const pointer_map);
};

struct GetSuppressedLogging {
  using Return = int;

  using Message = serialization::GetSuppressedLogging;
  static void Fill(Return const& result, not_null<Message*> const message);
  static void Run(Message const& message,
                  not_null<Player::PointerMap*> const pointer_map);
};

struct SetVerboseLogging {
  struct In {
    int const level;
  };

  using Message = serialization::SetVerboseLogging;
  static void Fill(In const& in, not_null<Message*> const message);
  static void Run(Message const& message,
                  not_null<Player::PointerMap*> const pointer_map);
};

struct GetVerboseLogging {
  using Return = int;

  using Message = serialization::GetVerboseLogging;
  static void Fill(Return const& result, not_null<Message*> const message);
  static void Run(Message const& message,
                  not_null<Player::PointerMap*> const pointer_map);
};

struct SetStderrLogging {
  struct In {
    int const min_severity;
  };

  using Message = serialization::SetStderrLogging;
  static void Fill(In const& in, not_null<Message*> const message);
  static void Run(Message const& message,
                  not_null<Player::PointerMap*> const pointer_map);
};

struct GetStderrLogging {
  using Return = int;

  using Message = serialization::GetStderrLogging;
  static void Fill(Return const& result, not_null<Message*> const message);
  static void Run(Message const& message,
                  not_null<Player::PointerMap*> const pointer_map);
};

struct LogInfo {
  struct In {
    char const* const message;
  };

  using Message = serialization::LogInfo;
  static void Fill(In const& in, not_null<Message*> const message);
  static void Run(Message const& message,
                  not_null<Player::PointerMap*> const pointer_map);
};

struct LogWarning {
  struct In {
    char const* const message;
  };

  using Message = serialization::LogWarning;
  static void Fill(In const& in, not_null<Message*> const message);
  static void Run(Message const& message,
                  not_null<Player::PointerMap*> const pointer_map);
};

struct LogError {
  struct In {
    char const* const message;
  };

  using Message = serialization::LogError;
  static void Fill(In const& in, not_null<Message*> const message);
  static void Run(Message const& message,
                  not_null<Player::PointerMap*> const pointer_map);
};

struct LogFatal {
  struct In {
    char const* const message;
  };

  using Message = serialization::LogFatal;
  static void Fill(In const& in, not_null<Message*> const message);
  static void Run(Message const& message,
                  not_null<Player::PointerMap*> const pointer_map);
};

struct NewPlugin {
  struct In {
    double const initial_time;
    double const planetarium_rotation_in_degrees;
  };
  using Return = Plugin*;

  using Message = serialization::NewPlugin;
  static void Fill(In const& in, not_null<Message*> const message);
  static void Fill(Return const& result, not_null<Message*> const message);
  static void Run(Message const& message,
                  not_null<Player::PointerMap*> const pointer_map);
};

struct DeletePlugin {
  struct In {
    Plugin const** const plugin;
  };
  struct Out {
    Plugin const** const plugin;
  };

  using Message = serialization::DeletePlugin;
  static void Fill(In const& in, not_null<Message*> const message);
  static void Fill(Out const& out, not_null<Message*> const message);
  static void Run(Message const& message,
                  not_null<Player::PointerMap*> const pointer_map);
};

struct DirectlyInsertCelestial {
  struct In {
    Plugin* const plugin;
    int const celestial_index;
    int const* const parent_index;
    char const* const gravitational_parameter;
    char const* const axis_right_ascension;
    char const* const axis_declination;
    char const* const j2;
    char const* const reference_radius;
    char const* const x;
    char const* const y;
    char const* const z;
    char const* const vx;
    char const* const vy;
    char const* const vz;
  };

  using Message = serialization::DirectlyInsertCelestial;
  static void Fill(In const& in, not_null<Message*> const message);
  static void Run(Message const& message,
                  not_null<Player::PointerMap*> const pointer_map);
};

struct InsertCelestial {
  struct In {
    Plugin* const plugin;
    int const celestial_index;
    double const gravitational_parameter;
    int const parent_index;
    QP const from_parent;
  };

  using Message = serialization::InsertCelestial;
  static void Fill(In const& in, not_null<Message*> const message);
  static void Run(Message const& message,
                  not_null<Player::PointerMap*> const pointer_map);
};

struct InsertSun {
  struct In {
    Plugin* const plugin;
    int const celestial_index;
    double const gravitational_parameter;
  };

  using Message = serialization::InsertSun;
  static void Fill(In const& in, not_null<Message*> const message);
  static void Run(Message const& message,
                  not_null<Player::PointerMap*> const pointer_map);
};

struct UpdateCelestialHierarchy {
  struct In {
    Plugin const* const plugin;
    int const celestial_index;
    int const parent_index;
  };

  using Message = serialization::UpdateCelestialHierarchy;
  static void Fill(In const& in, not_null<Message*> const message);
  static void Run(Message const& message,
                  not_null<Player::PointerMap*> const pointer_map);
};

struct EndInitialization {
  struct In {
    Plugin const* const plugin;
  };

  using Message = serialization::EndInitialization;
  static void Fill(In const& in, not_null<Message*> const message);
  static void Run(Message const& message,
                  not_null<Player::PointerMap*> const pointer_map);
};

struct InsertOrKeepVessel {
  struct In {
    Plugin* const plugin;
    char const* const vessel_guid;
    int const parent_index;
  };
  using Return = bool;

  using Message = serialization::InsertOrKeepVessel;
  static void Fill(In const& in, not_null<Message*> const message);
  static void Fill(Return const& result, not_null<Message*> const message);
  static void Run(Message const& message,
                  not_null<Player::PointerMap*> const pointer_map);
};

struct SetVesselStateOffset {
  struct In {
    Plugin* const plugin;
    char const* const vessel_guid;
    QP const from_parent;
  };

  using Message = serialization::SetVesselStateOffset;
  static void Fill(In const& in, not_null<Message*> const message);
  static void Run(Message const& message,
                  not_null<Player::PointerMap*> const pointer_map);
};

struct AdvanceTime {
  struct In {
    Plugin* const plugin;
    double const t;
    double const planetarium_rotation;
  };

  using Message = serialization::AdvanceTime;
  static void Fill(In const& in, not_null<Message*> const message);
  static void Run(Message const& message,
                  not_null<Player::PointerMap*> const pointer_map);
};

struct ForgetAllHistoriesBefore {
  struct In {
    Plugin* const plugin;
    double const t;
  };

  using Message = serialization::ForgetAllHistoriesBefore;
  static void Fill(In const& in, not_null<Message*> const message);
  static void Run(Message const& message,
                  not_null<Player::PointerMap*> const pointer_map);
};

struct VesselFromParent {
  struct In {
    Plugin const* const plugin;
    char const* const vessel_guid;
  };
  using Return = QP;

  using Message = serialization::VesselFromParent;
  static void Fill(In const& in, not_null<Message*> const message);
  static void Fill(Return const& result, not_null<Message*> const message);
  static void Run(Message const& message,
                  not_null<Player::PointerMap*> const pointer_map);
};

struct CelestialFromParent {
  struct In {
    Plugin const* const plugin;
    int const celestial_index;
  };
  using Return = QP;

  using Message = serialization::CelestialFromParent;
  static void Fill(In const& in, not_null<Message*> const message);
  static void Fill(Return const& result, not_null<Message*> const message);
  static void Run(Message const& message,
                  not_null<Player::PointerMap*> const pointer_map);
};

struct NewBodyCentredNonRotatingNavigationFrame {
  struct In {
    Plugin const* const plugin;
    int const reference_body_index;
  };
  using Return = NavigationFrame*;

  using Message = serialization::NewBodyCentredNonRotatingNavigationFrame;
  static void Fill(In const& in, not_null<Message*> const message);
  static void Fill(Return const& result, not_null<Message*> const message);
  static void Run(Message const& message,
                  not_null<Player::PointerMap*> const pointer_map);
};

struct NewBarycentricRotatingNavigationFrame {
  struct In {
    Plugin const* const plugin;
    int const primary_index;
    int const secondary_index;
  };
  using Return = NavigationFrame*;

  using Message = serialization::NewBarycentricRotatingNavigationFrame;
  static void Fill(In const& in, not_null<Message*> const message);
  static void Fill(Return const& result, not_null<Message*> const message);
  static void Run(Message const& message,
                  not_null<Player::PointerMap*> const pointer_map);
};

struct NewNavigationFrame {
  struct In {
    Plugin const* const plugin;
    NavigationFrameParameters const parameters;
  };
  using Return = NavigationFrame*;

  using Message = serialization::NewNavigationFrame;
  static void Fill(In const& in, not_null<Message*> const message);
  static void Fill(Return const& result, not_null<Message*> const message);
  static void Run(Message const& message,
                  not_null<Player::PointerMap*> const pointer_map);
};

struct GetNavigationFrameParameters {
  struct In {
    NavigationFrame const* const navigation_frame;
  };
  using Return = NavigationFrameParameters;

  using Message = serialization::GetNavigationFrameParameters;
  static void Fill(In const& in, not_null<Message*> const message);
  static void Fill(Return const& result, not_null<Message*> const message);
  static void Run(Message const& message,
                  not_null<Player::PointerMap*> const pointer_map);
};

struct SetPlottingFrame {
  struct In {
    Plugin* const plugin;
    NavigationFrame** const navigation_frame;
  };
  struct Out {
    NavigationFrame** const navigation_frame;
  };

  using Message = serialization::SetPlottingFrame;
  static void Fill(In const& in, not_null<Message*> const message);
  static void Fill(Out const& out, not_null<Message*> const message);
  static void Run(Message const& message,
                  not_null<Player::PointerMap*> const pointer_map);
};

struct GetPlottingFrame {
  struct In {
    Plugin const* const plugin;
  };
  using Return = NavigationFrame const*;

  using Message = serialization::GetPlottingFrame;
  static void Fill(In const& in, not_null<Message*> const message);
  static void Fill(Return const& result, not_null<Message*> const message);
  static void Run(Message const& message,
                  not_null<Player::PointerMap*> const pointer_map);
};

struct UpdatePrediction {
  struct In {
    Plugin const* const plugin;
    char const* const vessel_guid;
  };

  using Message = serialization::UpdatePrediction;
  static void Fill(In const& in, not_null<Message*> const message);
  static void Run(Message const& message,
                  not_null<Player::PointerMap*> const pointer_map);
};

struct RenderedVesselTrajectory {
  struct In {
    Plugin const* const plugin;
    char const* const vessel_guid;
    XYZ const sun_world_position;
  };
  using Return = LineAndIterator*;

  using Message = serialization::RenderedVesselTrajectory;
  static void Fill(In const& in, not_null<Message*> const message);
  static void Fill(Return const& result, not_null<Message*> const message);
  static void Run(Message const& message,
                  not_null<Player::PointerMap*> const pointer_map);
};

struct HasPrediction {
  struct In {
    Plugin const* const plugin;
    char const* const vessel_guid;
  };
  using Return = bool;

  using Message = serialization::HasPrediction;
  static void Fill(In const& in, not_null<Message*> const message);
  static void Fill(Return const& result, not_null<Message*> const message);
  static void Run(Message const& message,
                  not_null<Player::PointerMap*> const pointer_map);
};

struct RenderedPrediction {
  struct In {
    Plugin* const plugin;
    char const* const vessel_guid;
    XYZ const sun_world_position;
  };
  using Return = LineAndIterator*;

  using Message = serialization::RenderedPrediction;
  static void Fill(In const& in, not_null<Message*> const message);
  static void Fill(Return const& result, not_null<Message*> const message);
  static void Run(Message const& message,
                  not_null<Player::PointerMap*> const pointer_map);
};

struct FlightPlanSize {
  struct In {
    Plugin const* const plugin;
    char const* const vessel_guid;
  };
  using Return = int;

  using Message = serialization::FlightPlanSize;
  static void Fill(In const& in, not_null<Message*> const message);
  static void Fill(Return const& result, not_null<Message*> const message);
  static void Run(Message const& message,
                  not_null<Player::PointerMap*> const pointer_map);
};

struct RenderedFlightPlan {
  struct In {
    Plugin* const plugin;
    char const* const vessel_guid;
    int const plan_phase;
    XYZ const sun_world_position;
  };
  using Return = LineAndIterator*;

  using Message = serialization::RenderedFlightPlan;
  static void Fill(In const& in, not_null<Message*> const message);
  static void Fill(Return const& result, not_null<Message*> const message);
  static void Run(Message const& message,
                  not_null<Player::PointerMap*> const pointer_map);
};

struct SetPredictionLength {
  struct In {
    Plugin* const plugin;
    double const t;
  };

  using Message = serialization::SetPredictionLength;
  static void Fill(In const& in, not_null<Message*> const message);
  static void Run(Message const& message,
                  not_null<Player::PointerMap*> const pointer_map);
};

struct SetPredictionLengthTolerance {
  struct In {
    Plugin* const plugin;
    double const l;
  };

  using Message = serialization::SetPredictionLengthTolerance;
  static void Fill(In const& in, not_null<Message*> const message);
  static void Run(Message const& message,
                  not_null<Player::PointerMap*> const pointer_map);
};

struct SetPredictionSpeedTolerance {
  struct In {
    Plugin* const plugin;
    double const v;
  };

  using Message = serialization::SetPredictionSpeedTolerance;
  static void Fill(In const& in, not_null<Message*> const message);
  static void Run(Message const& message,
                  not_null<Player::PointerMap*> const pointer_map);
};

struct HasVessel {
  struct In {
    Plugin* const plugin;
    char const* const vessel_guid;
  };
  using Return = bool;

  using Message = serialization::HasVessel;
  static void Fill(In const& in, not_null<Message*> const message);
  static void Fill(Return const& result, not_null<Message*> const message);
  static void Run(Message const& message,
                  not_null<Player::PointerMap*> const pointer_map);
};

struct NumberOfSegments {
  struct In {
    LineAndIterator const* const line_and_iterator;
  };
  using Return = int;

  using Message = serialization::NumberOfSegments;
  static void Fill(In const& in, not_null<Message*> const message);
  static void Fill(Return const& result, not_null<Message*> const message);
  static void Run(Message const& message,
                  not_null<Player::PointerMap*> const pointer_map);
};

struct FetchAndIncrement {
  struct In {
    LineAndIterator* const line_and_iterator;
  };
  using Return = XYZSegment;

  using Message = serialization::FetchAndIncrement;
  static void Fill(In const& in, not_null<Message*> const message);
  static void Fill(Return const& result, not_null<Message*> const message);
  static void Run(Message const& message,
                  not_null<Player::PointerMap*> const pointer_map);
};

struct AtEnd {
  struct In {
    LineAndIterator const* const line_and_iterator;
  };
  using Return = bool;

  using Message = serialization::AtEnd;
  static void Fill(In const& in, not_null<Message*> const message);
  static void Fill(Return const& result, not_null<Message*> const message);
  static void Run(Message const& message,
                  not_null<Player::PointerMap*> const pointer_map);
};

struct DeleteLineAndIterator {
  struct In {
    LineAndIterator** const line_and_iterator;
  };
  struct Out {
    LineAndIterator** const line_and_iterator;
  };

  using Message = serialization::DeleteLineAndIterator;
  static void Fill(In const& in, not_null<Message*> const message);
  static void Fill(Out const& out, not_null<Message*> const message);
  static void Run(Message const& message,
                  not_null<Player::PointerMap*> const pointer_map);
};

struct AddVesselToNextPhysicsBubble {
  struct In {
    Plugin* const plugin;
    char const* const vessel_guid;
    KSPPart const* const parts;
    int count;
  };

  using Message = serialization::AddVesselToNextPhysicsBubble;
  static void Fill(In const& in, not_null<Message*> const message);
  static void Run(Message const& message,
                  not_null<Player::PointerMap*> const pointer_map);
};

struct PhysicsBubbleIsEmpty {
  struct In {
    Plugin const* const plugin;
  };
  using Return = bool;

  using Message = serialization::PhysicsBubbleIsEmpty;
  static void Fill(In const& in, not_null<Message*> const message);
  static void Fill(Return const& result, not_null<Message*> const message);
  static void Run(Message const& message,
                  not_null<Player::PointerMap*> const pointer_map);
};

struct BubbleDisplacementCorrection {
  struct In {
    Plugin const* const plugin;
    XYZ const sun_position;
  };
  using Return = XYZ;

  using Message = serialization::BubbleDisplacementCorrection;
  static void Fill(In const& in, not_null<Message*> const message);
  static void Fill(Return const& result, not_null<Message*> const message);
  static void Run(Message const& message,
                  not_null<Player::PointerMap*> const pointer_map);
};

struct BubbleVelocityCorrection {
  struct In {
    Plugin const* const plugin;
    int const reference_body_index;
  };
  using Return = XYZ;

  using Message = serialization::BubbleVelocityCorrection;
  static void Fill(In const& in, not_null<Message*> const message);
  static void Fill(Return const& result, not_null<Message*> const message);
  static void Run(Message const& message,
                  not_null<Player::PointerMap*> const pointer_map);
};

struct NavballOrientation {
  struct In {
    Plugin const* const plugin;
    XYZ const sun_world_position;
    XYZ const ship_world_position;
  };
  using Return = WXYZ;

  using Message = serialization::NavballOrientation;
  static void Fill(In const& in, not_null<Message*> const message);
  static void Fill(Return const& result, not_null<Message*> const message);
  static void Run(Message const& message,
                  not_null<Player::PointerMap*> const pointer_map);
};

struct VesselTangent {
  struct In {
    Plugin const* const plugin;
    char const* const vessel_guid;
  };
  using Return = XYZ;

  using Message = serialization::VesselTangent;
  static void Fill(In const& in, not_null<Message*> const message);
  static void Fill(Return const& result, not_null<Message*> const message);
  static void Run(Message const& message,
                  not_null<Player::PointerMap*> const pointer_map);
};

struct VesselNormal {
  struct In {
    Plugin const* const plugin;
    char const* const vessel_guid;
  };
  using Return = XYZ;

  using Message = serialization::VesselNormal;
  static void Fill(In const& in, not_null<Message*> const message);
  static void Fill(Return const& result, not_null<Message*> const message);
  static void Run(Message const& message,
                  not_null<Player::PointerMap*> const pointer_map);
};

struct VesselBinormal {
  struct In {
    Plugin const* const plugin;
    char const* const vessel_guid;
  };
  using Return = XYZ;

  using Message = serialization::VesselBinormal;
  static void Fill(In const& in, not_null<Message*> const message);
  static void Fill(Return const& result, not_null<Message*> const message);
  static void Run(Message const& message,
                  not_null<Player::PointerMap*> const pointer_map);
};

struct CurrentTime {
  struct In {
    Plugin const* const plugin;
  };
  using Return = double;

  using Message = serialization::CurrentTime;
  static void Fill(In const& in, not_null<Message*> const message);
  static void Fill(Return const& result, not_null<Message*> const message);
  static void Run(Message const& message,
                  not_null<Player::PointerMap*> const pointer_map);
};

struct SerializePlugin {
  struct In {
    Plugin const* const plugin;
    PullSerializer** const serializer;
  };
  struct Out {
    PullSerializer** const serializer;
  };
  using Return = char const*;

  using Message = serialization::SerializePlugin;
  static void Fill(In const& in, not_null<Message*> const message);
  static void Fill(Out const& out, not_null<Message*> const message);
  static void Fill(Return const& result, not_null<Message*> const message);
  static void Run(Message const& message,
                  not_null<Player::PointerMap*> const pointer_map);
};

struct DeletePluginSerialization {
  struct In {
    char const** const serialization;
  };
  struct Out {
    char const** const serialization;
  };

  using Message = serialization::DeletePluginSerialization;
  static void Fill(In const& in, not_null<Message*> const message);
  static void Fill(Out const& out, not_null<Message*> const message);
  static void Run(Message const& message,
                  not_null<Player::PointerMap*> const pointer_map);
};

struct DeserializePlugin {
  struct In {
    char const* const serialization;
    int const serialization_size;
    PushDeserializer** const deserializer;
    Plugin const** const plugin;
  };
  struct Out {
    PushDeserializer** const deserializer;
    Plugin const** const plugin;
  };

  using Message = serialization::DeserializePlugin;
  static void Fill(In const& in, not_null<Message*> const message);
  static void Fill(Out const& out, not_null<Message*> const message);
  static void Run(Message const& message,
                  not_null<Player::PointerMap*> const pointer_map);
};

struct SayHello {
  using Return = char const*;

  using Message = serialization::SayHello;
  static void Fill(Return const& result, not_null<Message*> const message);
  static void Run(Message const& message,
                  not_null<Player::PointerMap*> const pointer_map);
};

}  // namespace journal
}  // namespace principia
