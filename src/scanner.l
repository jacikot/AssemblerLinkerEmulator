%{ /* -*- C++ -*- */
# include <cerrno>
# include <climits>
# include <cstdlib>
# include <cstring> // strerror
# include <string>
# include "driver.h"
# include "parser.h"
%}

%option noyywrap nounput noinput batch debug

%{
  // A number symbol corresponding to the value in S.
  yy::parser::symbol_type
  make_NUMBER (const std::string &s, const yy::parser::location_type& loc);
%}

id    [a-zA-Z][a-zA-Z_0-9]*
int   [0-9]+
hex_int 0[xX][0-9a-fA-F]+
blank [ \t\r]
register r[0-7]
comment #[^\n]*

mnm0 (halt|iret|ret)
mnm1_op (call|jmp|jeq|jne|jgt)
mnm1_reg (int|push|pop|not)
mnm2_regreg (xchg|add|sub|mul|div|cmp|and|or|xor|test|shl|shr)
mnm2_regop (ldr|str)

%{
  // Code run each time a pattern is matched.
  # define YY_USER_ACTION  loc.columns (yyleng);
%}
%%
%{
  // A handy shortcut to the location held by the driver.
  yy::location& loc = drv.location;
  // Code run each time yylex is called.
  loc.step ();
%}
{blank}+   loc.step ();
\n+        loc.lines (yyleng); loc.step ();

"-"        return yy::parser::make_MINUS  (loc);
"+"        return yy::parser::make_PLUS   (loc);
"*"        return yy::parser::make_STAR   (loc);
"/"        return yy::parser::make_SLASH  (loc);
"("        return yy::parser::make_LPAREN (loc);
")"        return yy::parser::make_RPAREN (loc);
","        return yy::parser::make_COMMA  (loc);
":"        return yy::parser::make_COLON  (loc);
"$"        return yy::parser::make_DOLLAR (loc);
"%"        return yy::parser::make_PERCENT(loc);
"#"        return yy::parser::make_HASH   (loc);
"\n"       return yy::parser::make_NEWLINE(loc);

".global"  return yy::parser::make_GLOBAL (loc);
".extern"  return yy::parser::make_EXTERN (loc);
".section" return yy::parser::make_SECTION(loc);
".word"    return yy::parser::make_WORD   (loc);
".skip"    return yy::parser::make_SKIP   (loc);
".equ"     return yy::parser::make_EQU    (loc);
".end"     return yy::parser::make_END    (loc);

{register} return yy::parser::make_REG    (lyytext,oc);
"pc"       return yy::parser::make_REG_PC (loc);
"sp"       return yy::parser::make_REG_SP (loc);
"psw"      return yy::parser::make_REG_PSW(loc);

{mnm0}       return yy::parser::make_MNM0(yytext,loc);
{mnm1_op}    return yy::parser::make_MNM1OP(yytext,loc);
{mnm1_reg}   return yy::parser::make_MNM1REG(yytext,loc);
{mnm2_regop} return yy::parser::make_MNM2REGOP(yytext,loc);
{mnm2_regreg}return yy::parser::make_MNM2REGREG(yytext,loc);

{int}      return make_NUMBER (yytext, loc);
{hex_int}  return make_HEX (yytext, loc);
{comment}  return make_COMMENT (yytext, loc);

{id}       return yy::parser::make_SYMBOL (yytext, loc);
.          {
             throw yy::parser::syntax_error
               (loc, "invalid character: " + std::string(yytext));
}
<<EOF>>    return yy::parser::make_YYEOF (loc);
%%


//my make functions

yy::parser::symbol_type make_NUMBER (const std::string &s, const yy::parser::location_type& loc)
{
  errno = 0;
  long n = strtol (s.c_str(), NULL, 10);
  if (! (INT_MIN <= n && n <= INT_MAX && errno != ERANGE))
    throw yy::parser::syntax_error (loc, "integer is out of range: " + s);
  return yy::parser::make_NUMBER ((int) n, loc);
}

yy::parser::symbol_type make_HEX (const std::string &s, const yy::parser::location_type& loc)
{
  return yy::parser::make_HEX(std::stoi(s, nullptr, 16), loc);
}


void driver::scan_begin ()
{
  yy_flex_debug = trace_scanning;
  if (file.empty () || file == "-")
    yyin = stdin;
  else if (!(yyin = fopen (file.c_str (), "r")))
    {
      std::cerr << "cannot open " << file << ": " << strerror (errno) << '\n';
      exit (EXIT_FAILURE);
    }
}

void driver::scan_end ()
{
  fclose (yyin);
}