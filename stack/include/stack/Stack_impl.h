#ifndef STACK_STACK_IMPL_H
#define STACK_STACK_IMPL_H

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <utility>

#include "stack/Stack.h"

template <typename ElemTy>
Stack<ElemTy>::Stack(float grow_coeff) : capacity_(kDefaultCapacity), grow_coeff_(grow_coeff) {
  data_ = new ElemTy[capacity_];
}

template <typename ElemTy>
Stack<ElemTy>::Stack(const ElemTy* other_datum, size_t other_size, float grow_coeff) // NOLINT(bugprone-easily-swappable-parameters)
    : size_(other_size), capacity_(other_size), grow_coeff_(grow_coeff) {
  data_ = new ElemTy[capacity_];
  std::copy(other_datum, other_datum + size_, data_);
}

template <typename ElemTy>
Stack<ElemTy>::Stack(const Stack& other) : Stack(other.data_, other.size_, other.grow_coeff_) {}

template <typename ElemTy>
Stack<ElemTy>::Stack(Stack&& other) noexcept
    : data_(other.data_),
      size_(other.size_),
      capacity_(other.capacity_),
      grow_coeff_(other.grow_coeff_) {
  other.data_ = nullptr;
  other.capacity_ = other.size_ = 0;
}

template <typename ElemTy>
Stack<ElemTy>::~Stack() {
  delete[] data_;
}

template <typename ElemTy>
Stack<ElemTy>& Stack<ElemTy>::operator=(const Stack& rhs) {
  if (this == &rhs) {
    return *this;
  }

  size_ = rhs.size_;
  grow_coeff_ = rhs.grow_coeff_;
  size_t old_cap = capacity_;
  capacity_ = rhs.capacity_;
  if (old_cap < capacity_) {
    delete[] data_;

    data_ = new ElemTy[capacity_];
  }
  std::copy(rhs.data_, rhs.data_ + size_, data_);
  return *this;
}

template <typename ElemTy>
Stack<ElemTy>& Stack<ElemTy>::operator=(Stack&& other) noexcept {
  if (this == &other) {
    return *this;
  }

  delete[] data_;

  data_ = other.data_;
  size_ = other.size_;
  capacity_ = other.capacity_;
  grow_coeff_ = other.grow_coeff_;

  other.data_ = nullptr;
  other.capacity_ = other.size_ = 0;

  return *this;
}

template <typename ElemTy>
bool Stack<ElemTy>::operator==(const Stack& rhs) const {
  if (size_ != rhs.size_) {
    return false;
  }

  for (size_t i = 0; i < size_; ++i) {
    if (data_[i] != rhs.data_[i]) {
      return false;
    }
  }
  return true;
}

template <typename ElemTy>
bool Stack<ElemTy>::operator!=(const Stack& rhs) const {
  return !(*this == rhs);
}

template <typename ElemTy>
bool Stack<ElemTy>::operator<(const Stack& rhs) const {
  for (size_t i = 0, j = 0; i < size_ && j < rhs.size_; ++i, ++j) {
    if (data_[i] >= rhs.data_[j]) {
      return false;
    }
  }

  return size_ <= rhs.size_;
}

template <typename ElemTy>
bool Stack<ElemTy>::operator>(const Stack& rhs) const {
  return rhs < *this;
}

template <typename ElemTy>
bool Stack<ElemTy>::operator<=(const Stack& rhs) const {
  return !(rhs < *this);
}

template <typename ElemTy>
bool Stack<ElemTy>::operator>=(const Stack& rhs) const {
  return !(*this < rhs);
}

template <typename ElemTy>
ElemTy& Stack<ElemTy>::top() {
  assert(!empty());
  return data_[size_ - 1];
}

template <typename ElemTy>
const ElemTy& Stack<ElemTy>::top() const {
  assert(!empty());
  return data_[size_ - 1];
}

template <typename ElemTy>
bool Stack<ElemTy>::empty() const {
  return size_ == 0;
}

template <typename ElemTy>
size_t Stack<ElemTy>::size() const {
  return size_;
}

template <typename ElemTy>
void Stack<ElemTy>::push(ElemTy val) {
  if (size_ < capacity_) {
    data_[size_++] = val;
    return;
  }

  grow();
  data_[size_++] = val;
}

template <typename ElemTy>
void Stack<ElemTy>::pop() {
  assert(!empty());
  --size_;
}

template <typename ElemTy>
void Stack<ElemTy>::swap(Stack& other) {
  std::swap(data_, other.data_);
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
}

template <typename ElemTy>
void Stack<ElemTy>::grow() {
  capacity_ = capacity_ * grow_coeff_ + 1;
  auto* new_datum = new ElemTy[capacity_];
  std::move(data_, data_ + size_, new_datum);
  delete[] data_;
  data_ = new_datum;
}

inline Stack<bool>::Stack(float grow_coeff)
    : chunks_cnt_(kDefaultChunksCnt), grow_coeff_(grow_coeff) {
  chunks_ = new size_t[kDefaultChunksCnt];
}

inline Stack<bool>::Stack(const Stack& other)
    : size_(other.size_), chunks_cnt_(other.chunks_cnt_), grow_coeff_(other.grow_coeff_) {
  chunks_ = new size_t[chunks_cnt_];
  std::copy(other.chunks_, other.chunks_ + chunks_not_empty(), chunks_);
}

inline Stack<bool>::Stack(Stack&& other) noexcept
    : chunks_(other.chunks_),
      size_(other.size_),
      chunks_cnt_(other.chunks_cnt_),
      grow_coeff_(other.grow_coeff_) {
  other.chunks_ = nullptr;
  other.chunks_cnt_ = other.size_ = 0;
}

inline Stack<bool>::~Stack() {
  delete[] chunks_;
}

inline Stack<bool>& Stack<bool>::operator=(const Stack& rhs) {
  if (this == &rhs) {
    return *this;
  }

  size_ = rhs.size_;
  size_t old_storage_units_cnt = chunks_cnt_;
  chunks_cnt_ = rhs.chunks_cnt_;
  if (old_storage_units_cnt < chunks_cnt_) {
    delete[] chunks_;

    chunks_ = new size_t[chunks_cnt_];
  }
  std::copy(rhs.chunks_, rhs.chunks_ + chunks_not_empty(), chunks_);
  return *this;
}

inline Stack<bool>& Stack<bool>::operator=(Stack&& other) noexcept {
  if (this == &other) {
    return *this;
  }

  delete[] chunks_;

  chunks_ = other.chunks_;
  size_ = other.size_;
  chunks_cnt_ = other.chunks_cnt_;

  other.chunks_ = nullptr;
  other.chunks_cnt_ = other.size_ = 0;

  return *this;
}

inline bool Stack<bool>::operator==(const Stack& rhs) const {
  if (size_ != rhs.size_) {
    return false;
  }

  for (size_t i = 0; i < chunks_filled(); ++i) {
    if (chunks_[i] != rhs.chunks_[i]) {
      return false;
    }
  }

  if (bits_in_last_chunk() != rhs.bits_in_last_chunk()) {
    return false;
  }

  for (size_t i = 0; i < bits_in_last_chunk(); ++i) {
    if ((chunks_[chunks_filled()] & (1 << i)) != (rhs.chunks_[chunks_filled()] & (1 << i))) {
      return false;
    }
  }

  return true;
}

inline bool Stack<bool>::operator!=(const Stack& rhs) const {
  return !(*this == rhs);
}

inline bool Stack<bool>::operator<(const Stack& rhs) const {
  size_t min_chunks_filled = std::min(chunks_filled(), rhs.chunks_filled());
  for (size_t i = 0; i < min_chunks_filled; ++i) {
    if (chunks_[i] >= rhs.chunks_[i]) {
      return false;
    }
  }

  size_t min_bits_in_last_chunk;
  if (chunks_filled() != rhs.chunks_filled()) {
    min_bits_in_last_chunk =
        min_chunks_filled == chunks_filled() ? bits_in_last_chunk() : rhs.bits_in_last_chunk();
  } else {
    min_bits_in_last_chunk = std::min(bits_in_last_chunk(), rhs.bits_in_last_chunk());
  }

  size_t bit_mask = 0;
  for (size_t i = 0; i < min_bits_in_last_chunk; ++i) {
    bit_mask |= (1 << i);
  }

  if ((chunks_[min_chunks_filled] & bit_mask) >= (rhs.chunks_[min_chunks_filled] & bit_mask)) {
    return false;
  }

  if (chunks_filled() != rhs.chunks_filled()) {
    return chunks_filled() < rhs.chunks_filled();
  }

  return bits_in_last_chunk() <= rhs.bits_in_last_chunk();
}

inline bool Stack<bool>::operator>(const Stack& rhs) const {
  return rhs < *this;
}

inline bool Stack<bool>::operator<=(const Stack& rhs) const {
  return !(rhs < *this);
}

inline bool Stack<bool>::operator>=(const Stack& rhs) const {
  return !(*this < rhs);
}

inline bool Stack<bool>::get_top() const {
  assert(!empty());
  return (chunks_[chunks_filled()] & top_bit_mask()) != 0;
}

inline void Stack<bool>::set_top(bool val) {
  assert(!empty());
  if (val) {
    chunks_[chunks_filled()] |= top_bit_mask();
  } else {
    chunks_[chunks_filled()] &= ~top_bit_mask();
  }
}

inline bool Stack<bool>::empty() const {
  return size_ == 0;
}

inline size_t Stack<bool>::size() const {
  return size_;
}

inline void Stack<bool>::push(bool val) {
  if (chunks_filled() < chunks_cnt_) {
    ++size_;
    set_top(val);
    return;
  }

  grow();
  ++size_;
  set_top(val);
}

inline void Stack<bool>::pop() {
  assert(!empty());
  --size_;
}

inline void Stack<bool>::swap(Stack& other) {
  std::swap(chunks_, other.chunks_);
  std::swap(size_, other.size_);
  std::swap(chunks_cnt_, other.chunks_cnt_);
}

inline size_t Stack<bool>::chunks_filled() const {
  return size_ / kBitsInChunk;
}

inline size_t Stack<bool>::bits_in_last_chunk() const {
  return size_ % kBitsInChunk;
}

inline size_t Stack<bool>::top_bit_mask() const {
  return bits_in_last_chunk() == 0 ? 1 : 1 << (bits_in_last_chunk() - 1);
}

inline size_t Stack<bool>::chunks_not_empty() const {
  return (size_ + kBitsInChunk - 1) / kBitsInChunk;
}

inline void Stack<bool>::grow() {
  chunks_cnt_ = chunks_cnt_ * grow_coeff_ + 1;
  auto* new_datum = new size_t[chunks_cnt_];
  std::move(chunks_, chunks_ + chunks_not_empty(), new_datum);
  delete[] chunks_;
  chunks_ = new_datum;
}

#endif /* STACK_STACK_IMPL_H */
