/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: ProtoBuffers.proto */

#ifndef PROTOBUF_C_ProtoBuffers_2eproto__INCLUDED
#define PROTOBUF_C_ProtoBuffers_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1000000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1001001 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif


typedef struct _Message Message;


/* --- enums --- */


/* --- messages --- */

struct  _Message
{
  ProtobufCMessage base;
  int32_t type;
  char *username;
  char *chat;
  protobuf_c_boolean has_query_id_min;
  int32_t query_id_min;
  protobuf_c_boolean has_query_id_max;
  int32_t query_id_max;
  char *query_resp;
  char *log_resp;
};
#define MESSAGE__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&message__descriptor) \
    , 0, NULL, NULL, 0,0, 0,0, NULL, NULL }


/* Message methods */
void   message__init
                     (Message         *message);
size_t message__get_packed_size
                     (const Message   *message);
size_t message__pack
                     (const Message   *message,
                      uint8_t             *out);
size_t message__pack_to_buffer
                     (const Message   *message,
                      ProtobufCBuffer     *buffer);
Message *
       message__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   message__free_unpacked
                     (Message *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*Message_Closure)
                 (const Message *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCMessageDescriptor message__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_ProtoBuffers_2eproto__INCLUDED */
