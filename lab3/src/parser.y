%skeleton "lalr1.cc"
%require  "3.0"

%define api.namespace { ps }
%define api.parser.class { Parser }


%code requires{
  #include <memory>
  #include "ast_tree.hpp"

  class Driver;
  class Scanner;
}


%parse-param{ Scanner & scanner }
%parse-param{ Driver & driver }



%code{
  #include <iostream>
  #include <string>

  /* include for all driver functions */
  #include "scanner.hpp"
  #include "driver.hpp"

  #undef yylex
  #define yylex scanner.lex
}

%define api.value.type variant

%token END 0

%token <std::string>
TAG_IDENT
TAG_TYPE
TAG_NUMBER

TAG_IF
TAG_ELSE
TAG_WHILE
TAG_RETURN
TAG_LPAREN
TAG_RPAREN
TAG_SEMICOLON
TAG_EQUAL
TAG_CMPOP
TAG_MULT
TAG_DIV
TAG_PLUS
TAG_MINUS
TAG_LFPAREN
TAG_RFPAREN
;

%nterm <std::string>
Type
;

%nterm < std::vector<std::unique_ptr<StatementAST>> >
Block
Statements
IfStElse
;

%nterm < std::unique_ptr<StatementAST> >
Statement
ReturnSt
Assign
ReAssign
;

%nterm < std::unique_ptr<IfSt> >
IfSt
;

%nterm < std::unique_ptr<WhileSt> >
WhileSt
;



%nterm < std::unique_ptr<ExprAST> >
ArithExpr
T1
T2
LogicExpr
;

%nterm < std::unique_ptr<std::pair<std::string, std::unique_ptr<ExprAST>>> >
T1Tail
T2Tail
;

%nterm <std::string>
T1Op
T2Op
;

%%
%start Function;

Function:
Type TAG_IDENT TAG_LPAREN TAG_RPAREN Block {
  driver.rootAST = std::make_unique<FunctionAST>($1, $2, std::move($5)); 
}
;

Type:
TAG_TYPE {
  $$ = $1;
}
;

Block:
TAG_LFPAREN Statements TAG_RFPAREN {
  $$ = std::move($2);
}
;


Statements:
Statement Statements {
  auto vec = std::move($2);
  vec.insert(vec.begin(), std::move($1));
  $$ = std::move(vec);
}
| %empty {
  $$ = std::vector<std::unique_ptr<StatementAST>>();
}
;

Statement:
Assign TAG_SEMICOLON {
  $$ = std::move($1);
}
| ReAssign TAG_SEMICOLON {
  $$ = std::move($1);
}
| ReturnSt TAG_SEMICOLON {
  $$ = std::move($1);
}
| IfSt {
  $$ = std::move($1);
} 
| WhileSt {
  $$ = std::move($1);
}
;

Assign:
Type TAG_IDENT {
  $$ = std::make_unique<AssignSt>($1, $2);
}
;

ReAssign:
TAG_IDENT TAG_EQUAL ArithExpr {
  $$ = std::make_unique<ReAssignSt>($1, std::move($3));
}
;

ReturnSt:
TAG_RETURN ArithExpr {
  $$ = std::make_unique<ReturnSt>(std::move($2));
}
;

/* if */

IfSt:
TAG_IF TAG_LPAREN LogicExpr TAG_RPAREN Block IfStElse {
  $$ = std::make_unique<IfSt>(std::move($3), std::move($5), std::move($6));
}
;

IfStElse:
TAG_ELSE Block {
  $$ = std::move($2);
}
| %empty {
  $$ = std::move(std::vector<std::unique_ptr<StatementAST>>());
}
;

WhileSt:
TAG_WHILE TAG_LPAREN LogicExpr TAG_RPAREN Block {
  $$ = std::make_unique<WhileSt>(std::move($3), std::move($5));
}
;


/* LogicExpr */

LogicExpr:
ArithExpr TAG_CMPOP ArithExpr {
  $$ = std::make_unique<BinaryExprAST>($2, std::move($1), std::move($3));
}
;

/* ================ ArithExpr ===============*/

ArithExpr:
T1 T1Tail {
  if ($2) {
    $$ = std::make_unique<BinaryExprAST>($2->first, std::move($1), std::move($2->second));
  } else {
    $$ = std::move($1);
  }
}
;

T1Tail:
T1Op T1 T1Tail {
  std::unique_ptr<ExprAST> binexp;
  if ($3) {
    binexp = std::make_unique<BinaryExprAST>($3->first, std::move($2), std::move($3->second));
  } else {
    binexp = std::move($2);
  }
  $$ = std::make_unique<std::pair<std::string, std::unique_ptr<ExprAST>>>($1, std::move(binexp));
}
| %empty {
  $$ = nullptr;
}
;

T1Op:
TAG_PLUS {
  $$ = $1;
}
| TAG_MINUS {
  $$ = $1;
}
;


T1:
T2 T2Tail {
  if ($2) {
    $$ = std::make_unique<BinaryExprAST>($2->first, std::move($1), std::move($2->second));
  } else {
    $$ = std::move($1);
  }
}
;

T2Tail:
T2Op T2 T2Tail {
  std::unique_ptr<ExprAST> binexp;
  if ($3) {
    binexp = std::make_unique<BinaryExprAST>($3->first, std::move($2), std::move($3->second));
  } else {
    binexp = std::move($2);
  }
  $$ = std::make_unique<std::pair<std::string, std::unique_ptr<ExprAST>>>($1, std::move(binexp));
}
| %empty {
  $$ = nullptr;
}
;

T2Op:
TAG_MULT {
  $$ = $1;
}
| TAG_DIV {
  $$ = $1;
}
;

T2:
TAG_IDENT {
  $$ = std::make_unique<VariableExprAST>($1);
}
| TAG_NUMBER {
  $$ = std::make_unique<NumberExprAST>(stoi($1));
}
| TAG_LPAREN ArithExpr TAG_RPAREN {
  $$ = std::move($2);
}

%%


void ps::Parser::error(const std::string& err_message)
{
  std::cerr << "Error: " << err_message;
}
