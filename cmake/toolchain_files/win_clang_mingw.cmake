# set(CMAKE_SYSTEM_PROCESSOR x86_64)  # 或 i686 用于 32 位

# 指定编译器
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)
# set(CMAKE_RC_COMPILER x86_64-w64-mingw32-windres)  # Windows 资源编译器

# 设置目标环境
# set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
# set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
# set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# 额外选项（可选）
set(CMAKE_C_FLAGS "--target=x86_64-w64-mingw32")
set(CMAKE_CXX_FLAGS "--target=x86_64-w64-mingw32")
set(CMAKE_EXE_LINKER_FLAGS "--target=x86_64-w64-mingw32 -fuse-ld=lld -pthread")
