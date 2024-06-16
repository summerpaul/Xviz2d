// Copyright 2016 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/*!
 * @file PoseWithCovariance.cpp
 * This source file contains the definition of the described types in the IDL file.
 *
 * This file was generated by the tool gen.
 */

#ifdef _WIN32
// Remove linker warning LNK4221 on Visual Studio
namespace {
char dummy;
}  // namespace
#endif  // _WIN32

#include "PoseWithCovariance.h"
#include <fastcdr/Cdr.h>

#include <fastcdr/exceptions/BadParamException.h>
using namespace eprosima::fastcdr::exception;

#include <utility>

#define geometry_msgs_msg_Pose_max_cdr_typesize 56ULL;
#define geometry_msgs_msg_Point_max_cdr_typesize 24ULL;
#define geometry_msgs_msg_PoseWithCovariance_max_cdr_typesize 344ULL;
#define geometry_msgs_msg_Quaternion_max_cdr_typesize 32ULL;
#define geometry_msgs_msg_Pose_max_key_cdr_typesize 0ULL;
#define geometry_msgs_msg_Point_max_key_cdr_typesize 0ULL;
#define geometry_msgs_msg_PoseWithCovariance_max_key_cdr_typesize 0ULL;
#define geometry_msgs_msg_Quaternion_max_key_cdr_typesize 0ULL;

geometry_msgs::msg::PoseWithCovariance::PoseWithCovariance()
{
    // geometry_msgs::msg::Pose m_pose

    // geometry_msgs::msg::geometry_msgs__PoseWithCovariance__double_array_36 m_covariance
    memset(&m_covariance, 0, (36) * 8);
}

geometry_msgs::msg::PoseWithCovariance::~PoseWithCovariance()
{
}

geometry_msgs::msg::PoseWithCovariance::PoseWithCovariance(
        const PoseWithCovariance& x)
{
    m_pose = x.m_pose;
    m_covariance = x.m_covariance;
}

geometry_msgs::msg::PoseWithCovariance::PoseWithCovariance(
        PoseWithCovariance&& x) noexcept
{
    m_pose = std::move(x.m_pose);
    m_covariance = std::move(x.m_covariance);
}

geometry_msgs::msg::PoseWithCovariance& geometry_msgs::msg::PoseWithCovariance::operator =(
        const PoseWithCovariance& x)
{
    m_pose = x.m_pose;
    m_covariance = x.m_covariance;

    return *this;
}

geometry_msgs::msg::PoseWithCovariance& geometry_msgs::msg::PoseWithCovariance::operator =(
        PoseWithCovariance&& x) noexcept
{
    m_pose = std::move(x.m_pose);
    m_covariance = std::move(x.m_covariance);

    return *this;
}

bool geometry_msgs::msg::PoseWithCovariance::operator ==(
        const PoseWithCovariance& x) const
{
    return (m_pose == x.m_pose && m_covariance == x.m_covariance);
}

bool geometry_msgs::msg::PoseWithCovariance::operator !=(
        const PoseWithCovariance& x) const
{
    return !(*this == x);
}

size_t geometry_msgs::msg::PoseWithCovariance::getMaxCdrSerializedSize(
        size_t current_alignment)
{
    static_cast<void>(current_alignment);
    return geometry_msgs_msg_PoseWithCovariance_max_cdr_typesize;
}

size_t geometry_msgs::msg::PoseWithCovariance::getCdrSerializedSize(
        const geometry_msgs::msg::PoseWithCovariance& data,
        size_t current_alignment)
{
    size_t initial_alignment = current_alignment;
    current_alignment += geometry_msgs::msg::Pose::getCdrSerializedSize(data.pose(), current_alignment);
    current_alignment += ((36) * 8) + eprosima::fastcdr::Cdr::alignment(current_alignment, 8);

    return current_alignment - initial_alignment;
}

void geometry_msgs::msg::PoseWithCovariance::serialize(
        eprosima::fastcdr::Cdr& scdr) const
{
    scdr << m_pose;
    scdr << m_covariance;
}

void geometry_msgs::msg::PoseWithCovariance::deserialize(
        eprosima::fastcdr::Cdr& dcdr)
{
    dcdr >> m_pose;
    dcdr >> m_covariance;
}

/*!
 * @brief This function copies the value in member pose
 * @param _pose New value to be copied in member pose
 */
void geometry_msgs::msg::PoseWithCovariance::pose(
        const geometry_msgs::msg::Pose& _pose)
{
    m_pose = _pose;
}

/*!
 * @brief This function moves the value in member pose
 * @param _pose New value to be moved in member pose
 */
void geometry_msgs::msg::PoseWithCovariance::pose(
        geometry_msgs::msg::Pose&& _pose)
{
    m_pose = std::move(_pose);
}

/*!
 * @brief This function returns a constant reference to member pose
 * @return Constant reference to member pose
 */
const geometry_msgs::msg::Pose& geometry_msgs::msg::PoseWithCovariance::pose() const
{
    return m_pose;
}

/*!
 * @brief This function returns a reference to member pose
 * @return Reference to member pose
 */
geometry_msgs::msg::Pose& geometry_msgs::msg::PoseWithCovariance::pose()
{
    return m_pose;
}
/*!
 * @brief This function copies the value in member covariance
 * @param _covariance New value to be copied in member covariance
 */
void geometry_msgs::msg::PoseWithCovariance::covariance(
        const geometry_msgs::msg::geometry_msgs__PoseWithCovariance__double_array_36& _covariance)
{
    m_covariance = _covariance;
}

/*!
 * @brief This function moves the value in member covariance
 * @param _covariance New value to be moved in member covariance
 */
void geometry_msgs::msg::PoseWithCovariance::covariance(
        geometry_msgs::msg::geometry_msgs__PoseWithCovariance__double_array_36&& _covariance)
{
    m_covariance = std::move(_covariance);
}

/*!
 * @brief This function returns a constant reference to member covariance
 * @return Constant reference to member covariance
 */
const geometry_msgs::msg::geometry_msgs__PoseWithCovariance__double_array_36& geometry_msgs::msg::PoseWithCovariance::covariance() const
{
    return m_covariance;
}

/*!
 * @brief This function returns a reference to member covariance
 * @return Reference to member covariance
 */
geometry_msgs::msg::geometry_msgs__PoseWithCovariance__double_array_36& geometry_msgs::msg::PoseWithCovariance::covariance()
{
    return m_covariance;
}


size_t geometry_msgs::msg::PoseWithCovariance::getKeyMaxCdrSerializedSize(
        size_t current_alignment)
{
    static_cast<void>(current_alignment);
    return geometry_msgs_msg_PoseWithCovariance_max_key_cdr_typesize;
}

bool geometry_msgs::msg::PoseWithCovariance::isKeyDefined()
{
    return false;
}

void geometry_msgs::msg::PoseWithCovariance::serializeKey(
        eprosima::fastcdr::Cdr& scdr) const
{
    (void) scdr;
}
