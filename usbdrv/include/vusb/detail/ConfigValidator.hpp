#pragma once

#include <izi/mpl.hpp>
#include <izi/type_traits.hpp>

namespace vusb {
namespace detail {

class ConfigValidator
{
protected:
  template<int N> struct Please_Update__USB_CFG_HID_REPORT_DESCRIPTOR_LENGTH__to;
  template<int N> struct Please_Update__USB_CFG_VENDOR_NAME_LEN__to;
  template<int N> struct Please_Update__USB_CFG_DEVICE_NAME_LEN__to;

  template <class T, size_t N>
  void validateReportDescriptor(const T (&)[N]) noexcept
  {
    using actual_length_t = izi::integral_type<N>;
    using expected_length_t = izi::integral_type<USB_CFG_HID_REPORT_DESCRIPTOR_LENGTH>;
    using valid_t = izi::is_same<actual_length_t, expected_length_t>;
    using actual_length_value_t = izi::if_<
      valid_t, 
      izi::true_type, 
      Please_Update__USB_CFG_HID_REPORT_DESCRIPTOR_LENGTH__to<actual_length_t::value>
    >;
    using actual_length_check_t = izi::integral_type<sizeof(actual_length_value_t)>;        
  }

  using vendor_name_t = izi::char_array<USB_CFG_VENDOR_NAME>;
  using vendor_name_value_t = izi::if_c<
    (vendor_name_t::size == USB_CFG_VENDOR_NAME_LEN),
    izi::true_type,
    Please_Update__USB_CFG_VENDOR_NAME_LEN__to<vendor_name_t::size>
  >;
  using vendor_name_check_t = izi::integral_type<sizeof(vendor_name_value_t)>;

  using device_name_t = izi::char_array<USB_CFG_DEVICE_NAME>;
  using device_name_value_t = izi::if_c<
    (device_name_t::size == USB_CFG_DEVICE_NAME_LEN),
    izi::true_type,
    Please_Update__USB_CFG_DEVICE_NAME_LEN__to<device_name_t::size>
  >;
  using device_name_check_t = izi::integral_type<sizeof(device_name_value_t)>;
};

} // namespace detail
} // namespace vusb