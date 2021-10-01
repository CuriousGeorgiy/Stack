#include <gtest/gtest.h>

#include "stack/Stack.h"
#include "stack/Stack_impl.h"

TEST(StackTest, DefaultConstructor) {
  Stack<size_t> stack(2);

  EXPECT_EQ(stack.size(), 0);
  EXPECT_TRUE(stack.empty());
}

TEST(StackTest, ConstructorFromContainer) {
  const size_t datum_size = 3;
  size_t datum[datum_size]{1, 2, 3};

  Stack<size_t> stack{datum, datum_size};

  EXPECT_EQ(stack.size(), datum_size);
  ASSERT_TRUE(!stack.empty());
  EXPECT_EQ(stack.top(), datum[datum_size - 1]);
}

TEST(StackTest, Pop) {
  const size_t datum_size = 3;
  size_t datum[datum_size]{1, 2, 3};
  Stack<size_t> stack{datum, datum_size};

  for (ptrdiff_t i = datum_size - 1; i >= 0; --i) {
    EXPECT_EQ(stack.top(), datum[i]);
    stack.pop();
  }
}

TEST(StackTest, EQOperator) {
  const size_t datum_size = 3;
  size_t datum[datum_size]{1, 2, 3};

  Stack<size_t> x{datum, datum_size};
  Stack<size_t> y{datum, datum_size};

  EXPECT_EQ(x, y);
}

TEST(StackTest, CopyConstructor) {
  const size_t datum_size = 3;
  size_t datum[datum_size]{1, 2, 3};

  Stack<size_t> other_stack{datum, datum_size};

  Stack<size_t> stack{other_stack}; // NOLINT(performance-unnecessary-copy-initialization)

  EXPECT_EQ(stack.size(), other_stack.size());
  ASSERT_TRUE(!stack.empty());
  EXPECT_EQ(stack, other_stack);
}

TEST(StackTest, MoveConstructor) {
  const size_t datum_size = 3;
  size_t datum[datum_size]{1, 2, 3};

  Stack<size_t> other_stack{datum, datum_size};
  Stack<size_t> other_stack_cp{other_stack};

  Stack<size_t> stack{std::move(other_stack)};

  EXPECT_EQ(stack.size(), datum_size);
  ASSERT_TRUE(!stack.empty());
  EXPECT_EQ(stack, other_stack_cp);
}

TEST(StackTest, CopyAssignmentOperator) {
  const size_t datum_size = 3;
  size_t datum[datum_size]{1, 2, 3};

  Stack<size_t> other_stack{datum, datum_size};

  Stack<size_t> stack(2);
  stack = other_stack;

  EXPECT_EQ(stack.size(), other_stack.size());
  ASSERT_TRUE(!stack.empty());
  EXPECT_EQ(stack, other_stack);
}

TEST(StackTest, MoveAssignmentOperator) {
  const size_t datum_size = 3;
  size_t datum[datum_size]{1, 2, 3};

  Stack<size_t> other_stack{datum, datum_size};
  Stack<size_t> other_stack_cp{other_stack};

  Stack<size_t> stack(2);
  stack = std::move(other_stack);

  EXPECT_EQ(stack.size(), datum_size);
  ASSERT_TRUE(!stack.empty());
  EXPECT_EQ(stack, other_stack_cp);
}

TEST(StackTest, Swap) {
  const size_t datum_x_size = 3;
  size_t datum_x[datum_x_size]{1, 2, 3};
  const size_t datum_y_size = 3;
  size_t datum_y[datum_x_size]{4, 5, 6};

  Stack<size_t> a{datum_x, datum_x_size};
  Stack<size_t> b{a};
  Stack<size_t> c{datum_y, datum_y_size};
  Stack<size_t> d{c};

  EXPECT_NE(a, d);
  EXPECT_NE(c, b);

  a.swap(c);

  EXPECT_EQ(a, d);
  EXPECT_EQ(c, b);
}

TEST(StackTest, NEQOperator) {
  const size_t datum_x_size = 3;
  size_t datum_x[datum_x_size]{1, 2, 3};
  const size_t datum_y_size = 3;
  size_t datum_y[datum_x_size]{4, 5, 6};

  Stack<size_t> x{datum_x, datum_x_size};
  Stack<size_t> y{datum_y, datum_y_size};

  EXPECT_NE(x, y);
}

TEST(StackTest, LTOperator) {
  const size_t datum_x_size = 3;
  size_t datum_x[datum_x_size]{1, 2, 3};
  const size_t datum_y_size = 3;
  size_t datum_y[datum_x_size]{4, 5, 6};

  Stack<size_t> x{datum_x, datum_x_size};
  Stack<size_t> y{datum_y, datum_y_size};

  EXPECT_LT(x, y);
}

TEST(StackTest, GTOperator) {
  const size_t datum_x_size = 3;
  size_t datum_x[datum_x_size]{1, 2, 3};
  const size_t datum_y_size = 3;
  size_t datum_y[datum_x_size]{4, 5, 6};

  Stack<size_t> x{datum_x, datum_x_size};
  Stack<size_t> y{datum_y, datum_y_size};

  EXPECT_GT(y, x);
}

TEST(StackTest, LEOperatorLT) {
  const size_t datum_x_size = 3;
  size_t datum_x[datum_x_size]{1, 2, 3};
  const size_t datum_y_size = 3;
  size_t datum_y[datum_x_size]{4, 5, 6};

  Stack<size_t> x{datum_x, datum_x_size};
  Stack<size_t> y{datum_y, datum_y_size};

  EXPECT_LE(x, y);
}

TEST(StackTest, LEOperatorEQ) {
  const size_t datum_size = 3;
  size_t datum[datum_size]{1, 2, 3};

  Stack<size_t> x{datum, datum_size};
  Stack<size_t> y{datum, datum_size};

  EXPECT_LE(x, y);
}

TEST(StackTest, GEOperatorGT) {
  const size_t datum_x_size = 3;
  size_t datum_x[datum_x_size]{1, 2, 3};
  const size_t datum_y_size = 3;
  size_t datum_y[datum_x_size]{4, 5, 6};

  Stack<size_t> x{datum_x, datum_x_size};
  Stack<size_t> y{datum_y, datum_y_size};

  EXPECT_GE(y, x);
}

TEST(StackTest, GEOperatorEQ) {
  const size_t datum_size = 3;
  size_t datum[datum_size]{1, 2, 3};

  Stack<size_t> x{datum, datum_size};
  Stack<size_t> y{datum, datum_size};

  EXPECT_GE(y, x);
}

TEST(StackTest, Top) {
  const size_t datum_size = 3;
  size_t datum[datum_size]{1, 2, 3};

  Stack<size_t> stack{datum, datum_size};

  EXPECT_EQ(stack.top(), 3);
  stack.top() = 4;
  EXPECT_EQ(stack.top(), 4);
}

TEST(StackTest, Empty) {
  Stack<size_t> stack(2);
  EXPECT_TRUE(stack.empty());

  Stack<size_t> other_stack(2);
  stack = other_stack;
  EXPECT_TRUE(stack.empty());

  stack = Stack<size_t>{};
  EXPECT_TRUE(stack.empty());
}

TEST(StackTest, Size) {
  {
    const size_t datum_size = 1;
    size_t datum[datum_size]{};

    Stack<size_t> stack{datum, datum_size};
    EXPECT_EQ(stack.size(), datum_size);
  }

  {
    const size_t datum_size = 2;
    size_t datum[datum_size]{};

    Stack<size_t> stack{datum, datum_size};
    EXPECT_EQ(stack.size(), datum_size);
  }

  {
    const size_t datum_size = 3;
    size_t datum[datum_size]{};

    Stack<size_t> stack{datum, datum_size};
    EXPECT_EQ(stack.size(), datum_size);
  }
}

TEST(StackTest, Push) {
  Stack<size_t> stack(2);

  for (size_t val = 0; val < 3; ++val) {
    stack.push(val);
    EXPECT_EQ(stack.top(), val);
  }
}

TEST(BoolSpecializationStackTest, DefaultConstructor) {
  Stack<bool> stack(2);

  EXPECT_EQ(stack.size(), 0);
  EXPECT_TRUE(stack.empty());
}

TEST(BoolSpecializationStackTest, Push) {
  Stack<bool> stack(2);

  for (size_t val = 1; val <= 3; ++val) {
    stack.push(val % 2 == 0);
    EXPECT_EQ(stack.get_top(), val % 2 == 0);
  }
}

TEST(BoolSpecializationStackTest, EQOperator) {
  const size_t stack_size = 3;
  Stack<bool> x(2);
  Stack<bool> y(2);
  for (size_t val = 1; val <= stack_size; ++val) {
    x.push(val % 2 == 0);
    y.push(val % 2 == 0);
  }

  EXPECT_EQ(x, y);
}

TEST(BoolSpecializationStackTest, CopyConstructor) {
  const size_t stack_size = 3;
  Stack<bool> other_stack(2);
  for (size_t val = 1; val <= stack_size; ++val) {
    other_stack.push(val % 2 == 0);
  }

  Stack<bool> stack{other_stack};

  EXPECT_EQ(stack.size(), other_stack.size());
  ASSERT_TRUE(!stack.empty());
  EXPECT_EQ(stack, other_stack);
}

TEST(BoolSpecializationStackTest, MoveConstructor) {
  const size_t stack_size = 3;
  Stack<bool> other_stack(2);
  for (size_t val = 1; val <= stack_size; ++val) {
    other_stack.push(val % 2 == 0);
  }
  Stack<bool> other_stack_cp{other_stack};

  Stack<bool> stack{std::move(other_stack)};

  EXPECT_EQ(stack.size(), stack_size);
  ASSERT_TRUE(!stack.empty());
  EXPECT_EQ(stack, other_stack_cp);
}

TEST(BoolSpecializationStackTest, CopyAssignmentOperator) {
  const size_t stack_size = 3;
  Stack<bool> other_stack(2);
  for (size_t val = 1; val <= stack_size; ++val) {
    other_stack.push(val % 2 == 0);
  }

  Stack<bool> stack(2);
  stack = other_stack;

  EXPECT_EQ(stack.size(), other_stack.size());
  ASSERT_TRUE(!stack.empty());
  EXPECT_EQ(stack, other_stack);
}

TEST(BoolSpecializationStackTest, MoveAssignmentOperator) {
  const size_t stack_size = 3;
  Stack<bool> other_stack(2);
  for (size_t val = 1; val <= stack_size; ++val) {
    other_stack.push(val % 2 == 0);
  }
  Stack<bool> other_stack_cp{other_stack};

  Stack<bool> stack(2);
  stack = std::move(other_stack);

  EXPECT_EQ(stack.size(), stack_size);
  ASSERT_TRUE(!stack.empty());
  EXPECT_EQ(stack, other_stack_cp);
}

TEST(BoolSpecializationStackTest, Swap) {
  const size_t stack_size = 3;
  Stack<bool> x(2);
  Stack<bool> y(2);
  for (size_t val = 1; val <= stack_size; ++val) {
    x.push(val % 2 == 0);
    y.push(val % 2 == 1);
  }

  Stack<bool> a{x};
  Stack<bool> b{a};
  Stack<bool> c{y};
  Stack<bool> d{c};

  EXPECT_NE(a, d);
  EXPECT_NE(c, b);

  a.swap(c);

  EXPECT_EQ(a, d);
  EXPECT_EQ(c, b);
}

TEST(BoolSpecializationStackTest, NEQOperator) {
  const size_t stack_size = 3;
  Stack<bool> x(2);
  Stack<bool> y(2);
  for (size_t val = 1; val <= stack_size; ++val) {
    x.push(val % 2 == 0);
    y.push(val % 2 == 1);
  }

  EXPECT_NE(x, y);
}

TEST(BoolSpecializationStackTest, LTOperator) {
  const size_t stack_size = 3;
  Stack<bool> x(2);
  Stack<bool> y(2);
  for (size_t val = 1; val <= stack_size; ++val) {
    x.push(val % 2 == 0);
    y.push(val % 2 == 1);
  }

  EXPECT_LT(x, y);
}

TEST(BoolSpecializationStackTest, GTOperator) {
  const size_t stack_size = 3;
  Stack<bool> x(2);
  Stack<bool> y(2);
  for (size_t val = 1; val <= stack_size; ++val) {
    x.push(val % 2 == 0);
    y.push(val % 2 == 1);
  }

  EXPECT_GT(y, x);
}

TEST(BoolSpecializationStackTest, LEOperatorLT) {
  const size_t stack_size = 3;
  Stack<bool> x(2);
  Stack<bool> y(2);
  for (size_t val = 1; val <= stack_size; ++val) {
    x.push(val % 2 == 0);
    y.push(val % 2 == 1);
  }

  EXPECT_LE(x, y);
}

TEST(BoolSpecializationStackTest, LEOperatorEQ) {
  const size_t stack_size = 3;
  Stack<bool> x(2);
  Stack<bool> y(2);
  for (size_t val = 1; val <= stack_size; ++val) {
    x.push(val % 2 == 0);
    y.push(val % 2 == 0);
  }

  EXPECT_LE(x, y);
}

TEST(BoolSpecializationStackTest, GEOperatorGT) {
  const size_t stack_size = 3;
  Stack<bool> x(2);
  Stack<bool> y(2);
  for (size_t val = 1; val <= stack_size; ++val) {
    x.push(val % 2 == 0);
    y.push(val % 2 == 1);
  }

  EXPECT_GE(y, x);
}

TEST(BoolSpecializationStackTest, GEOperatorEQ) {
  const size_t stack_size = 3;
  Stack<bool> x(2);
  Stack<bool> y(2);
  for (size_t val = 1; val <= stack_size; ++val) {
    x.push(val % 2 == 0);
    y.push(val % 2 == 0);
  }

  EXPECT_GE(y, x);
}

TEST(BoolSpecializationStackTest, Top) {
  const size_t stack_size = 3;
  Stack<bool> stack(2);
  for (size_t val = 1; val <= stack_size; ++val) {
    stack.push(val % 2 == 0);
  }

  EXPECT_EQ(stack.get_top(), stack_size % 2 == 0);
  stack.set_top(stack_size % 2 != 0);
  EXPECT_EQ(stack.get_top(), stack_size % 2 != 0);
}

TEST(BoolSpecializationStackTest, Empty) {
  Stack<bool> stack(2);
  EXPECT_TRUE(stack.empty());

  Stack<bool> other_stack(2);
  stack = other_stack;
  EXPECT_TRUE(stack.empty());

  stack = Stack<bool>{};
  EXPECT_TRUE(stack.empty());
}

TEST(BoolSpecializationStackTest, Size) {
  {
    const size_t stack_size = 1;
    Stack<bool> stack(2);
    for (size_t val = 1; val <= stack_size; ++val) {
      stack.push(val % 2 == 0);
    }

    EXPECT_EQ(stack.size(), stack_size);
  }

  {
    const size_t stack_size = 2;
    Stack<bool> stack(2);
    for (size_t val = 1; val <= stack_size; ++val) {
      stack.push(val % 2 == 0);
    }

    EXPECT_EQ(stack.size(), stack_size);
  }

  {
    const size_t stack_size = 3;
    Stack<bool> stack(2);
    for (size_t val = 1; val <= stack_size; ++val) {
      stack.push(val % 2 == 0);
    }

    EXPECT_EQ(stack.size(), stack_size);
  }
}

TEST(BoolSpecializationStackTest, Pop) {
  const size_t stack_size = 1;
  Stack<bool> stack(2);
  for (size_t val = 1; val <= stack_size; ++val) {
    stack.push(val % 2 == 0);
  }

  for (ptrdiff_t i = stack_size; i >= 1; --i) {
    EXPECT_EQ(stack.get_top(), i % 2 == 0);
    stack.pop();
  }
}
