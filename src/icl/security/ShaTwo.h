/**
 * \file sha256.h
 *
 * \brief This file contains SHA-224 and SHA-256 definitions and functions.
 *
 * The Secure Hash Algorithms 224 and 256 (SHA-224 and SHA-256) cryptographic
 * hash functions are defined in <em>FIPS 180-4: Secure Hash Standard (SHS)</em>.
 */
/*
 *  Copyright (C) 2006-2018, Arm Limited (or its affiliates), All Rights Reserved
 *  SPDX-License-Identifier: Apache-2.0
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may
 *  not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 *  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  This file is part of Mbed TLS (https://tls.mbed.org)
 */
#ifndef SHA256_H
#define SHA256_H


#include "mbedtls/sha256.h"

#include <stddef.h>
#include <cstdint>
#include <string>


class Sha256
{
public:
    ~Sha256();
    Sha256();

    bool Update(const std::string &s);
    bool Final(std::string &hmac);
private:
    mbedtls_sha256_context mCtx;
};

std::string hmac_compute(const std::string &key, const std::string &message);


#endif /* mbedtls_sha256.h */

