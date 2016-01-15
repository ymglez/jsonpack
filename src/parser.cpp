
/**
 *  Jsonpack - JSON syntax parser
 *
 *  Copyright (c) 2015 Yadiel Martinez Gonzalez <ymglez2015@gmail.com>
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#include <string.h>
#include <string>

#include "jsonpack/parser.hpp"
#include "jsonpack/object.hpp"
#include "jsonpack/exceptions.hpp"

JSONPACK_API_BEGIN_NAMESPACE

/** ****************************************************************************
 ******************************** SCANER ***************************************
 *******************************************************************************/

void scanner::init(const char* json, const std::size_t &len)
{
    _size = len;
    if(_size > 0)
    {
        _source = (_size != 0) ? json : nullptr;
        _i = 0;
        _c = _source[0];
    }
    else
    {
        throw invalid_json("Empty json string");
    }
}

void scanner::advance()
{
    _c = _source[++_i];
}

jsonpack_token_type scanner::next()
{
    switch ( _c )
    {
    case '{':
        advance();
        return JTK_OPEN_KEY;
        break;
    case '}':
        advance();
        return JTK_CLOSE_KEY;
        break;
    case '[':
        advance();
        return JTK_OPEN_BRACKET;
        break;
    case ']':
        advance();
        return JTK_CLOSE_BRACKET;
        break;
    case ':':
        advance();
        return JTK_COLON;
        break;
    case ',':
        advance();
        return JTK_COMMA;
        break;
    case '"':
        return string_literal();
        break;
    case '\0':
        if(_i < _size -1) advance();
        return JTK_EOF;

    default:
        if(std::isspace(  _c ) )
        {
            advance();
            return next();
        }
        else
        {
            return other_value();
        }
    }
}

jsonpack_token_type scanner::string_literal()
{
    _start_token_pos = _i;
    advance();

    while( _c != '"' && _i < _size )
    {
        if( _c == '\\') // escape
        {
            advance();
            switch (_c)
            {
            case '"':
            case '\\':
            case '/':
            case 'b':
            case 'f':
            case 'n':
            case 'r':
            case 't':
                break;
            case 'u':
                for (unsigned i = 0; i < 4; ++i)
                {
                    advance();
                    if (!(_c >= '0' && _c <= '9') &&
                            !(_c >= 'A' && _c <= 'F') &&
                            !(_c >= 'a' && _c <= 'f') )
                        throw invalid_json("JSON syntax error: Invalid unicode escape hex value");
                }
                break;
            default:
                throw invalid_json("JSON syntax error: Invalid escape");
            }
        }
        else if ((unsigned)_c < 0x20)
        {
            throw invalid_json("JSON syntax error: Control characters are not allowed in string literals");
        }

        advance();
    }

    if( _i < _size - 1 )//last char must be '}' or ']'
    {
        advance();
        return JTK_STRING_LITERAL;
    }

    return JTK_INVALID;
}

jsonpack_token_type scanner::other_value()
{
    if(std::isdigit( _c ) || _c == '-' )
        return number();

    if(std::isalpha( _c ) )
    {
        std::string lex = "";
        lex.reserve(8);
        _start_token_pos = _i;
        do
        {
            lex += _c;
            advance();
        }
        while( std::isalpha(_c) && _i < _size );

        if(lex.compare("true") == 0 || lex.compare("TRUE") == 0 )
            return JTK_TRUE;
        if(lex.compare("false") == 0 || lex.compare("FALSE") == 0 )
            return JTK_FALSE;
        if(lex.compare("null") == 0 || lex.compare("NULL") == 0 )
            return JTK_NULL;
    }

    return JTK_INVALID;
}

jsonpack_token_type scanner::number()
{
    int_fast8_t state = 1;
    _start_token_pos = _i;

    if(_c == '0') state = -1;

    if(_c == '-') state = 0;

    while (true)
    {
        switch (state)
        {
        case -1://0
            advance();
            if( std::isdigit( _c ) ) throw invalid_json("JSON Syntax error: Numbers cannot have leading zeroes");

            if(_c == '.') state = 2;
            else if(_c == 'e' || _c == 'E') state = 4;
            else return JTK_INTEGER;
            break;
        case 0://-
            advance();
            if( std::isdigit( _c ) ) state = 1;
            else if(_c == '0') state = -1;
            else return JTK_INVALID;
            break;
        case 1:
            do
            {
                advance();
            }
            while( std::isdigit( _c ) && _i < _size );

            if(_c == '.') state = 2;
            else if(_c == 'e' || _c == 'E') state = 4;
            else return JTK_INTEGER;

            break;
        case 2:
            advance();
            if( std::isdigit(_c) ) state = 3;
            else return JTK_INVALID;
            break;
        case 3:
            do
            {
                advance();
            }
            while( std::isdigit(_c) && _i < _size );

            if(_c == 'e' || _c == 'E') state = 4;
            else return JTK_REAL;

            break;
        case 4:
            advance();
            if(_c == '+' || _c == '-') state = 5;
            else if(std::isdigit(_c)) state = 6;
            else return JTK_INVALID;

            break;
        case 5:
            advance();
            if(std::isdigit(_c)) state = 6;
            else return JTK_INVALID;

            break;
        case 6:
            do
            {
                advance();
            }
            while( std::isdigit(_c) && _i < _size );

            return JTK_REAL;

            break;
        default:
            return JTK_INVALID;
            break;
        }
    }
}

key scanner::get_last_key( bool expect_str_literal = false )
{
    char * lex = const_cast<char*>(_source)  ;
    lex += _start_token_pos + expect_str_literal;

    key k;
    k._ptr = lex;
    k._bytes = _i - _start_token_pos - 2*expect_str_literal;

    return k;
}


/** ****************************************************************************
 ******************************** PARSER ***************************************
 *******************************************************************************/

parser::parser():
    _tk(JTK_INVALID),
    _s()
{}

parser::parser(const parser &p):
    _tk(p._tk),
    _s(p._s)
{}

//---------------------------------------------------------------------------------------------------
bool parser::match(const jsonpack_token_type &token)
{
    if(_tk != token)
    {
        std::string token_str[] =
        {
            "Open object",
            "Close object",
            "Colon",
            "Comma",
            "Open array",
            "Close array",
            "String value",
            "Number value",
            "Number value",
            "Boolean value",
            "Boolean value",
            "Null value",
            "Ivalid value",
            "End of input"
        };

        char msg[256];
        sprintf(msg, "JSON syntax error: Expect '%s' but found '%s' at %d", token_str[token].c_str(), token_str[_tk].c_str(), _s._i);

        throw invalid_json(msg);
    }

    advance();
    return true;
}

//---------------------------------------------------------------------------------------------------
bool parser::is_literal(const jsonpack_token_type &token)
{
    return( token == JTK_INTEGER ||
            token == JTK_REAL ||
            token == JTK_STRING_LITERAL ||
            token == JTK_TRUE ||
            token == JTK_FALSE ||
            token == JTK_NULL );
}

//---------------------------------------------------------------------------------------------------
void parser::advance()
{
    _tk = _s.next();
}

//---------------------------------------------------------------------------------------------------
bool parser::json_validate(const char *json,const std::size_t &len, object_t &members )
{
    _s.init(json, len);
    advance();

    return match(JTK_OPEN_KEY) && item_list(members) && match(JTK_CLOSE_KEY) && match(JTK_EOF);
}

//---------------------------------------------------------------------------------------------------
bool parser::json_validate(const char *json,const std::size_t &len, array_t &elemets )
{
    _s.init(json, len);
    advance();

    return match(JTK_OPEN_BRACKET) && array_list(elemets) && match(JTK_CLOSE_BRACKET) && match(JTK_EOF);
}

//---------------------------------------------------------------------------------------------------
std::string parser::err_msg()
{
    char buff[125];
    sprintf(buff, "JSON syntax error: near \'%c\' at position %u", _s._c, _s._i);    return std::string(buff);
}

//---------------------------------------------------------------------------------------------------
bool parser::item_list(object_t &members)
{
    if(_tk == JTK_CLOSE_KEY)
        return true;

    if( item(members) )
    {
        if(_tk == JTK_COMMA )
        {
            advance();
            if( _tk != JTK_STRING_LITERAL)
                throw invalid_json("JSON Syntax error: Expect valid string after comma");

            return item_list(members);
        }
        return true;
    }

    return false;
}

//---------------------------------------------------------------------------------------------------
bool parser::item(object_t &members)
{
    if( _tk == JTK_STRING_LITERAL ) //key
    {
        /**
         * Get current object key
         */
        key k = _s.get_last_key(true);

        advance();
        return match(JTK_COLON) && value(k, members); // : value
    }

    return false;
}

//---------------------------------------------------------------------------------------------------
bool parser::value(key k, object_t &members)
{
    if( is_literal(_tk) ) //literals
    {

        /**
         * Add value into the map with current key
         */
        bool is_str = (_tk == JTK_STRING_LITERAL);
        position pos;
        pos._pos = const_cast<char*>(_s._source +(_s._start_token_pos + is_str));
        pos._count = _s._i - _s._start_token_pos - 2*is_str;
        pos._type = _tk;

        jsonpack::value val(pos);
        members[k] = val;

        advance();
        return true;
    }

    if( _tk == JTK_OPEN_KEY )
    {
        advance();

        object_t o(16);
        bool object_ok = item_list(o);

        if(object_ok)
        {
            members[k] = new object_t(std::move(o));

            return match(JTK_CLOSE_KEY);
        }
        return false;
    }

    if( _tk == JTK_OPEN_BRACKET )
    {
        advance();

        array_t a;
        bool array_ok = array_list(a);

        if(array_ok)
        {
            members[k] = new array_t(std::move(a));

            return match(JTK_CLOSE_BRACKET);
        }
        return false;
    }

    return false;
}

//---------------------------------------------------------------------------------------------------
bool parser::array_list(array_t &elemets)
{
    if(_tk == JTK_CLOSE_BRACKET)
        return true;

    if( value(elemets) )
    {
        if(_tk == JTK_COMMA )
        {
            advance();
            if(!is_literal(_tk) && _tk != JTK_OPEN_BRACKET && _tk != JTK_OPEN_KEY)
                throw invalid_json("JSON Synatax error: Expect valid value after comma");

            return array_list(elemets);
        }
        return true;
    }
    return false;
}

//---------------------------------------------------------------------------------------------------
bool parser::value( array_t &elemets)
{
    if( is_literal(_tk) ) //literals
    {
        /**
         * Add value into the vector
         */
        bool is_str = (_tk == JTK_STRING_LITERAL);
        position pos;
        pos._pos = const_cast<char*>(_s._source +(_s._start_token_pos + is_str));
        pos._count = _s._i - _s._start_token_pos - 2*is_str;
        pos._type = _tk;

        elemets.emplace_back(pos);

        advance();
        return true;
    }

    if( _tk == JTK_OPEN_KEY )
    {
        advance();

        object_t o;
        bool object_ok = item_list(o);

        if(object_ok)
        {
            elemets.emplace_back(new object_t(std::move(o)));

            return match(JTK_CLOSE_KEY);
        }

        return false;
    }

    if( _tk == JTK_OPEN_BRACKET )
    {
        advance();

        array_t a;
        bool array_ok = array_list(a);

        if(array_ok)
        {
            elemets.emplace_back(new array_t(std::move(a)));

            return match(JTK_CLOSE_BRACKET);
        }
        return false;
    }

    return false;
}


JSONPACK_API_END_NAMESPACE
