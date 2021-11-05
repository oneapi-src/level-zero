/*
 *
 * Copyright (C) 2019-2021 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */
#pragma once
#include <memory>
#include <unordered_map>
#include <mutex>

//////////////////////////////////////////////////////////////////////////
/// a abstract factory for creation of singleton objects
template<typename _singleton_t, typename _key_t>
class singleton_factory_t
{
protected:
    using singleton_t = _singleton_t;
    using key_t = typename std::conditional<std::is_pointer<_key_t>::value, size_t, _key_t>::type;

    using ptr_t = std::unique_ptr < singleton_t >;
    using map_t = std::unordered_map < key_t, ptr_t >;

    std::mutex mut; ///< lock for thread-safety
    map_t map;      ///< single instance of singleton for each unique key

    //////////////////////////////////////////////////////////////////////////
    /// extract the key from parameter list and if necessary, convert type
    template<typename... Ts>
    key_t getKey( _key_t _key, Ts&&... _params )
    {
        return reinterpret_cast<key_t>( _key );
    }

public:
    //////////////////////////////////////////////////////////////////////////
    /// default ctor/dtor
    singleton_factory_t() = default;
    ~singleton_factory_t() = default;

    //////////////////////////////////////////////////////////////////////////
    /// gets a pointer to a unique instance of singleton
    /// if no instance exists, then creates a new instance
    /// the params are forwarded to the ctor of the singleton
    /// the first parameter must be the unique identifier of the instance
    template<typename... Ts>
    _singleton_t* getInstance( Ts&&... _params )
    {
        auto key = getKey( std::forward<Ts>( _params )... );

        if(key == 0) // No zero keys allowed in map
            return static_cast<_singleton_t*>(0);

        std::lock_guard<std::mutex> lk( mut );
        auto iter = map.find( key );

        if( map.end() == iter )
        {
            auto ptr = std::make_unique<singleton_t>( std::forward<Ts>( _params )... );
            iter = map.emplace( key, std::move( ptr ) ).first;
        }
        return iter->second.get();
    }

    //////////////////////////////////////////////////////////////////////////
    /// once the key is no longer valid, release the singleton
    void release( _key_t _key )
    {
        std::lock_guard<std::mutex> lk( mut );
        map.erase( getKey( _key ) );
    }
};
