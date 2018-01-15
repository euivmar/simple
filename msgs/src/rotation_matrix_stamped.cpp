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

#include "simple_msgs/rotation_matrix_stamped.h"

namespace simple_msgs
{
RotationMatrixStamped::RotationMatrixStamped()
  : GenericMessage()
{
}

RotationMatrixStamped::RotationMatrixStamped(const Header& header, const RotationMatrix& rotation_matrix)
  : GenericMessage()
  , rotation_matrix_(rotation_matrix)
  , header_(header)
{
}

RotationMatrixStamped::RotationMatrixStamped(const uint8_t* data)
  : GenericMessage()
  , rotation_matrix_(GetRotationMatrixStampedFbs(data)->rotation_matrix()->data())
  , header_(GetRotationMatrixStampedFbs(data)->header()->data())
{
}

RotationMatrixStamped::RotationMatrixStamped(const RotationMatrixStamped& m)
  : RotationMatrixStamped(m.header_, m.rotation_matrix_)
{
}

RotationMatrixStamped::RotationMatrixStamped(RotationMatrixStamped&& m)
  : RotationMatrixStamped(std::move(m.header_), std::move(m.rotation_matrix_))
{
}

RotationMatrixStamped& RotationMatrixStamped::operator=(const RotationMatrixStamped& other)
{
  if (this != std::addressof(other))
  {
    std::lock_guard<std::mutex> lock(mutex_);
    rotation_matrix_ = other.rotation_matrix_;
    header_ = other.header_;
    modified_ = true;
  }
  return *this;
}

RotationMatrixStamped& RotationMatrixStamped::operator=(RotationMatrixStamped&& other)
{
  if (this != std::addressof(other))
  {
    std::lock_guard<std::mutex> lock(mutex_);
    rotation_matrix_ = std::move(other.rotation_matrix_);
    header_ = std::move(other.header_);
    modified_ = true;
  }
  return *this;
}

RotationMatrixStamped& RotationMatrixStamped::operator=(const uint8_t* data)
{
  std::lock_guard<std::mutex> lock(mutex_);
  auto matrix = GetRotationMatrixStampedFbs(data);
  rotation_matrix_ = RotationMatrix(matrix->rotation_matrix()->data());
  header_ = Header(matrix->header()->data());
  modified_ = true;

  return *this;
}

uint8_t* RotationMatrixStamped::getBufferData() const
{
  std::lock_guard<std::mutex> lock(mutex_);
  if (modified_ || header_.isModified() || rotation_matrix_.isModified())
  {
    builder_->Clear();
    auto rotation_matrix_vector =
        builder_->CreateVector(rotation_matrix_.getBufferData(), rotation_matrix_.getBufferSize());
    auto header_vector = builder_->CreateVector(header_.getBufferData(), header_.getBufferSize());
    RotationMatrixStampedFbsBuilder tmp_builder(*builder_);
    tmp_builder.add_rotation_matrix(rotation_matrix_vector);
    tmp_builder.add_header(header_vector);
    FinishRotationMatrixStampedFbsBuffer(*builder_, tmp_builder.Finish());
    modified_ = false;
  }
  return builder_->GetBufferPointer();
}

inline void RotationMatrixStamped::setRotationMatrix(const RotationMatrix& rotation_matrix)
{
  std::lock_guard<std::mutex> lock(mutex_);
  rotation_matrix_ = rotation_matrix;
  modified_ = true;
}

inline void RotationMatrixStamped::setHeader(const Header& header)
{
  std::lock_guard<std::mutex> lock(mutex_);
  header_ = header;
  modified_ = true;
}

std::ostream& operator<<(std::ostream& out, const RotationMatrixStamped& q)
{
  out << q.header_ << q.rotation_matrix_;

  return out;
}
}  // namespace simple_msgs