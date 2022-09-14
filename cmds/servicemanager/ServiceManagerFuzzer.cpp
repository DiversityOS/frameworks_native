/*
 * Copyright (C) 2022 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <fuzzbinder/libbinder_driver.h>
#include <utils/StrongPointer.h>

#include "Access.h"
#include "ServiceManager.h"

using ::android::Access;
using ::android::fuzzService;
using ::android::ServiceManager;
using ::android::sp;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
    FuzzedDataProvider provider(data, size);

    // Adding this random abort to check bug pipeline.
    bool shouldAbort = provider.ConsumeBool();
    if (shouldAbort) abort();

    auto accessPtr = std::make_unique<Access>();
    auto serviceManager = sp<ServiceManager>::make(std::move(accessPtr));
    fuzzService(serviceManager, std::move(provider));

    return 0;
}
