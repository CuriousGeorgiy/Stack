#ifndef STACK_STACK_H
#define STACK_STACK_H

#include <climits>
#include <cstddef>

template <typename ElemTy>
class Stack {
 public:
  explicit Stack(float grow_coeff = 1.5);
  Stack(const ElemTy* other_datum, size_t other_size, float grow_coeff = 1.5);
  Stack(const Stack& other);
  Stack(Stack&& other) noexcept;

  ~Stack();

  Stack& operator=(const Stack& rhs);
  Stack& operator=(Stack&& other) noexcept;

  bool operator==(const Stack& rhs) const;
  bool operator!=(const Stack& rhs) const;

  bool operator<(const Stack& rhs) const;
  bool operator>(const Stack& rhs) const;
  bool operator<=(const Stack& rhs) const;
  bool operator>=(const Stack& rhs) const;

  void swap(Stack& other);

  ElemTy& top();
  [[nodiscard]] const ElemTy& top() const;

  [[nodiscard]] bool empty() const;
  [[nodiscard]] size_t size() const;

  void push(ElemTy val);
  void pop();

 private:
  static const size_t kDefaultCapacity = 32;

  ElemTy* data_;
  size_t size_{0};
  size_t capacity_;
  float grow_coeff_;

  void grow();
};

template <>
class Stack<bool> {
 public:
  explicit Stack(float grow_coeff = 1.5);
  Stack(const Stack& other);
  Stack(Stack&& other) noexcept;

  ~Stack();

  Stack& operator=(const Stack& rhs);
  Stack& operator=(Stack&& other) noexcept;

  bool operator==(const Stack& rhs) const;
  bool operator!=(const Stack& rhs) const;

  bool operator<(const Stack& rhs) const;
  bool operator>(const Stack& rhs) const;
  bool operator<=(const Stack& rhs) const;
  bool operator>=(const Stack& rhs) const;

  void swap(Stack& other);

  [[nodiscard]] bool get_top() const;
  void set_top(bool val);

  [[nodiscard]] bool empty() const;
  [[nodiscard]] size_t size() const;

  void push(bool val);
  void pop();

 private:
  static const size_t kDefaultChunksCnt = 32;
  static const size_t kBitsInChunk = CHAR_BIT * sizeof(size_t);

  size_t* chunks_;
  size_t size_{0};
  size_t chunks_cnt_;
  float grow_coeff_;

  [[nodiscard]] size_t chunks_filled() const;
  [[nodiscard]] size_t bits_in_last_chunk() const;
  [[nodiscard]] size_t top_bit_mask() const;

  [[nodiscard]] size_t chunks_not_empty() const;

  void grow();
};

#endif /* STACK_STACK_H */
