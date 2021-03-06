// Copyright (c) 2014 Baidu, Inc.
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//     http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// Authors: Rujie Jiang (jiangrujie@baidu.com) 
//          Ge,Jun (gejun@baidu.com)

#ifndef BRPC_POLICY_NOVA_PBRPC_PROTOCOL_H
#define BRPC_POLICY_NOVA_PBRPC_PROTOCOL_H

#include "brpc/nshead_pb_service_adaptor.h"
#include "brpc/policy/nshead_protocol.h" 


namespace brpc {
namespace policy {

// Actions to a (server) response in nova_pbrpc format.
void ProcessNovaResponse(InputMessageBase* msg);

void SerializeNovaRequest(butil::IOBuf* buf, Controller* cntl,
                                 const google::protobuf::Message* request);

// Pack `request' to `method' into `buf'.
void PackNovaRequest(butil::IOBuf* buf,
                     SocketMessage** user_message_out,
                     uint64_t correlation_id,
                     const google::protobuf::MethodDescriptor* method,
                     Controller* controller,
                     const butil::IOBuf& request,
                     const Authenticator* auth);

class NovaServiceAdaptor : public NsheadPbServiceAdaptor {
public:
    void ParseNsheadMeta(const Server& svr,
                        const NsheadMessage& request,
                        Controller*,
                        NsheadMeta* out_meta) const;

    void ParseRequestFromIOBuf(
        const NsheadMeta& meta, const NsheadMessage& ns_req,
        Controller* controller, google::protobuf::Message* pb_req) const;

    void SerializeResponseToIOBuf(
        const NsheadMeta& meta,
        Controller* controller,
        const google::protobuf::Message* pb_res,
        NsheadMessage* ns_res) const;
};

}  // namespace policy
} // namespace brpc


#endif // BRPC_POLICY_NOVA_PBRPC_PROTOCOL_H
