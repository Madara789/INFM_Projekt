// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: subscale.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_subscale_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_subscale_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3021000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3021008 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_subscale_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_subscale_2eproto {
  static const uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_subscale_2eproto;
namespace subscale {
class SubscaleData;
struct SubscaleDataDefaultTypeInternal;
extern SubscaleDataDefaultTypeInternal _SubscaleData_default_instance_;
class SubspaceTable;
struct SubspaceTableDefaultTypeInternal;
extern SubspaceTableDefaultTypeInternal _SubspaceTable_default_instance_;
}  // namespace subscale
PROTOBUF_NAMESPACE_OPEN
template<> ::subscale::SubscaleData* Arena::CreateMaybeMessage<::subscale::SubscaleData>(Arena*);
template<> ::subscale::SubspaceTable* Arena::CreateMaybeMessage<::subscale::SubspaceTable>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace subscale {

// ===================================================================

class SubscaleData final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:subscale.SubscaleData) */ {
 public:
  inline SubscaleData() : SubscaleData(nullptr) {}
  ~SubscaleData() override;
  explicit PROTOBUF_CONSTEXPR SubscaleData(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  SubscaleData(const SubscaleData& from);
  SubscaleData(SubscaleData&& from) noexcept
    : SubscaleData() {
    *this = ::std::move(from);
  }

  inline SubscaleData& operator=(const SubscaleData& from) {
    CopyFrom(from);
    return *this;
  }
  inline SubscaleData& operator=(SubscaleData&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const SubscaleData& default_instance() {
    return *internal_default_instance();
  }
  static inline const SubscaleData* internal_default_instance() {
    return reinterpret_cast<const SubscaleData*>(
               &_SubscaleData_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(SubscaleData& a, SubscaleData& b) {
    a.Swap(&b);
  }
  inline void Swap(SubscaleData* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(SubscaleData* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  SubscaleData* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<SubscaleData>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const SubscaleData& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const SubscaleData& from) {
    SubscaleData::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena, bool is_message_owned);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(SubscaleData* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "subscale.SubscaleData";
  }
  protected:
  explicit SubscaleData(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kIdFieldNumber = 1,
  };
  // int64 id = 1;
  void clear_id();
  int64_t id() const;
  void set_id(int64_t value);
  private:
  int64_t _internal_id() const;
  void _internal_set_id(int64_t value);
  public:

  // @@protoc_insertion_point(class_scope:subscale.SubscaleData)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    int64_t id_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_subscale_2eproto;
};
// -------------------------------------------------------------------

class SubspaceTable final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:subscale.SubspaceTable) */ {
 public:
  inline SubspaceTable() : SubspaceTable(nullptr) {}
  ~SubspaceTable() override;
  explicit PROTOBUF_CONSTEXPR SubspaceTable(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  SubspaceTable(const SubspaceTable& from);
  SubspaceTable(SubspaceTable&& from) noexcept
    : SubspaceTable() {
    *this = ::std::move(from);
  }

  inline SubspaceTable& operator=(const SubspaceTable& from) {
    CopyFrom(from);
    return *this;
  }
  inline SubspaceTable& operator=(SubspaceTable&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const SubspaceTable& default_instance() {
    return *internal_default_instance();
  }
  static inline const SubspaceTable* internal_default_instance() {
    return reinterpret_cast<const SubspaceTable*>(
               &_SubspaceTable_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(SubspaceTable& a, SubspaceTable& b) {
    a.Swap(&b);
  }
  inline void Swap(SubspaceTable* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(SubspaceTable* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  SubspaceTable* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<SubspaceTable>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const SubspaceTable& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const SubspaceTable& from) {
    SubspaceTable::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena, bool is_message_owned);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(SubspaceTable* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "subscale.SubspaceTable";
  }
  protected:
  explicit SubspaceTable(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kIdFieldNumber = 1,
  };
  // int64 id = 1;
  void clear_id();
  int64_t id() const;
  void set_id(int64_t value);
  private:
  int64_t _internal_id() const;
  void _internal_set_id(int64_t value);
  public:

  // @@protoc_insertion_point(class_scope:subscale.SubspaceTable)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    int64_t id_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_subscale_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// SubscaleData

// int64 id = 1;
inline void SubscaleData::clear_id() {
  _impl_.id_ = int64_t{0};
}
inline int64_t SubscaleData::_internal_id() const {
  return _impl_.id_;
}
inline int64_t SubscaleData::id() const {
  // @@protoc_insertion_point(field_get:subscale.SubscaleData.id)
  return _internal_id();
}
inline void SubscaleData::_internal_set_id(int64_t value) {
  
  _impl_.id_ = value;
}
inline void SubscaleData::set_id(int64_t value) {
  _internal_set_id(value);
  // @@protoc_insertion_point(field_set:subscale.SubscaleData.id)
}

// -------------------------------------------------------------------

// SubspaceTable

// int64 id = 1;
inline void SubspaceTable::clear_id() {
  _impl_.id_ = int64_t{0};
}
inline int64_t SubspaceTable::_internal_id() const {
  return _impl_.id_;
}
inline int64_t SubspaceTable::id() const {
  // @@protoc_insertion_point(field_get:subscale.SubspaceTable.id)
  return _internal_id();
}
inline void SubspaceTable::_internal_set_id(int64_t value) {
  
  _impl_.id_ = value;
}
inline void SubspaceTable::set_id(int64_t value) {
  _internal_set_id(value);
  // @@protoc_insertion_point(field_set:subscale.SubspaceTable.id)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace subscale

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_subscale_2eproto
