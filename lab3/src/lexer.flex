%{
/* C++ string header, for string ops below */
#include <string>
#include <iostream>
#include <memory>

#include "scanner.hpp"
#include "driver.hpp"

/* Implementation of yyFlexScanner */ 
#undef  YY_DECL
#define YY_DECL \
 int Scanner::lex(ps::Parser::value_type* lval)

using DOMAIN_TAG = ps::Parser::token;

#define yyterminate() return (DOMAIN_TAG::END)

Driver driver;


#define YY_USER_ACTION \
{ \
   driver.common(lval, yytext); \
}

%}

%option debug
%option nodefault
%option yyclass="Scanner"
%option noyywrap
%option c++

NUMBER [0-9]*
IDENT \_*[A-Za-z][\_A-Za-z0-9]*
TYPE int

NON_IDENT [^a-zA-Z\_0-9]

%%

{NUMBER} {
   lval->build< std::string >( yytext );
   return DOMAIN_TAG::TAG_NUMBER;
}


if/{NON_IDENT} {
   lval->build< std::string >( yytext );
   return DOMAIN_TAG::TAG_IF;
}

else/{NON_IDENT} {
   lval->build< std::string >( yytext );
   return DOMAIN_TAG::TAG_ELSE;
}

while/{NON_IDENT} {
   lval->build< std::string >( yytext );
   return DOMAIN_TAG::TAG_WHILE;
}

return/{NON_IDENT} {
   lval->build< std::string >( yytext );
   return DOMAIN_TAG::TAG_RETURN;
}

{TYPE}/{NON_IDENT} {
   lval->build< std::string >( yytext );
   return DOMAIN_TAG::TAG_TYPE;
}

{IDENT} {
   lval->build< std::string >( yytext );
   return DOMAIN_TAG::TAG_IDENT;
}

\( {
   lval->build< std::string >( yytext );
   return DOMAIN_TAG::TAG_LPAREN;
}

\) {
   lval->build< std::string >( yytext );
   return DOMAIN_TAG::TAG_RPAREN;
}

\{ {
   lval->build< std::string >( yytext );
   return DOMAIN_TAG::TAG_LFPAREN;
}

\} {
   lval->build< std::string >( yytext );
   return DOMAIN_TAG::TAG_RFPAREN;
}

\; {
   lval->build< std::string >( yytext );
   return DOMAIN_TAG::TAG_SEMICOLON;
}


\</[^=] {
   lval->build< std::string >( yytext );
   return DOMAIN_TAG::TAG_CMPOP;
}

\>/[^=] { 
   lval->build< std::string >( yytext );
   return DOMAIN_TAG::TAG_CMPOP; 
}

\<\= { 
   lval->build< std::string >( yytext );
   return DOMAIN_TAG::TAG_CMPOP; 
}

\>\= { 
   lval->build< std::string >( yytext );
   return DOMAIN_TAG::TAG_CMPOP; 
}

\=\= {
   lval->build< std::string >( yytext );
   return DOMAIN_TAG::TAG_CMPOP; 
}

\=/[^=] {
   lval->build< std::string >( yytext );
   return DOMAIN_TAG::TAG_EQUAL;
}

\* {
   lval->build< std::string >( yytext );
   return DOMAIN_TAG::TAG_MULT;
}
\/ {
   lval->build< std::string >( yytext );
   return DOMAIN_TAG::TAG_DIV;
}
\+ {
   lval->build< std::string >( yytext );
   return DOMAIN_TAG::TAG_PLUS;
}
\- {
   lval->build< std::string >( yytext );
   return DOMAIN_TAG::TAG_MINUS;
}

[ \t\r\n]+ {
}

. {
   throw std::runtime_error("error token!");
}

%%
