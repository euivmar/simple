/**
 * S.I.M.P.L.E. - Smart Intuitive Messaging Platform with Less Effort
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

#ifndef SIMPLE_MSGS_BOOL_H
#define SIMPLE_MSGS_BOOL_H

#include "generated/bool_generated.h"
#include "generic_message.h"

namespace simple_msgs {
class Bool : public GenericMessage {
public:
  Bool() = default;
  Bool(bool);
  Bool(const uint8_t*);
  Bool(const Bool&);
  Bool(Bool&&) noexcept;

  Bool& operator=(const Bool&);
  Bool& operator=(Bool&&) noexcept;
  Bool& operator=(const uint8_t* data);

  inline bool operator==(const Bool& rhs) const { return (data_ == rhs.data_); }
  inline bool operator!=(const Bool& rhs) const { return !(*this == rhs); }
  inline Bool& operator!() {
    data_ = !data_;
    return *this;
  }

  friend std::ostream& operator<<(std::ostream& out, const Bool& b);

  /**
   * @brief Builds and returns the buffer accordingly to the values currently stored.
   * @return the buffer data.
   */
  std::shared_ptr<flatbuffers::DetachedBuffer> getBufferData() const override;

  /**
   * @brief Set the boolean value.
   */
  void set(bool data);

  /**
   * @brief Get the boolean value.
   */
  bool get() const { return data_; }
  /**
   * @brief Returns an identifier of the message type generated by the flatbuffers.
   */
  static inline const char* getTopic() { return BoolFbsIdentifier(); }

private:
  bool data_{false};
};
}  // Namespace simple_msgs.

#endif  // SIMPLE_MSGS_BOOL_H
