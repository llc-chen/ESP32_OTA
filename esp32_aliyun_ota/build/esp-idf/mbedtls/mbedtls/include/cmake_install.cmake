# Install script for directory: J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/esp32_aliyun_ota")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "J:/Espressif/tools/xtensa-esp32-elf/esp-2021r2-patch5-8.4.0/xtensa-esp32-elf/bin/xtensa-esp32-elf-objdump.exe")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mbedtls" TYPE FILE PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ FILES
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/aes.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/aesni.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/arc4.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/aria.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/asn1.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/asn1write.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/base64.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/bignum.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/blowfish.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/bn_mul.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/camellia.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/ccm.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/certs.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/chacha20.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/chachapoly.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/check_config.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/cipher.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/cipher_internal.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/cmac.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/compat-1.3.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/config.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/config_psa.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/constant_time.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/ctr_drbg.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/debug.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/des.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/dhm.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/ecdh.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/ecdsa.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/ecjpake.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/ecp.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/ecp_internal.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/entropy.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/entropy_poll.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/error.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/gcm.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/havege.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/hkdf.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/hmac_drbg.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/md.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/md2.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/md4.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/md5.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/md_internal.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/memory_buffer_alloc.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/net.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/net_sockets.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/nist_kw.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/oid.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/padlock.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/pem.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/pk.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/pk_internal.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/pkcs11.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/pkcs12.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/pkcs5.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/platform.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/platform_time.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/platform_util.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/poly1305.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/psa_util.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/ripemd160.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/rsa.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/rsa_internal.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/sha1.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/sha256.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/sha512.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/ssl.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/ssl_cache.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/ssl_ciphersuites.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/ssl_cookie.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/ssl_internal.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/ssl_ticket.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/threading.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/timing.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/version.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/x509.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/x509_crl.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/x509_crt.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/x509_csr.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/mbedtls/xtea.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/psa" TYPE FILE PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ FILES
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/psa/crypto.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/psa/crypto_builtin_composites.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/psa/crypto_builtin_primitives.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/psa/crypto_compat.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/psa/crypto_config.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/psa/crypto_driver_common.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/psa/crypto_driver_contexts_composites.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/psa/crypto_driver_contexts_primitives.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/psa/crypto_extra.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/psa/crypto_platform.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/psa/crypto_se_driver.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/psa/crypto_sizes.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/psa/crypto_struct.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/psa/crypto_types.h"
    "J:/Espressif/frameworks/esp-idf-v4.4.3/components/mbedtls/mbedtls/include/psa/crypto_values.h"
    )
endif()

