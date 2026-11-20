#pragma once

#define NO_COPY(Type)           \
	Type(const Type&) = delete; \
	Type& operator=(const Type&) = delete

#define NO_MOVE(Type)      \
	Type(Type&&) = delete; \
	Type& operator=(Type&&) = delete

#define MOVE_ONLY(Type)     \
	Type() = default;       \
	NO_COPY(Type);          \
	Type(Type&&) = default; \
	Type& operator=(Type&&) = default

#define NO_COPY_MOVE(Type) \
	NO_COPY(Type);         \
	NO_MOVE(Type)

#define NO_CREATE(Type) \
	Type() = delete;    \
	NO_COPY_MOVE(Type)
