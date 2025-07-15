# 设置所有依赖库的根目录
set(FETCHCONTENT_BASE_DIR ${CMAKE_SOURCE_DIR}/external CACHE PATH "下载依赖库的根目录")
# 第三方库安装路径
set(THIRD_PARTY_INSTALL_DIR ${CMAKE_SOURCE_DIR}/out/third_party CACHE PATH "第三方库安装路径")

# 使用FetchContent模块
include(FetchContent)

# 声明并下载Google Test
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.12.1
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
