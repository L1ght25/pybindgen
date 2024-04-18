// Copyright 2017 The Abseil Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// This header file contains C++14 versions of standard <utility> header
// abstractions available within C++17, and are designed to be drop-in
// replacement for code compliant with C++14 and C++17.
//
// The following abstractions are defined:
//
//   * apply<Functor, Tuple>         == std::apply<Functor, Tuple>
//   * exchange<T>                   == std::exchange<T>
//   * make_from_tuple<T>            == std::make_from_tuple<T>
//
// This header file also provides the tag types `in_place_t`, `in_place_type_t`,
// and `in_place_index_t`, as well as the constant `in_place`, and
// `constexpr` `std::move()` and `std::forward()` implementations in C++11.
//
// References:
//
//  https://en.cppreference.com/w/cpp/utility/apply
//  http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2013/n3658.html

#ifndef Y_ABSL_UTILITY_UTILITY_H_
#define Y_ABSL_UTILITY_UTILITY_H_

#include <cstddef>
#include <cstdlib>
#include <tuple>
#include <utility>

#include "y_absl/base/config.h"
#include "y_absl/base/internal/inline_variable.h"
#include "y_absl/base/internal/invoke.h"
#include "y_absl/meta/type_traits.h"

namespace y_absl {
Y_ABSL_NAMESPACE_BEGIN

// Historical note: Abseil once provided implementations of these
// abstractions for platforms that had not yet provided them. Those
// platforms are no longer supported. New code should simply use the
// the ones from std directly.
using std::index_sequence;
using std::index_sequence_for;
using std::integer_sequence;
using std::make_index_sequence;
using std::make_integer_sequence;

namespace utility_internal {

template <typename T>
struct InPlaceTypeTag {
  explicit InPlaceTypeTag() = delete;
  InPlaceTypeTag(const InPlaceTypeTag&) = delete;
  InPlaceTypeTag& operator=(const InPlaceTypeTag&) = delete;
};

template <size_t I>
struct InPlaceIndexTag {
  explicit InPlaceIndexTag() = delete;
  InPlaceIndexTag(const InPlaceIndexTag&) = delete;
  InPlaceIndexTag& operator=(const InPlaceIndexTag&) = delete;
};

}  // namespace utility_internal

// Tag types

#ifdef Y_ABSL_USES_STD_OPTIONAL

using std::in_place_t;
using std::in_place;

#else  // Y_ABSL_USES_STD_OPTIONAL

// in_place_t
//
// Tag type used to specify in-place construction, such as with
// `y_absl::optional`, designed to be a drop-in replacement for C++17's
// `std::in_place_t`.
struct in_place_t {};

Y_ABSL_INTERNAL_INLINE_CONSTEXPR(in_place_t, in_place, {});

#endif  // Y_ABSL_USES_STD_OPTIONAL

#if defined(Y_ABSL_USES_STD_ANY) || defined(Y_ABSL_USES_STD_VARIANT)
using std::in_place_type;
using std::in_place_type_t;
#else

// in_place_type_t
//
// Tag type used for in-place construction when the type to construct needs to
// be specified, such as with `y_absl::any`, designed to be a drop-in replacement
// for C++17's `std::in_place_type_t`.
template <typename T>
using in_place_type_t = void (*)(utility_internal::InPlaceTypeTag<T>);

template <typename T>
void in_place_type(utility_internal::InPlaceTypeTag<T>) {}
#endif  // Y_ABSL_USES_STD_ANY || Y_ABSL_USES_STD_VARIANT

#ifdef Y_ABSL_USES_STD_VARIANT
using std::in_place_index;
using std::in_place_index_t;
#else

// in_place_index_t
//
// Tag type used for in-place construction when the type to construct needs to
// be specified, such as with `y_absl::any`, designed to be a drop-in replacement
// for C++17's `std::in_place_index_t`.
template <size_t I>
using in_place_index_t = void (*)(utility_internal::InPlaceIndexTag<I>);

template <size_t I>
void in_place_index(utility_internal::InPlaceIndexTag<I>) {}
#endif  // Y_ABSL_USES_STD_VARIANT

// Constexpr move and forward

// move()
//
// A constexpr version of `std::move()`, designed to be a drop-in replacement
// for C++14's `std::move()`.
template <typename T>
constexpr y_absl::remove_reference_t<T>&& move(T&& t) noexcept {
  return static_cast<y_absl::remove_reference_t<T>&&>(t);
}

// forward()
//
// A constexpr version of `std::forward()`, designed to be a drop-in replacement
// for C++14's `std::forward()`.
template <typename T>
constexpr T&& forward(
    y_absl::remove_reference_t<T>& t) noexcept {  // NOLINT(runtime/references)
  return static_cast<T&&>(t);
}

namespace utility_internal {
// Helper method for expanding tuple into a called method.
template <typename Functor, typename Tuple, std::size_t... Indexes>
auto apply_helper(Functor&& functor, Tuple&& t, index_sequence<Indexes...>)
    -> decltype(y_absl::base_internal::invoke(
        y_absl::forward<Functor>(functor),
        std::get<Indexes>(y_absl::forward<Tuple>(t))...)) {
  return y_absl::base_internal::invoke(
      y_absl::forward<Functor>(functor),
      std::get<Indexes>(y_absl::forward<Tuple>(t))...);
}

}  // namespace utility_internal

// apply
//
// Invokes a Callable using elements of a tuple as its arguments.
// Each element of the tuple corresponds to an argument of the call (in order).
// Both the Callable argument and the tuple argument are perfect-forwarded.
// For member-function Callables, the first tuple element acts as the `this`
// pointer. `y_absl::apply` is designed to be a drop-in replacement for C++17's
// `std::apply`. Unlike C++17's `std::apply`, this is not currently `constexpr`.
//
// Example:
//
//   class Foo {
//    public:
//     void Bar(int);
//   };
//   void user_function1(int, TString);
//   void user_function2(std::unique_ptr<Foo>);
//   auto user_lambda = [](int, int) {};
//
//   int main()
//   {
//       std::tuple<int, TString> tuple1(42, "bar");
//       // Invokes the first user function on int, TString.
//       y_absl::apply(&user_function1, tuple1);
//
//       std::tuple<std::unique_ptr<Foo>> tuple2(y_absl::make_unique<Foo>());
//       // Invokes the user function that takes ownership of the unique
//       // pointer.
//       y_absl::apply(&user_function2, std::move(tuple2));
//
//       auto foo = y_absl::make_unique<Foo>();
//       std::tuple<Foo*, int> tuple3(foo.get(), 42);
//       // Invokes the method Bar on foo with one argument, 42.
//       y_absl::apply(&Foo::Bar, tuple3);
//
//       std::tuple<int, int> tuple4(8, 9);
//       // Invokes a lambda.
//       y_absl::apply(user_lambda, tuple4);
//   }
template <typename Functor, typename Tuple>
auto apply(Functor&& functor, Tuple&& t)
    -> decltype(utility_internal::apply_helper(
        y_absl::forward<Functor>(functor), y_absl::forward<Tuple>(t),
        y_absl::make_index_sequence<std::tuple_size<
            typename std::remove_reference<Tuple>::type>::value>{})) {
  return utility_internal::apply_helper(
      y_absl::forward<Functor>(functor), y_absl::forward<Tuple>(t),
      y_absl::make_index_sequence<std::tuple_size<
          typename std::remove_reference<Tuple>::type>::value>{});
}

// exchange
//
// Replaces the value of `obj` with `new_value` and returns the old value of
// `obj`.  `y_absl::exchange` is designed to be a drop-in replacement for C++14's
// `std::exchange`.
//
// Example:
//
//   Foo& operator=(Foo&& other) {
//     ptr1_ = y_absl::exchange(other.ptr1_, nullptr);
//     int1_ = y_absl::exchange(other.int1_, -1);
//     return *this;
//   }
template <typename T, typename U = T>
T exchange(T& obj, U&& new_value) {
  T old_value = y_absl::move(obj);
  obj = y_absl::forward<U>(new_value);
  return old_value;
}

namespace utility_internal {
template <typename T, typename Tuple, size_t... I>
T make_from_tuple_impl(Tuple&& tup, y_absl::index_sequence<I...>) {
  return T(std::get<I>(std::forward<Tuple>(tup))...);
}
}  // namespace utility_internal

// make_from_tuple
//
// Given the template parameter type `T` and a tuple of arguments
// `std::tuple(arg0, arg1, ..., argN)` constructs an object of type `T` as if by
// calling `T(arg0, arg1, ..., argN)`.
//
// Example:
//
//   std::tuple<const char*, size_t> args("hello world", 5);
//   auto s = y_absl::make_from_tuple<TString>(args);
//   assert(s == "hello");
//
template <typename T, typename Tuple>
constexpr T make_from_tuple(Tuple&& tup) {
  return utility_internal::make_from_tuple_impl<T>(
      std::forward<Tuple>(tup),
      y_absl::make_index_sequence<
          std::tuple_size<y_absl::decay_t<Tuple>>::value>{});
}

Y_ABSL_NAMESPACE_END
}  // namespace y_absl

#endif  // Y_ABSL_UTILITY_UTILITY_H_
