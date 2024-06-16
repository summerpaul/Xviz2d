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
 * @file Point32.cpp
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

#include "Point32.h"
#include <fastcdr/Cdr.h>

#include <fastcdr/exceptions/BadParamException.h>
using namespace eprosima::fastcdr::exception;

#include <utility>

#define geometry_msgs_msg_Point32_max_cdr_typesize 12ULL;
#define geometry_msgs_msg_Point32_max_key_cdr_typesize 0ULL;

geometry_msgs::msg::Point32::Point32()
{
    // float m_x
    m_x = 0.0;
    // float m_y
    m_y = 0.0;
    // float m_z
    m_z = 0.0;
}

geometry_msgs::msg::Point32::~Point32()
{
}

geometry_msgs::msg::Point32::Point32(
        const Point32& x)
{
    m_x = x.m_x;
    m_y = x.m_y;
    m_z = x.m_z;
}

geometry_msgs::msg::Point32::Point32(
        Point32&& x) noexcept
{
    m_x = x.m_x;
    m_y = x.m_y;
    m_z = x.m_z;
}

geometry_msgs::msg::Point32& geometry_msgs::msg::Point32::operator =(
        const Point32& x)
{
    m_x = x.m_x;
    m_y = x.m_y;
    m_z = x.m_z;

    return *this;
}

geometry_msgs::msg::Point32& geometry_msgs::msg::Point32::operator =(
        Point32&& x) noexcept
{
    m_x = x.m_x;
    m_y = x.m_y;
    m_z = x.m_z;

    return *this;
}

bool geometry_msgs::msg::Point32::operator ==(
        const Point32& x) const
{
    return (m_x == x.m_x && m_y == x.m_y && m_z == x.m_z);
}

bool geometry_msgs::msg::Point32::operator !=(
        const Point32& x) const
{
    return !(*this == x);
}

size_t geometry_msgs::msg::Point32::getMaxCdrSerializedSize(
        size_t current_alignment)
{
    static_cast<void>(current_alignment);
    return geometry_msgs_msg_Point32_max_cdr_typesize;
}

size_t geometry_msgs::msg::Point32::getCdrSerializedSize(
        const geometry_msgs::msg::Point32& data,
        size_t current_alignment)
{
    (void)data;
    size_t initial_alignment = current_alignment;
    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4);
    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4);
    current_alignment += 4 + eprosima::fastcdr::Cdr::alignment(current_alignment, 4);

    return current_alignment - initial_alignment;
}

void geometry_msgs::msg::Point32::serialize(
        eprosima::fastcdr::Cdr& scdr) const
{
    scdr << m_x;
    scdr << m_y;
    scdr << m_z;
}

void geometry_msgs::msg::Point32::deserialize(
        eprosima::fastcdr::Cdr& dcdr)
{
    dcdr >> m_x;
    dcdr >> m_y;
    dcdr >> m_z;
}

/*!
 * @brief This function sets a value in member x
 * @param _x New value for member x
 */
void geometry_msgs::msg::Point32::x(
        float _x)
{
    m_x = _x;
}

/*!
 * @brief This function returns the value of member x
 * @return Value of member x
 */
float geometry_msgs::msg::Point32::x() const
{
    return m_x;
}

/*!
 * @brief This function returns a reference to member x
 * @return Reference to member x
 */
float& geometry_msgs::msg::Point32::x()
{
    return m_x;
}

/*!
 * @brief This function sets a value in member y
 * @param _y New value for member y
 */
void geometry_msgs::msg::Point32::y(
        float _y)
{
    m_y = _y;
}

/*!
 * @brief This function returns the value of member y
 * @return Value of member y
 */
float geometry_msgs::msg::Point32::y() const
{
    return m_y;
}

/*!
 * @brief This function returns a reference to member y
 * @return Reference to member y
 */
float& geometry_msgs::msg::Point32::y()
{
    return m_y;
}

/*!
 * @brief This function sets a value in member z
 * @param _z New value for member z
 */
void geometry_msgs::msg::Point32::z(
        float _z)
{
    m_z = _z;
}

/*!
 * @brief This function returns the value of member z
 * @return Value of member z
 */
float geometry_msgs::msg::Point32::z() const
{
    return m_z;
}

/*!
 * @brief This function returns a reference to member z
 * @return Reference to member z
 */
float& geometry_msgs::msg::Point32::z()
{
    return m_z;
}

size_t geometry_msgs::msg::Point32::getKeyMaxCdrSerializedSize(
        size_t current_alignment)
{
    static_cast<void>(current_alignment);
    return geometry_msgs_msg_Point32_max_key_cdr_typesize;
}

bool geometry_msgs::msg::Point32::isKeyDefined()
{
    return false;
}

void geometry_msgs::msg::Point32::serializeKey(
        eprosima::fastcdr::Cdr& scdr) const
{
    (void) scdr;
}
