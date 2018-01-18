/**
 * S.I.M.P.L.E. - Smart Intra-operative Messaging Platform with Less Effort
 * Copyright (C) 2018 Salvatore Virga - salvo.virga@tum.de, Fernanda Levy Langsch - fernanda.langsch@tum.de
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser Public License for more details.
 *
 * You should have received a copy of the GNU Lesser Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SIMPLE_MSGS_POSE_H
#define SIMPLE_MSGS_POSE_H

#include <iostream>

#include "generated/pose_generated.h"
#include "quaternion.h"
#include "point.h"

namespace simple_msgs
{
class Pose : public GenericMessage
{
public:
  Pose();
  Pose(const Point&, const Quaternion&);
  Pose(const uint8_t*);
  Pose(const Pose&);
  Pose(Pose&&);

  Pose& operator=(const Pose&);
  Pose& operator=(Pose&&);
  Pose& operator=(const uint8_t*);

  inline bool operator==(const Pose& rhs) const
  {
    return (position_ == rhs.position_ && quaternion_ == rhs.quaternion_);
  }
  inline bool operator!=(const Pose& rhs) const { return !(*this == rhs); }
  friend std::ostream& operator<<(std::ostream&, const Pose&);

  /**
   * @brief Builds and returns the buffer accordingly to the values currently stored.
   * @return the buffer data.
   */
  uint8_t* getBufferData() const override;

  /**
   * @brief Returns the translational part of the Pose as a Point message.
   */
  const Point& getPosition() const { return position_; }

  /**
   * @brief Returns the rotational part of the Pose as a Quaternion message.
   */
  const Quaternion& getQuaternion() const { return quaternion_; }

  /**
   * @brief Returns the translational part of the Pose as a Point message.
   */
  Point& getPosition() { return position_; }

  /**
   * @brief Returns the rotational part of the Pose as a Quaternion message.
   */
  Quaternion& getQuaternion() { return quaternion_; }

  /**
   * @brief Modifies the rotational part of the Pose.
   */
  void setPosition(const Point&);

  /**
   * @brief Modifies the translational part of the Pose.
   */
  void setQuaternion(const Quaternion&);

  /**
   * @brief Returns an identifier of the message type generated by the flatbuffers.
   */
  static const char* getTopic() { return PoseFbsIdentifier(); }

private:
  Quaternion quaternion_;
  Point position_;
};
}  // Namespace simple_msgs.

#endif  // SIMPLE_MSGS_POSE_H
