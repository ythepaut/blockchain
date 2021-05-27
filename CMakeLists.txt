cmake_minimum_required(VERSION 3.19)
project(blockchain C)

set(CMAKE_C_STANDARD 99)

FIND_PACKAGE(OpenSSL REQUIRED)
PKG_CHECK_MODULES(openssl REQUIRED)

add_executable(blockchain src/main.c src/blockchain.c)
TARGET_LINK_LIBRARIES(blockchain OpenSSL::SSL)
