cmake_minimum_required(VERSION 3.19)
project(blockchain C)

set(CMAKE_C_STANDARD 99)

FIND_PACKAGE(OpenSSL REQUIRED)
PKG_CHECK_MODULES(openssl REQUIRED)

add_executable(blockchain src/main.c src/blockchain.c)
add_executable(simple examples/simple/main.c src/blockchain.c)
add_executable(cryptocurrency examples/cryptocurrency/main.c examples/cryptocurrency/cryptocurrency.c src/blockchain.c src/util/linkedlist.c)
TARGET_LINK_LIBRARIES(blockchain OpenSSL::SSL)
TARGET_LINK_LIBRARIES(simple OpenSSL::SSL)
TARGET_LINK_LIBRARIES(cryptocurrency OpenSSL::SSL)
