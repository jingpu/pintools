//Groups: @ingroup\s+(API_REF|KNOBS|IMG_BASIC_API|INS_BASIC_API|INS_INST_API|INS_BASIC_API_GEN_IA32|INS_BASIC_API_IA32|INS_BASIC_API_IPF|INS_MOD_API_GEN_IA32|SEC_BASIC_API|RTN_BASIC_API|REG_BASIC_API|REG_CPU_GENERIC|REG_CPU_IPF|REG_CPU_IA32|TRACE_BASIC_API|BBL_BASIC_API|SYM_BASIC_API|MISC_PRINT|MISC_PARSE|KNOB_API|KNOB_BASIC|KNOB_PRINT|LOCK|PIN_CONTROL|TRACE_VERSION_API|BUFFER_API|PROTO_API|PIN_PROCESS_API|PIN_THREAD_API|PIN_SYSCALL_API|WINDOWS_SYSCALL_API_UNDOC|DEBUG_API|ERROR_FILE_BASIC|TYPE_BASE|INSTLIB|ALARM|CODECACHE_API|CHILD_PROCESS_API|UTILS|IPF_UTILS_API|MISC|CONTEXT_API|PHYSICAL_CONTEXT_API|EXCEPTION_API|APPDEBUG_API|BUFFER_API|PROTO|INST_ARGS|DEPRECATED_PIN_API|INTERNAL_EXCEPTION_PRIVATE_UNDOCUMENTED|PIN_THREAD_PRIVATE|CHILD_PROCESS_INTERNAL|BBL_BASIC|ROGUE_BASIC_API|INS_BASIC_API_GEN_IPF|MESSAGE_TYPE|MESSAGE_BASIC|ERRFILE|MISC_BASIC|ITC_INST_API|CONTEXT_API_UNDOC|EXCEPTION_API_UNDOC|UNDOCUMENTED_PIN_API|OPIN|TRACE_VERSIONS
/* PIN API */

/* THIS FILE IS AUTOMAGICALLY GENERATED - DO NOT CHANGE DIRECTLY*/


const LEVEL_BASE::UINT32 SET_SIZE = 32;

                                                                  /* DO NOT EDIT */
template<LEVEL_BASE::UINT32 _min,
                    LEVEL_BASE::UINT32 _max, 
                    LEVEL_BASE::UINT32 _num_sets=((_max-_min)/SET_SIZE) + 1> class REGISTER_SET 
{
  private:
    LEVEL_BASE::UINT32 _set[_num_sets];
    
  public:
    REGISTER_SET<_min, _max, _num_sets>()
    {
        ASSERTX( (_max - _min) < (_num_sets * SET_SIZE) );
        for (LEVEL_BASE::UINT32 k=0; k< _num_sets; k++)
            _set[k] = 0;
    }

    REGISTER_SET<_min, _max, _num_sets>(LEVEL_BASE::UINT32 first, LEVEL_BASE::UINT32 last)
    {
        ASSERTX( (_max - _min) < (_num_sets * SET_SIZE) );
        for (LEVEL_BASE::UINT32 k=0; k< _num_sets; k++)
            _set[k] = 0;
        for (LEVEL_BASE::UINT32 r=first; r <= last; r++)
            Insert( REG(r) );
    }

    REG Min() const
    {
        return REG(_min);
    }

    REG Max() const
    {
        return REG(_max);
    }
    
    LEVEL_BASE::BOOL Contains(REG reg_no) const
    {
        const LEVEL_BASE::UINT32 i = LEVEL_BASE::UINT32(reg_no);
#if defined(__INTEL_COMPILER)
#pragma warning(push)
#pragma warning(disable : 186)
#endif
        ASSERTX( _min <= i && i <= _max );
#if defined(__INTEL_COMPILER)
#pragma warning(pop)
#endif

        const LEVEL_BASE::UINT32 set_no = (i - _min) / SET_SIZE;
        const LEVEL_BASE::UINT32 pos_no = (i - _min) % SET_SIZE;

        return (_set[ set_no ] & (1UL << pos_no)) != 0;
    }

    VOID InsertVector(REG reg_no,LEVEL_BASE::UINT32 vector)
    {
        const LEVEL_BASE::UINT32 i = LEVEL_BASE::UINT32(reg_no);
#if defined(__INTEL_COMPILER)
#pragma warning(push)        
#pragma warning(disable : 186)        
#endif
        ASSERTX( _min <= i && i <= _max );
#if defined(__INTEL_COMPILER)
#pragma warning(pop)
#endif
        const LEVEL_BASE::UINT32 set_no = (i - _min) / SET_SIZE;
        ASSERTX( 0 == (i - _min) % SET_SIZE );
        _set[set_no] = vector;
    }
    
    VOID InsertAll()
    {
        for (LEVEL_BASE::UINT32 k=0; k<_num_sets; k++)
            _set[k] = ~0;
    }

    VOID Insert(REG reg_no)
    {
        const LEVEL_BASE::UINT32 i = LEVEL_BASE::UINT32(reg_no);
#if defined(__INTEL_COMPILER)
#pragma warning(push)        
#pragma warning(disable : 186)        
#endif
        ASSERT( _min <= i && i <= _max,
                "_min(" + decstr(_min) + ") i(" + decstr(i) + ") _max( " +decstr(_max) + ")\n");
#if defined(__INTEL_COMPILER)
#pragma warning(pop)
#endif
        const LEVEL_BASE::UINT32 set_no = (i - _min) / SET_SIZE;
        const LEVEL_BASE::UINT32 pos_no = (i - _min) % SET_SIZE;

        _set[set_no] |= (1UL << pos_no);
    }

    VOID Remove(REG reg_no)
    {
        const LEVEL_BASE::UINT32 i = LEVEL_BASE::UINT32(reg_no);
#if defined(__INTEL_COMPILER)
#pragma warning(push)
#pragma warning(disable : 186)
#endif
        ASSERTX( _min <= i && i <= _max );
#if defined(__INTEL_COMPILER)
#pragma warning(pop)
#endif
        const LEVEL_BASE::UINT32 set_no = (i - _min) / SET_SIZE;
        const LEVEL_BASE::UINT32 pos_no = (i - _min) % SET_SIZE;

        _set[set_no] &= ~(1UL << pos_no);
    }
    
    VOID Clear()
    {
        for (LEVEL_BASE::UINT32 k=0; k<_num_sets; k++)
            _set[k] = 0;
    }

    VOID Invert()
    {
        for (LEVEL_BASE::UINT32 k=0; k<_num_sets; k++)
            _set[k] = ~_set[k];
    }

    REG PopNext()
    {
        for (LEVEL_BASE::UINT32 i=_min; i<=_max; i++)
        {
            const REG reg = REG(i);
            if ( Contains(reg) )
            {
                Remove(reg);
                return reg;
            }
        }
        
        return REG_INVALID();
    }
    
    REG PopNextFast()
    {
        for (LEVEL_BASE::UINT32 s=0; s<_num_sets; s++)
        {
            if (_set[s] == 0) continue;

            const LEVEL_BASE::UINT32 limit = MIN(_max, (s+1) * SET_SIZE);

            for (LEVEL_BASE::UINT32 i = _min + (s * SET_SIZE); i <= limit; i++)
            {
                const REG reg = REG(i);
                if ( Contains(reg) )
                {
                    Remove(reg);
                    return reg;
                }
            }
        }
        
        return REG_INVALID();
    }
    
    LEVEL_BASE::UINT32 PopCount() const
    {
        LEVEL_BASE::UINT32 count = 0;
        for ( LEVEL_BASE::UINT32 s=0; s<_num_sets; s++)
            count += BitCount( _set[s] );
        return count;
    }

    LEVEL_BASE::BOOL PopCountIsZero() const
    {
        for ( LEVEL_BASE::UINT32 s=0; s<_num_sets; s++) if( _set[s] != 0 ) return FALSE;
        return TRUE;
    }

    LEVEL_BASE::UINT32 HashKey() const
    {
        LEVEL_BASE::UINT32 hashKey = 0;
        for ( LEVEL_BASE::UINT32 s=0; s<_num_sets; s++)
           hashKey = HashData(hashKey, _set[s] );
        return hashKey;
    }
    
    VOID operator=(const REGISTER_SET<_min,_max,_num_sets> a)
    {
        for (LEVEL_BASE::UINT32 i=0; i<_num_sets; i++)
        {
            _set[i] = a._set[i];
        }
    }

    REGISTER_SET<_min,_max,_num_sets> operator| (const REGISTER_SET<_min,_max,_num_sets>& b) const 
    {
        REGISTER_SET<_min,_max,_num_sets> c;
  
        for (LEVEL_BASE::UINT32 i=0; i< _num_sets; i++)
            c._set[i] = _set[i] | b._set[i];
        return c;
        
    }

    REGISTER_SET<_min,_max,_num_sets> & operator|=(const REGISTER_SET<_min,_max,_num_sets>& b)
    {
  
        for (LEVEL_BASE::UINT32 i=0; i< _num_sets; i++)
            _set[i] |= b._set[i];
        return *this;
    }

    int operator== (const REGISTER_SET<_min,_max,_num_sets>& b) const 
    {
        for (LEVEL_BASE::UINT32 i=0; i< _num_sets; i++) if( _set[i] != b._set[i] ) return FALSE;
        return TRUE;
        
    }
    
    int operator!= (const REGISTER_SET<_min,_max,_num_sets>& b) const 
    {
        for (LEVEL_BASE::UINT32 i=0; i< _num_sets; i++) if( _set[i] != b._set[i] ) return TRUE;
        return FALSE;
    }

    REGISTER_SET<_min,_max,_num_sets> operator& (const REGISTER_SET<_min,_max,_num_sets>& b) const 
    {
        REGISTER_SET<_min,_max,_num_sets> c;
  
        for (LEVEL_BASE::UINT32 i=0; i< _num_sets; i++)
            c._set[i] = _set[i] & b._set[i];
        return c;
        
    }

    REGISTER_SET<_min,_max,_num_sets> operator- (const REGISTER_SET<_min,_max,_num_sets>& b) const
    {
        REGISTER_SET<_min,_max,_num_sets> c;
  
        for (LEVEL_BASE::UINT32 i=0; i< _num_sets; i++)
            c._set[i] = _set[i] & ~b._set[i];
        return c;
        
    }

    STATIC inline string PrintRange(REG start, REG stop)
    {
        if ( start == stop )
            return REG_StringShort( start );
        else
            return REG_StringShort( start ) + "-" + REG_StringShort( stop ) ;
    }

    string Dump () const
    {
        string s("{");
        for (LEVEL_BASE::UINT32 i=0; i< _num_sets; i++)
        {
            if (i!=0) s += ",";
            s += hexstr(_set[i]);
        }
        s += "}";
        return s;
    }
    
    string String () const
    {
        string s;
    
        s += "{";
        LEVEL_BASE::BOOL printed_range = FALSE;
        
        for (LEVEL_BASE::UINT32 i=_min; i<=_max; i++)
        {
            const REG reg = REG(i);
            
            if ( Contains(reg) ) 
            {
                if( printed_range ) s += ",";
                
                s += PrintRange(reg, reg);
                printed_range = TRUE;
            }
        }
    
        s += "}";
        
        return s;
    }

    string StringList() const
    {
        string s;
    
        s += "{";

        LEVEL_BASE::BOOL first = TRUE;
        
        for (LEVEL_BASE::UINT32 i=_min; i<=_max; i++)
        {
            const REG reg = REG(i);
            
            if ( Contains(reg) ) 
            {
                if (first)
                    first = FALSE;
                else
                    s += ",";
                    
                s += REG_StringShort(reg);
            }
        }
        
        s += "}";
        
        return s;
    }
    
};

                                                                  /* DO NOT EDIT */

