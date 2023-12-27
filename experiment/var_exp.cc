/**
 * @file var_exp.cc
 * @author Li Pingan (lipingan.dev@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-12-27
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <iostream>
#include <memory>

struct Var {

  struct Storage {
    virtual void Add(void *args) = 0;

    virtual void *Get() = 0;
  };

  template <typename Type> struct StorageImpl : public Storage {

    explicit StorageImpl(Type const &value) : value_(value) {}

    void Add(void *args) override { value_ += *(static_cast<Type *>(args)); }
    Type value_;

    void *Get() override { return &value_; }
  };

  template <typename Type>
  explicit Var(Type const &value) : storage_(new StorageImpl<Type>(value)) {}

  template <typename Type> void Set(Type const &value) {
    storage_ = std::make_unique<StorageImpl<Type>>(value);
  }

  template <typename Type> Type const &Get() {
    return static_cast<Type const &>(*static_cast<Type *>(storage_->Get()));
  }

  std::unique_ptr<Storage> storage_ = nullptr;
};

int main() {
  Var var{123};
  std::cout << var.Get<int>() << std::endl;
  var.Set(std::string{"000456"});
  std::cout << var.Get<std::string>() << std::endl;
  var.Set(789.1f);
  std::cout << var.Get<float>() << std::endl;
}