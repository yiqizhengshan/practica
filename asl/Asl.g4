//////////////////////////////////////////////////////////////////////
//
//    Asl - Another simple language (grammar)
//
//    Copyright (C) 2020-2030  Universitat Politecnica de Catalunya
//
//    This library is free software; you can redistribute it and/or
//    modify it under the terms of the GNU General Public License
//    as published by the Free Software Foundation; either version 3
//    of the License, or (at your option) any later version.
//
//    This library is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//    Affero General Public License for more details.
//
//    You should have received a copy of the GNU Affero General Public
//    License along with this library; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
//
//    contact: José Miguel Rivero (rivero@cs.upc.edu)
//             Computer Science Department
//             Universitat Politecnica de Catalunya
//             despatx Omega.110 - Campus Nord UPC
//             08034 Barcelona.  SPAIN
//
//////////////////////////////////////////////////////////////////////

grammar Asl;

//////////////////////////////////////////////////
/// Parser Rules
//////////////////////////////////////////////////

// A program is a list of functions
program : function+ EOF
        ;

// A function has a name, a list of parameters and a list of statements
function : FUNC ID '(' parameters ')' (':' type)? declarations statements ENDFUNC
        ;

parameters : (ID ':' type (',' ID ':' type)*)? ;

declarations
        : (variable_decl)*
        ;

variable_decl
        : VAR ID (',' ID)* ':' type
        ;

basic_type    
        : INT
        | FLOAT
        | BOOL
        | CHAR
        ;

type    : basic_type                                    # accessbasic
        | ARRAY LCLA INTVAL RCLA OF basic_type          # accessarray
        ;

statements
        : (statement)*
        ;

// The different types of instructions
statement
          // Assignment
        : left_expr ASSIGN expr ';'                             # assignStmt
          // if-then-else statement (else is optional)
        | IF expr THEN statements (ELSE statements)? ENDIF      # ifStmt
          // while-do-endwhile
        | WHILE expr DO statements ENDWHILE                     # whileStmt
          // A function/procedure call has a list of arguments in parenthesis (possibly empty)
        | call_to_func ';'                                      # procStmt
          // Read a variable
        | READ left_expr ';'                                    # readStmt
          // Write an expression
        | WRITE expr ';'                                        # writeExpr
          // Write a string
        | WRITE STRING ';'                                      # writeString
          // return
        | RETURN (expr)? ';'                                    # retStmt
        ;

// Grammar for left expressions (l-values in C++)
left_expr
        : ident LCLA expr RCLA                          # larray
        | ident                                         # lexprIdent
        ;

call_to_func
        : ident LPAR (expr (',' expr)*)? RPAR              # procCall
        ;

// Grammar for expressions with boolean, relational and aritmetic operators
expr    : LPAR expr RPAR                                # parent
        | call_to_func                                  # func
        | op=MINUS expr                                 # minus_unari 
        | expr op=(MUL|DIV) expr                        # arithmetic
        | expr op=(PLUS|MINUS) expr                     # arithmetic
        | expr op=(EQUAL|NEQ|GT|GE|LT|LE) expr          # relational
        | op=NOT expr                                   # logical_unari
        | expr op=AND expr                              # logical
        | expr op=OR expr                               # logical
        | INTVAL                                        # value
        | FLOATVAL                                      # value
        | CHARVAL                                       # value
        | (TRUE|FALSE)                                  # value
        | ident LCLA expr RCLA                          # array
        | ident                                         # exprIdent
        ;

// Identifiers
ident   : ID
        ;

//////////////////////////////////////////////////
/// Lexer Rules
//////////////////////////////////////////////////

TRUE      : 'true' ;
FALSE     : 'false' ;
ASSIGN    : '=' ;
EQUAL     : '==' ;
NEQ       : '!=' ;
GT        : '>' ;
GE        : '>=' ;
LT        : '<' ;
LE        : '<=' ;
NOT       : 'not' ;
AND       : 'and' ;
OR        : 'or' ;
PLUS      : '+' ;
MINUS     : '-' ;
MUL       : '*' ;
DIV       : '/' ;
VAR       : 'var' ;
INT       : 'int' ;
FLOAT     : 'float' ;
CHAR      : 'char' ;
BOOL      : 'bool' ;
IF        : 'if' ;
THEN      : 'then' ;
ELSE      : 'else' ;
ENDIF     : 'endif' ;
WHILE     : 'while' ;
DO        : 'do' ;
ENDWHILE  : 'endwhile' ;
RETURN    : 'return' ;
FUNC      : 'func' ;
ENDFUNC   : 'endfunc' ;
READ      : 'read' ;
WRITE     : 'write' ;
LPAR      : '(' ;
RPAR      : ')' ;
LCLA      : '[' ;
RCLA      : ']' ;
ARRAY     : 'array' ;
OF        : 'of' ;


ID        : ('a'..'z'|'A'..'Z') ('a'..'z'|'A'..'Z'|'_'|'0'..'9')* ;
INTVAL    : ('0'..'9')+ ;
FLOATVAL  : (('0'..'9')+ '.' ('0'..'9')* | ('0'..'9')* '.' ('0'..'9')+) ;
CHARVAL   : '\'' ( ESC_SEQ | ~('\\'|'"') )? '\'' ; 

// Strings (in quotes) with escape sequences
STRING    : '"' ( ESC_SEQ | ~('\\'|'"') )* '"' ;

fragment
ESC_SEQ   : '\\' ('b'|'t'|'n'|'f'|'r'|'"'|'\''|'\\') ;

// Comments (inline C++-style)
COMMENT   : '//' ~('\n'|'\r')* '\r'? '\n' -> skip ;

// White spaces
WS        : (' '|'\t'|'\r'|'\n')+ -> skip ;
