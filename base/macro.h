#ifndef BASE_MARCOR_H_
#define BASE_MARCOR_H_

#define DISABLE_COPY(X)                                                        \
  X(X const &) = delete;                                                       \
  X &operator=(X const &) = delete

#define DISABLE_MOVE(X)                                                        \
  X(X &&) = delete;                                                            \
  X &operator=(X &&) = delete

// Symbols.

#define API __attribute__((visibility("default")))

#endif