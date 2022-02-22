#ifndef BOOST_QVM_VEC_HPP_INCLUDED
#define BOOST_QVM_VEC_HPP_INCLUDED

// Copyright 2008-2022 Emil Dotchevski and Reverge Studios, Inc.

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/qvm/detail/vec_assign.hpp>
#include <boost/qvm/assert.hpp>
#include <boost/qvm/static_assert.hpp>

namespace boost { namespace qvm {

template <class T,int D>
struct
vec
    {
    T a[D];
    template <class R>
    operator R() const
        {
        R r;
        assign(r,*this);
        return r;
        }
    };

#ifdef __GNUC__

template <>
struct
vec<float,4>
    {
    typedef float v4sf __attribute__ ((vector_size (16)));
    v4sf a;
    template <class R>
    operator R() const
        {
        R r;
        assign(r,*this);
        return r;
        }
    };

template <>
struct
vec<double,4>
    {
    typedef double v4sd __attribute__ ((vector_size (32)));
    v4sd a;
    template <class R>
    operator R() const
        {
        R r;
        assign(r,*this);
        return r;
        }
    };

#endif

template <class V>
struct vec_traits;

template <class T,int Dim>
struct
vec_traits< vec<T,Dim> >
    {
    typedef vec<T,Dim> this_vector;
    typedef T scalar_type;
    static int const dim=Dim;

    template <int I>
    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type
    read_element( this_vector const & x )
        {
        BOOST_QVM_STATIC_ASSERT(I>=0);
        BOOST_QVM_STATIC_ASSERT(I<dim);
        return x.a[I];
        }

    template <int I>
    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    void
    write_element( this_vector & x, scalar_type s )
        {
        BOOST_QVM_STATIC_ASSERT(I>=0);
        BOOST_QVM_STATIC_ASSERT(I<dim);
        x.a[I] = s;
        }

    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type
    read_element_idx( int i, this_vector const & x )
        {
        BOOST_QVM_ASSERT(i>=0);
        BOOST_QVM_ASSERT(i<dim);
        return x.a[i];
        }

    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    void
    write_element_idx( int i, this_vector & x, scalar_type s )
        {
        BOOST_QVM_ASSERT(i>=0);
        BOOST_QVM_ASSERT(i<dim);
        x.a[i] = s;
        }
    };

} }

#endif
