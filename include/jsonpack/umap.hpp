#ifndef JSONPACK_UMAP_HPP
#define JSONPACK_UMAP_HPP

#include <unordered_map>

#include "jsonpack/exceptions.hpp"

JSONPACK_API_BEGIN_NAMESPACE

/**
 * Represent a keys in the json string
 */
struct key
{

    bool operator== (const key &k1) const
    {
        std::size_t min =  std::min( k1._bytes, _bytes );
        bool ret = ( memcmp(k1._ptr, _ptr, min) == 0 );
        return ret;
    }

    key():_ptr(nullptr), _bytes(0){}

    key(const key& k):
        _ptr(k._ptr),
        _bytes(k._bytes)
    {}

#ifndef _MSC_VER
    const char * _ptr = nullptr;
    std::size_t _bytes = 0;
#else
    const char * _ptr;
    std::size_t _bytes;
#endif
};


/**
 * Collection of key/value pairs (javascript object)
 * std::unordered_map adapter overloading operator[](const char*) for easy lookup
 */
template<class _KeyType,
         class _ValType,
         class _Hasher >
class umap
{

public:
    typedef typename std::unordered_map<_KeyType, _ValType, _Hasher > base_map;
    typedef typename base_map::mapped_type mapped_type;
    typedef typename base_map::key_type key_type;
    typedef typename base_map::size_type size_type;

    typedef typename base_map::iterator iterator;
    typedef typename base_map::const_iterator const_iterator;

    base_map _umap;
public:

    explicit umap(size_type __n = 10):_umap(__n)
    {}

    iterator begin() noexcept
    {return _umap.begin();}

    const_iterator begin() const noexcept
    { return _umap.begin();}

    iterator end() noexcept
    { return _umap.end();}

    const_iterator end() const noexcept
    { return _umap.end();}

    iterator find(const key_type& __x)
    { return _umap.find(__x); }

    const_iterator find(const key_type& __x) const
    { return _umap.find(__x); }

    mapped_type& operator[](const key_type& __k)
    { return _umap[__k];}

    mapped_type& operator[](key_type&& __k)
    {return _umap[std::move(__k)];}

    void clear() noexcept
    { _umap.clear(); }

    /**
     * Overload for easy lookup. Throw exception on fail
     */
    mapped_type operator[](const char* str_key)
    {
        key obj_key;
        obj_key._ptr = str_key;
        obj_key._bytes = strlen(str_key);

        const_iterator found = find(obj_key);
        if(found != end())
            return found->second;

        std::string msg = "key '";
        msg += str_key;
        msg+= "' not found!";
        throw jsonpack_error( msg.c_str() );
    }
};

JSONPACK_API_END_NAMESPACE

#endif // JSONPACK_UMAP_HPP

