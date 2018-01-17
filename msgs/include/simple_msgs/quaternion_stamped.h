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

#pragma once

#include <array>
#include <iostream>

#include "generic_message.h"
#include "quaternion.h"
#include "header.h"
#include "generated/quaternion_stamped_generated.h"

namespace simple_msgs
{
/**
 * @brief Quaternion: wrapper class around the QuaternionFbs generated code from flatbuffers.
 */
class QuaternionStamped : public GenericMessage
{
public:
  QuaternionStamped();
  QuaternionStamped(const Header&, const Quaternion&);
  QuaternionStamped(const uint8_t*);
  QuaternionStamped(const QuaternionStamped&);
  QuaternionStamped(QuaternionStamped&&);

  QuaternionStamped& operator=(const QuaternionStamped&);
  QuaternionStamped& operator=(QuaternionStamped&&);
  QuaternionStamped& operator=(const uint8_t*);

  inline bool operator==(const QuaternionStamped& rhs) const
  {
    return (quaternion_ == rhs.quaternion_ && header_ == rhs.header_);
  }
  inline bool operator!=(const QuaternionStamped& rhs) const { return !(*this == rhs); }
  friend std::ostream& operator<<(std::ostream&, const QuaternionStamped&);

  /**
   * @brief Builds and returns the buffer accordingly to the values currently stored.
   */
  uint8_t* getBufferData() const override;

  /**
   * @brief Returns the message Quaternion.
   * @return
   */
  inline Quaternion& getQuaternion() { return quaternion_; }
  inline const Quaternion& getQuaternion() const { return quaternion_; }
  /**
   * @brief Returns the message Hader.
   */
  inline Header& getHeader() { return header_; }
  inline const Header& getHeader() const { return header_; }
  /**
   * @brief Modifies the message Quaternion.
   */
  void setQuaternion(const Quaternion&);
  /**
   * @brief Modifies the message Header.
   */
  void setHeader(const Header&);
  /**
   * @brief Returns an identifier of the message type generated by the flatbuffers.
   */
  static const char* getTopic() { return QuaternionStampedFbsIdentifier(); }
private:
  Quaternion quaternion_;
  Header header_;
};
}  // Namespace simple_msgs.
