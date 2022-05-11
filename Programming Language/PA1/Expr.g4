grammar Expr;

// parser rules
prog : (expr ';'?NEWLINE?)*;
expr : '(' expr ')'         # parensExpr
     | expr ('*'|'/') expr  # infixExpr
     | expr ('+'|'-') expr  # infixExpr
     | num                  # numberExpr
     | '(' expr ')'         # parensExpr
     | ID '=' expr           # assignExpr 
     | MIN '(' expr ',' expr ')' #minExpr
     | MAX '(' expr ',' expr ')' #maxExpr
     | POW '(' expr ',' expr ')' #powExpr
     | SQRT '(' expr ')'        #sqrtExpr
     ;


num  : INT
     | REAL
     ;

// lexer rules
NEWLINE: [\r\n]+ ;
INT: [0-9]+ ;          // should handle negatives
REAL: [0-9]+'.'[0-9]* ; // should handle signs(+/-)
MIN: 'min' ;
MAX: 'max' ;
POW: 'pow' ;
SQRT: 'sqrt' ;
ID: [a-zA-Z]+ ;
WS: [ \t\r\n]+ -> skip ;
