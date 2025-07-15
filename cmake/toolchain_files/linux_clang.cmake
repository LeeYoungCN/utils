set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")

# 启用RPATH设置
set(CMAKE_SKIP_BUILD_RPATH FALSE)  # 不跳过构建时的RPATH
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)  # 构建时使用默认RPATH
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)  # 使用链接路径作为RPATH的一部分
# 设置安装后的RPATH（指向动态库所在目录）
# 对于UNIX系统（Linux/macOS）
set(CMAKE_INSTALL_RPATH "$ORIGIN/../lib")  # 假设库安装在bin目录的上一级的lib目录
# 也可以添加绝对路径，例如：
# set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
