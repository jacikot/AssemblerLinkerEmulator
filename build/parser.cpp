// A Bison parser, made by GNU Bison 3.5.1.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2020 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// Undocumented macros, especially those whose name start with YY_,
// are private implementation details.  Do not rely on them.





#include "parser.h"


// Unqualified %code blocks.
#line 19 "../src/parser.y"

# include "../h/driver.h"

#line 49 "parser.cpp"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

namespace yy {
#line 140 "parser.cpp"


  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              else
                goto append;

            append:
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
  parser::parser (Driver& drv_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      drv (drv_yyarg)
  {}

  parser::~parser ()
  {}

  parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  parser::symbol_number_type
  parser::by_state::type_get () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[+state];
  }

  parser::stack_symbol_type::stack_symbol_type ()
  {}

  parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 24: // NUMBER
      case 25: // HEX
      case 41: // literal
        value.YY_MOVE_OR_COPY< int > (YY_MOVE (that.value));
        break;

      case 22: // REG
      case 23: // SYMBOL
      case 26: // MNM0
      case 27: // MNM1OP
      case 28: // MNM1REG
      case 29: // MNM2REGOP
      case 30: // MNM2REGREG
      case 31: // COMMENT
      case 34: // lines
      case 36: // label
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      case 39: // symbols
      case 40: // initializers
        value.YY_MOVE_OR_COPY< std::vector<tokens::Initializer> > (YY_MOVE (that.value));
        break;

      case 38: // directive
        value.YY_MOVE_OR_COPY< tokens::Directive* > (YY_MOVE (that.value));
        break;

      case 37: // expression
        value.YY_MOVE_OR_COPY< tokens::Expression* > (YY_MOVE (that.value));
        break;

      case 42: // instruction
        value.YY_MOVE_OR_COPY< tokens::Instruction* > (YY_MOVE (that.value));
        break;

      case 35: // line
        value.YY_MOVE_OR_COPY< tokens::Line > (YY_MOVE (that.value));
        break;

      case 43: // operand_jmp
      case 44: // operand
        value.YY_MOVE_OR_COPY< tokens::Operand > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 24: // NUMBER
      case 25: // HEX
      case 41: // literal
        value.move< int > (YY_MOVE (that.value));
        break;

      case 22: // REG
      case 23: // SYMBOL
      case 26: // MNM0
      case 27: // MNM1OP
      case 28: // MNM1REG
      case 29: // MNM2REGOP
      case 30: // MNM2REGREG
      case 31: // COMMENT
      case 34: // lines
      case 36: // label
        value.move< std::string > (YY_MOVE (that.value));
        break;

      case 39: // symbols
      case 40: // initializers
        value.move< std::vector<tokens::Initializer> > (YY_MOVE (that.value));
        break;

      case 38: // directive
        value.move< tokens::Directive* > (YY_MOVE (that.value));
        break;

      case 37: // expression
        value.move< tokens::Expression* > (YY_MOVE (that.value));
        break;

      case 42: // instruction
        value.move< tokens::Instruction* > (YY_MOVE (that.value));
        break;

      case 35: // line
        value.move< tokens::Line > (YY_MOVE (that.value));
        break;

      case 43: // operand_jmp
      case 44: // operand
        value.move< tokens::Operand > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

#if YY_CPLUSPLUS < 201103L
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 24: // NUMBER
      case 25: // HEX
      case 41: // literal
        value.copy< int > (that.value);
        break;

      case 22: // REG
      case 23: // SYMBOL
      case 26: // MNM0
      case 27: // MNM1OP
      case 28: // MNM1REG
      case 29: // MNM2REGOP
      case 30: // MNM2REGREG
      case 31: // COMMENT
      case 34: // lines
      case 36: // label
        value.copy< std::string > (that.value);
        break;

      case 39: // symbols
      case 40: // initializers
        value.copy< std::vector<tokens::Initializer> > (that.value);
        break;

      case 38: // directive
        value.copy< tokens::Directive* > (that.value);
        break;

      case 37: // expression
        value.copy< tokens::Expression* > (that.value);
        break;

      case 42: // instruction
        value.copy< tokens::Instruction* > (that.value);
        break;

      case 35: // line
        value.copy< tokens::Line > (that.value);
        break;

      case 43: // operand_jmp
      case 44: // operand
        value.copy< tokens::Operand > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 24: // NUMBER
      case 25: // HEX
      case 41: // literal
        value.move< int > (that.value);
        break;

      case 22: // REG
      case 23: // SYMBOL
      case 26: // MNM0
      case 27: // MNM1OP
      case 28: // MNM1REG
      case 29: // MNM2REGOP
      case 30: // MNM2REGREG
      case 31: // COMMENT
      case 34: // lines
      case 36: // label
        value.move< std::string > (that.value);
        break;

      case 39: // symbols
      case 40: // initializers
        value.move< std::vector<tokens::Initializer> > (that.value);
        break;

      case 38: // directive
        value.move< tokens::Directive* > (that.value);
        break;

      case 37: // expression
        value.move< tokens::Expression* > (that.value);
        break;

      case 42: // instruction
        value.move< tokens::Instruction* > (that.value);
        break;

      case 35: // line
        value.move< tokens::Line > (that.value);
        break;

      case 43: // operand_jmp
      case 44: // operand
        value.move< tokens::Operand > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
#if defined __GNUC__ && ! defined __clang__ && ! defined __ICC && __GNUC__ * 100 + __GNUC_MINOR__ <= 408
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
#endif
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  void
  parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  parser::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  bool
  parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::operator() ()
  {
    return parse ();
  }

  int
  parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex (drv));
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case 24: // NUMBER
      case 25: // HEX
      case 41: // literal
        yylhs.value.emplace< int > ();
        break;

      case 22: // REG
      case 23: // SYMBOL
      case 26: // MNM0
      case 27: // MNM1OP
      case 28: // MNM1REG
      case 29: // MNM2REGOP
      case 30: // MNM2REGREG
      case 31: // COMMENT
      case 34: // lines
      case 36: // label
        yylhs.value.emplace< std::string > ();
        break;

      case 39: // symbols
      case 40: // initializers
        yylhs.value.emplace< std::vector<tokens::Initializer> > ();
        break;

      case 38: // directive
        yylhs.value.emplace< tokens::Directive* > ();
        break;

      case 37: // expression
        yylhs.value.emplace< tokens::Expression* > ();
        break;

      case 42: // instruction
        yylhs.value.emplace< tokens::Instruction* > ();
        break;

      case 35: // line
        yylhs.value.emplace< tokens::Line > ();
        break;

      case 43: // operand_jmp
      case 44: // operand
        yylhs.value.emplace< tokens::Operand > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2:
#line 84 "../src/parser.y"
          {}
#line 792 "parser.cpp"
    break;

  case 3:
#line 88 "../src/parser.y"
           {}
#line 798 "parser.cpp"
    break;

  case 4:
#line 89 "../src/parser.y"
               {
        drv.assembler.addLine(yystack_[0].value.as < tokens::Line > ());
    }
#line 806 "parser.cpp"
    break;

  case 5:
#line 92 "../src/parser.y"
                  {}
#line 812 "parser.cpp"
    break;

  case 6:
#line 97 "../src/parser.y"
           {}
#line 818 "parser.cpp"
    break;

  case 7:
#line 98 "../src/parser.y"
               {
        yylhs.value.as < tokens::Line > ()=yystack_[0].value.as < tokens::Line > ();
    }
#line 826 "parser.cpp"
    break;

  case 8:
#line 101 "../src/parser.y"
               {
        yylhs.value.as < tokens::Line > ()=tokens::Line();
        yylhs.value.as < tokens::Line > ().exp=yystack_[0].value.as < tokens::Expression* > ();
    }
#line 835 "parser.cpp"
    break;

  case 9:
#line 108 "../src/parser.y"
               {
        drv.assembler.addSymbol(yystack_[1].value.as < std::string > ());
    }
#line 843 "parser.cpp"
    break;

  case 10:
#line 114 "../src/parser.y"
              {
        yylhs.value.as < tokens::Expression* > ()=yystack_[0].value.as < tokens::Directive* > ();
    }
#line 851 "parser.cpp"
    break;

  case 11:
#line 117 "../src/parser.y"
                {
        yylhs.value.as < tokens::Expression* > ()=yystack_[0].value.as < tokens::Instruction* > ();
    }
#line 859 "parser.cpp"
    break;

  case 12:
#line 123 "../src/parser.y"
                   {
        yylhs.value.as < tokens::Directive* > ()=new tokens::Directive();
        yylhs.value.as < tokens::Directive* > ()->symbols=yystack_[0].value.as < std::vector<tokens::Initializer> > ();
        yylhs.value.as < tokens::Directive* > ()->type=tokens::DirType::GLOBAL;
    }
#line 869 "parser.cpp"
    break;

  case 13:
#line 128 "../src/parser.y"
                   {
        yylhs.value.as < tokens::Directive* > ()=new tokens::Directive();
        yylhs.value.as < tokens::Directive* > ()->symbols=yystack_[0].value.as < std::vector<tokens::Initializer> > ();
        yylhs.value.as < tokens::Directive* > ()->type=tokens::DirType::EXTERN;
        for (tokens::Initializer i:yystack_[0].value.as < std::vector<tokens::Initializer> > ()){
            drv.assembler.addUndefinedSymbol(i.name);
        }
    }
#line 882 "parser.cpp"
    break;

  case 14:
#line 136 "../src/parser.y"
                   {
        yylhs.value.as < tokens::Directive* > ()=new tokens::Directive();
        tokens::Initializer ini;
        ini.symbol=true;
        ini.name=yystack_[0].value.as < std::string > ();
        yylhs.value.as < tokens::Directive* > ()->symbols.push_back(ini);
        yylhs.value.as < tokens::Directive* > ()->type=tokens::DirType::SECTION;
        drv.assembler.addSection(yystack_[0].value.as < std::string > ());
    }
#line 896 "parser.cpp"
    break;

  case 15:
#line 145 "../src/parser.y"
                      {
        yylhs.value.as < tokens::Directive* > ()=new tokens::Directive();
        yylhs.value.as < tokens::Directive* > ()->symbols=yystack_[0].value.as < std::vector<tokens::Initializer> > ();
        yylhs.value.as < tokens::Directive* > ()->type=tokens::DirType::WORD;
        drv.assembler.addToCounter(yylhs.value.as < tokens::Directive* > ()->symbols.size()*2);
    }
#line 907 "parser.cpp"
    break;

  case 16:
#line 151 "../src/parser.y"
                 {
        yylhs.value.as < tokens::Directive* > ()=new tokens::Directive();
        tokens::Initializer ini;
        ini.symbol=false;
        ini.value=yystack_[0].value.as < int > ();
        yylhs.value.as < tokens::Directive* > ()->symbols.push_back(ini);
        yylhs.value.as < tokens::Directive* > ()->type=tokens::DirType::SKIP;
        drv.assembler.addToCounter(yystack_[0].value.as < int > ());
    }
#line 921 "parser.cpp"
    break;

  case 17:
#line 160 "../src/parser.y"
                           {
        yylhs.value.as < tokens::Directive* > ()=new tokens::Directive();
        tokens::Initializer ini;
        ini.symbol=false;
        ini.value=yystack_[0].value.as < int > ();
        yylhs.value.as < tokens::Directive* > ()->symbols.push_back(ini);
        yylhs.value.as < tokens::Directive* > ()->type=tokens::DirType::EQU;
        yylhs.value.as < tokens::Directive* > ()->toInitialize=yystack_[2].value.as < std::string > ();
        drv.assembler.addAbsoluteSymbol(yystack_[2].value.as < std::string > (),yystack_[0].value.as < int > ());
    }
#line 936 "parser.cpp"
    break;

  case 18:
#line 173 "../src/parser.y"
           {
        tokens::Initializer ini;        
        ini.symbol=true;
        ini.name=yystack_[0].value.as < std::string > ();
        yylhs.value.as < std::vector<tokens::Initializer> > ()=std::vector<tokens::Initializer>();
        yylhs.value.as < std::vector<tokens::Initializer> > ().push_back(ini);
    }
#line 948 "parser.cpp"
    break;

  case 19:
#line 180 "../src/parser.y"
                      {
        yylhs.value.as < std::vector<tokens::Initializer> > ()=yystack_[2].value.as < std::vector<tokens::Initializer> > ();
        tokens::Initializer ini;
        ini.symbol=true;
        ini.name=yystack_[0].value.as < std::string > ();
        yylhs.value.as < std::vector<tokens::Initializer> > ().push_back(ini);
    }
#line 960 "parser.cpp"
    break;

  case 20:
#line 191 "../src/parser.y"
                            {
        tokens::Initializer ini;
        ini.symbol=true;
        ini.name=yystack_[0].value.as < std::string > ();
        yylhs.value.as < std::vector<tokens::Initializer> > ()=yystack_[2].value.as < std::vector<tokens::Initializer> > ();
        yylhs.value.as < std::vector<tokens::Initializer> > ().push_back(ini);
    }
#line 972 "parser.cpp"
    break;

  case 21:
#line 198 "../src/parser.y"
                             {
        tokens::Initializer ini;
        ini.symbol=false;
        ini.value=yystack_[0].value.as < int > ();
        yylhs.value.as < std::vector<tokens::Initializer> > ()=yystack_[2].value.as < std::vector<tokens::Initializer> > ();
        yylhs.value.as < std::vector<tokens::Initializer> > ().push_back(ini);
    }
#line 984 "parser.cpp"
    break;

  case 22:
#line 205 "../src/parser.y"
            {
        tokens::Initializer ini;
        ini.symbol=false;
        ini.value=yystack_[0].value.as < int > ();
        yylhs.value.as < std::vector<tokens::Initializer> > ()=std::vector<tokens::Initializer>();
        yylhs.value.as < std::vector<tokens::Initializer> > ().push_back(ini);
    }
#line 996 "parser.cpp"
    break;

  case 23:
#line 212 "../src/parser.y"
           {
        tokens::Initializer ini;
        ini.symbol=true;
        ini.name=yystack_[0].value.as < std::string > ();
        yylhs.value.as < std::vector<tokens::Initializer> > ()=std::vector<tokens::Initializer>();
        yylhs.value.as < std::vector<tokens::Initializer> > ().push_back(ini);
    }
#line 1008 "parser.cpp"
    break;

  case 24:
#line 222 "../src/parser.y"
           {
        yylhs.value.as < int > ()=yystack_[0].value.as < int > ();
    }
#line 1016 "parser.cpp"
    break;

  case 25:
#line 225 "../src/parser.y"
               {
        yylhs.value.as < int > ()=-yystack_[0].value.as < int > ();
    }
#line 1024 "parser.cpp"
    break;

  case 26:
#line 228 "../src/parser.y"
        {
        yylhs.value.as < int > ()=yystack_[0].value.as < int > ();
    }
#line 1032 "parser.cpp"
    break;

  case 27:
#line 231 "../src/parser.y"
            {
        yylhs.value.as < int > ()=-yystack_[0].value.as < int > ();
    }
#line 1040 "parser.cpp"
    break;

  case 28:
#line 236 "../src/parser.y"
         {
        tokens::Instr0* inst=new tokens::Instr0();
        inst->mnemonic=yystack_[0].value.as < std::string > ();
        yylhs.value.as < tokens::Instruction* > ()=inst;
        drv.assembler.addToCounter(1); //1B instr
    }
#line 1051 "parser.cpp"
    break;

  case 29:
#line 242 "../src/parser.y"
                       {
        tokens::Instr1_op*inst=new tokens::Instr1_op();
        inst->mnemonic=yystack_[1].value.as < std::string > ();
        inst->operand=yystack_[0].value.as < tokens::Operand > ();
        yylhs.value.as < tokens::Instruction* > ()=inst;
    }
#line 1062 "parser.cpp"
    break;

  case 30:
#line 248 "../src/parser.y"
                {
        if(yystack_[1].value.as < std::string > ()=="push"||yystack_[1].value.as < std::string > ()=="pop"){
            tokens::Instr2_regop*inst=new tokens::Instr2_regop();
            inst->mnemonic=yystack_[1].value.as < std::string > ();
            inst->reg=yystack_[0].value.as < std::string > ();
            tokens::Operand op;
            op.adr=tokens::Addressing::REGIND;
            op.reg="sp";
            if(yystack_[1].value.as < std::string > ()=="push")op.addend=0b0001;
            else op.addend=0b0100;
            inst->operand=op; 
            drv.assembler.addToCounter(3);
            yylhs.value.as < tokens::Instruction* > ()=inst;
        }
        else{
            tokens::Instr1_reg*inst=new tokens::Instr1_reg();
            inst->mnemonic=yystack_[1].value.as < std::string > ();
            inst->reg=yystack_[0].value.as < std::string > ();
            yylhs.value.as < tokens::Instruction* > ()=inst;
            drv.assembler.addToCounter(2);
        }
    }
#line 1089 "parser.cpp"
    break;

  case 31:
#line 270 "../src/parser.y"
                              {
        tokens::Instr2_regop*inst=new tokens::Instr2_regop();
        inst->mnemonic=yystack_[3].value.as < std::string > ();
        inst->reg=yystack_[2].value.as < std::string > ();
        inst->operand=yystack_[0].value.as < tokens::Operand > ();
        yylhs.value.as < tokens::Instruction* > ()=inst;
    }
#line 1101 "parser.cpp"
    break;

  case 32:
#line 277 "../src/parser.y"
                          {
        tokens::Instr2_regreg*inst=new tokens::Instr2_regreg();
        inst->mnemonic=yystack_[3].value.as < std::string > ();
        inst->regDST=yystack_[2].value.as < std::string > ();
        inst->regSRC=yystack_[0].value.as < std::string > ();
        yylhs.value.as < tokens::Instruction* > ()=inst;
        drv.assembler.addToCounter(2);
    }
#line 1114 "parser.cpp"
    break;

  case 33:
#line 288 "../src/parser.y"
            {
        tokens::Initializer ini;
        ini.symbol=false;
        ini.value=yystack_[0].value.as < int > ();
        yylhs.value.as < tokens::Operand > ()=tokens::Operand();
        yylhs.value.as < tokens::Operand > ().adr=tokens::Addressing::IMMED;
        yylhs.value.as < tokens::Operand > ().ini=ini;
        drv.assembler.addToCounter(5); //5B instr
    }
#line 1128 "parser.cpp"
    break;

  case 34:
#line 297 "../src/parser.y"
           {
        tokens::Initializer ini;
        ini.symbol=true;
        ini.name=yystack_[0].value.as < std::string > ();
        yylhs.value.as < tokens::Operand > ()=tokens::Operand();
        yylhs.value.as < tokens::Operand > ().adr=tokens::Addressing::IMMED;
        yylhs.value.as < tokens::Operand > ().ini=ini;
        drv.assembler.addToCounter(5); //5B instr
    }
#line 1142 "parser.cpp"
    break;

  case 35:
#line 306 "../src/parser.y"
              {
        tokens::Initializer ini;
        ini.symbol=true;
        ini.name=yystack_[0].value.as < std::string > ();
        yylhs.value.as < tokens::Operand > ()=tokens::Operand();
        yylhs.value.as < tokens::Operand > ().adr=tokens::Addressing::REGDIRPOM; //value not from memory pcrel - regdirpom
        yylhs.value.as < tokens::Operand > ().ini=ini;
        yylhs.value.as < tokens::Operand > ().reg="pc";
        yylhs.value.as < tokens::Operand > ().isPCREL=true;
        drv.assembler.addToCounter(5); //5B instr
    }
#line 1158 "parser.cpp"
    break;

  case 36:
#line 317 "../src/parser.y"
                {
        tokens::Initializer ini;
        ini.symbol=false;
        ini.value=yystack_[0].value.as < int > ();
        yylhs.value.as < tokens::Operand > ()=tokens::Operand();
        yylhs.value.as < tokens::Operand > ().adr=tokens::Addressing::MEMDIR;
        yylhs.value.as < tokens::Operand > ().ini=ini;
        drv.assembler.addToCounter(5); //5B instr
    }
#line 1172 "parser.cpp"
    break;

  case 37:
#line 326 "../src/parser.y"
               {
        tokens::Initializer ini;
        ini.symbol=true;
        ini.name=yystack_[0].value.as < std::string > ();
        yylhs.value.as < tokens::Operand > ()=tokens::Operand();
        yylhs.value.as < tokens::Operand > ().adr=tokens::Addressing::MEMDIR;
        yylhs.value.as < tokens::Operand > ().ini=ini;
        drv.assembler.addToCounter(5); //5B instr
    }
#line 1186 "parser.cpp"
    break;

  case 38:
#line 335 "../src/parser.y"
            {
        yylhs.value.as < tokens::Operand > ()=tokens::Operand();
        yylhs.value.as < tokens::Operand > ().adr=tokens::Addressing::REGDIR;
        yylhs.value.as < tokens::Operand > ().reg=yystack_[0].value.as < std::string > ();
        drv.assembler.addToCounter(3); //3B instr
    }
#line 1197 "parser.cpp"
    break;

  case 39:
#line 341 "../src/parser.y"
                    {
        yylhs.value.as < tokens::Operand > ()=tokens::Operand();
        yylhs.value.as < tokens::Operand > ().adr=tokens::Addressing::REGIND;
        yylhs.value.as < tokens::Operand > ().reg=yystack_[1].value.as < std::string > ();
        drv.assembler.addToCounter(3); //3B instr
    }
#line 1208 "parser.cpp"
    break;

  case 40:
#line 347 "../src/parser.y"
                                {
        tokens::Initializer ini;
        ini.symbol=false;
        ini.value=yystack_[1].value.as < int > ();
        yylhs.value.as < tokens::Operand > ()=tokens::Operand();
        yylhs.value.as < tokens::Operand > ().adr=tokens::Addressing::REGINDPOM;
        yylhs.value.as < tokens::Operand > ().ini=ini;
        yylhs.value.as < tokens::Operand > ().reg=yystack_[3].value.as < std::string > ();
        drv.assembler.addToCounter(5); //5B instr
    }
#line 1223 "parser.cpp"
    break;

  case 41:
#line 357 "../src/parser.y"
                               {
        tokens::Initializer ini;
        ini.symbol=true;
        ini.name=yystack_[1].value.as < std::string > ();
        yylhs.value.as < tokens::Operand > ()=tokens::Operand();
        yylhs.value.as < tokens::Operand > ().adr=tokens::Addressing::REGINDPOM;
        yylhs.value.as < tokens::Operand > ().ini=ini;
        yylhs.value.as < tokens::Operand > ().reg=yystack_[3].value.as < std::string > ();
        drv.assembler.addToCounter(5); //5B instr
    }
#line 1238 "parser.cpp"
    break;

  case 42:
#line 371 "../src/parser.y"
                {
        tokens::Initializer ini;
        ini.symbol=false;
        ini.value=yystack_[0].value.as < int > ();
        yylhs.value.as < tokens::Operand > ()=tokens::Operand();
        yylhs.value.as < tokens::Operand > ().adr=tokens::Addressing::IMMED;
        yylhs.value.as < tokens::Operand > ().ini=ini;
        drv.assembler.addToCounter(5); //5B instr
    }
#line 1252 "parser.cpp"
    break;

  case 43:
#line 380 "../src/parser.y"
               {
        tokens::Initializer ini;
        ini.symbol=true;
        ini.name=yystack_[0].value.as < std::string > ();
        yylhs.value.as < tokens::Operand > ()=tokens::Operand();
        yylhs.value.as < tokens::Operand > ().adr=tokens::Addressing::IMMED;
        yylhs.value.as < tokens::Operand > ().ini=ini;
        drv.assembler.addToCounter(5); //5B instr

    }
#line 1267 "parser.cpp"
    break;

  case 44:
#line 390 "../src/parser.y"
              {
        tokens::Initializer ini;
        ini.symbol=true;
        ini.name=yystack_[0].value.as < std::string > ();
        yylhs.value.as < tokens::Operand > ()=tokens::Operand();
        yylhs.value.as < tokens::Operand > ().adr=tokens::Addressing::REGINDPOM; //value from memory pcrel - regindpom
        yylhs.value.as < tokens::Operand > ().ini=ini;
        yylhs.value.as < tokens::Operand > ().reg="pc";
        yylhs.value.as < tokens::Operand > ().isPCREL=true;
        drv.assembler.addToCounter(5); //5B instr
    }
#line 1283 "parser.cpp"
    break;

  case 45:
#line 401 "../src/parser.y"
            {
        tokens::Initializer ini;
        ini.symbol=false;
        ini.value=yystack_[0].value.as < int > ();
        yylhs.value.as < tokens::Operand > ()=tokens::Operand();
        yylhs.value.as < tokens::Operand > ().adr=tokens::Addressing::MEMDIR;
        yylhs.value.as < tokens::Operand > ().ini=ini;
        drv.assembler.addToCounter(5); //5B instr
    }
#line 1297 "parser.cpp"
    break;

  case 46:
#line 410 "../src/parser.y"
           {
        tokens::Initializer ini;
        ini.symbol=true;
        ini.name=yystack_[0].value.as < std::string > ();
        yylhs.value.as < tokens::Operand > ()=tokens::Operand();
        yylhs.value.as < tokens::Operand > ().adr=tokens::Addressing::MEMDIR;
        yylhs.value.as < tokens::Operand > ().ini=ini;
        drv.assembler.addToCounter(5); //5B instr
    }
#line 1311 "parser.cpp"
    break;

  case 47:
#line 419 "../src/parser.y"
        {
        yylhs.value.as < tokens::Operand > ()=tokens::Operand();
        yylhs.value.as < tokens::Operand > ().adr=tokens::Addressing::REGDIR;
        yylhs.value.as < tokens::Operand > ().reg=yystack_[0].value.as < std::string > ();
        drv.assembler.addToCounter(3); //3B instr
    }
#line 1322 "parser.cpp"
    break;

  case 48:
#line 425 "../src/parser.y"
                {
        yylhs.value.as < tokens::Operand > ()=tokens::Operand();
        yylhs.value.as < tokens::Operand > ().adr=tokens::Addressing::REGIND;
        yylhs.value.as < tokens::Operand > ().reg=yystack_[1].value.as < std::string > ();
        drv.assembler.addToCounter(3); //3B instr
    }
#line 1333 "parser.cpp"
    break;

  case 49:
#line 431 "../src/parser.y"
                            {
        tokens::Initializer ini;
        ini.symbol=false;
        ini.value=yystack_[1].value.as < int > ();
        yylhs.value.as < tokens::Operand > ()=tokens::Operand();
        yylhs.value.as < tokens::Operand > ().adr=tokens::Addressing::REGINDPOM;
        yylhs.value.as < tokens::Operand > ().ini=ini;
        yylhs.value.as < tokens::Operand > ().reg=yystack_[3].value.as < std::string > ();
        drv.assembler.addToCounter(5); //5B instr
    }
#line 1348 "parser.cpp"
    break;

  case 50:
#line 441 "../src/parser.y"
                           {
        tokens::Initializer ini;
        ini.symbol=true;
        ini.name=yystack_[1].value.as < std::string > ();
        yylhs.value.as < tokens::Operand > ()=tokens::Operand();
        yylhs.value.as < tokens::Operand > ().adr=tokens::Addressing::REGINDPOM;
        yylhs.value.as < tokens::Operand > ().ini=ini;
        yylhs.value.as < tokens::Operand > ().reg=yystack_[3].value.as < std::string > ();
        drv.assembler.addToCounter(5); //5B instr
    }
#line 1363 "parser.cpp"
    break;


#line 1367 "parser.cpp"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[+yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yy_error_token_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yy_error_token_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  // Generate an error message.
  std::string
  parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    std::ptrdiff_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */
    if (!yyla.empty ())
      {
        symbol_number_type yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];

        int yyn = yypact_[+yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yy_error_token_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char parser::yypact_ninf_ = -23;

  const signed char parser::yytable_ninf_ = -1;

  const signed char
  parser::yypact_[] =
  {
     -23,     5,    57,   -23,   -17,   -17,   -15,    13,    23,   -13,
      29,   -23,     9,    -5,    -4,    21,   -23,   -23,    73,   -23,
     -23,   -23,   -23,    33,    33,   -23,   -22,   -23,   -23,   -23,
      38,   -23,   -23,    40,   -23,     6,    30,   -23,   -23,   -23,
     -23,    49,    68,   -23,    36,   -23,   -23,    32,    23,    46,
     -23,   -23,   -23,   -23,    -2,    59,   -23,   -23,   -23,   -23,
      15,    60,    39,    72,   -23,   -23,   -23,   -23,   -23,    42,
     -23,    48,   -23,   -23,   -23,    87,    88,    47,   -23,   -23,
     -23,    94,    95,   -23,   -23
  };

  const signed char
  parser::yydefact_[] =
  {
       3,     0,     2,     1,     0,     0,     0,     0,     0,     0,
       0,    28,     0,     0,     0,     0,     5,     4,     6,     8,
      10,    11,    18,    12,    13,    14,     0,    23,    24,    26,
      15,    22,    16,     0,     9,     0,     0,    34,    33,    29,
      30,     0,     0,     7,     0,    25,    27,     0,     0,     0,
      38,    37,    36,    35,     0,     0,    19,    20,    21,    17,
       0,     0,     0,     0,    47,    46,    45,    31,    32,     0,
      39,     0,    43,    42,    44,     0,     0,     0,    48,    41,
      40,     0,     0,    50,    49
  };

  const signed char
  parser::yypgoto_[] =
  {
     -23,   -23,   -23,    89,   -23,   -23,   -23,   101,   -23,    -8,
     -23,   -23,   -23
  };

  const signed char
  parser::yydefgoto_[] =
  {
      -1,     1,     2,    17,    18,    19,    20,    23,    30,    31,
      21,    39,    67
  };

  const signed char
  parser::yytable_[] =
  {
      32,    26,    45,    46,    38,     3,    22,    61,    25,    26,
      33,    62,    26,    63,    35,    49,    26,    40,    41,    69,
      64,    65,    28,    29,    36,    70,    26,    52,    50,    51,
      28,    29,    37,    28,    29,    26,    27,    28,    29,    58,
      59,    34,    26,    42,    44,    26,    66,    28,    29,    47,
      26,    48,    77,    53,    73,    57,    28,    29,    78,    56,
      54,    76,    72,    28,    29,    75,    28,    29,    60,    82,
      81,    28,    29,     4,     5,     6,     7,     8,     9,    55,
      10,    68,    71,    11,    12,    13,    14,    15,    16,     4,
       5,     6,     7,     8,     9,    74,    10,    79,    80,    11,
      12,    13,    14,    15,    83,    84,    24,    43
  };

  const signed char
  parser::yycheck_[] =
  {
       8,     3,    24,    25,    12,     0,    23,     9,    23,     3,
      23,    13,     3,    15,     5,     9,     3,    22,    22,     4,
      22,    23,    24,    25,    15,    10,     3,    35,    22,    23,
      24,    25,    23,    24,    25,     3,    23,    24,    25,    47,
      48,    12,     3,    22,    11,     3,    54,    24,    25,    11,
       3,    11,     4,    23,    62,    23,    24,    25,    10,    23,
      11,    69,    23,    24,    25,    23,    24,    25,    22,    77,
      23,    24,    25,    16,    17,    18,    19,    20,    21,    11,
      23,    22,    22,    26,    27,    28,    29,    30,    31,    16,
      17,    18,    19,    20,    21,    23,    23,    10,    10,    26,
      27,    28,    29,    30,    10,    10,     5,    18
  };

  const signed char
  parser::yystos_[] =
  {
       0,    33,    34,     0,    16,    17,    18,    19,    20,    21,
      23,    26,    27,    28,    29,    30,    31,    35,    36,    37,
      38,    42,    23,    39,    39,    23,     3,    23,    24,    25,
      40,    41,    41,    23,    12,     5,    15,    23,    41,    43,
      22,    22,    22,    35,    11,    24,    25,    11,    11,     9,
      22,    23,    41,    23,    11,    11,    23,    23,    41,    41,
      22,     9,    13,    15,    22,    23,    41,    44,    22,     4,
      10,    22,    23,    41,    23,    23,    41,     4,    10,    10,
      10,    23,    41,    10,    10
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    32,    33,    34,    34,    34,    35,    35,    35,    36,
      37,    37,    38,    38,    38,    38,    38,    38,    39,    39,
      40,    40,    40,    40,    41,    41,    41,    41,    42,    42,
      42,    42,    42,    43,    43,    43,    43,    43,    43,    43,
      43,    43,    44,    44,    44,    44,    44,    44,    44,    44,
      44
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     0,     2,     2,     0,     2,     1,     2,
       1,     1,     2,     2,     2,     2,     2,     4,     1,     3,
       3,     3,     1,     1,     1,     2,     1,     2,     1,     2,
       2,     4,     4,     1,     1,     2,     2,     2,     2,     4,
       6,     6,     2,     2,     2,     1,     1,     1,     3,     5,
       5
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "YYEOF", "error", "$undefined", "\"-\"", "\"+\"", "\"*\"", "\"/\"",
  "\"(\"", "\")\"", "\"[\"", "\"]\"", "\",\"", "\":\"", "\"$\"", "\"#\"",
  "\"%\"", "GLOBAL", "EXTERN", "SECTION", "WORD", "SKIP", "EQU", "REG",
  "SYMBOL", "NUMBER", "HEX", "MNM0", "MNM1OP", "MNM1REG", "MNM2REGOP",
  "MNM2REGREG", "COMMENT", "$accept", "code", "lines", "line", "label",
  "expression", "directive", "symbols", "initializers", "literal",
  "instruction", "operand_jmp", "operand", YY_NULLPTR
  };

#if YYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,    84,    84,    88,    89,    92,    97,    98,   101,   108,
     114,   117,   123,   128,   136,   145,   151,   160,   173,   180,
     191,   198,   205,   212,   222,   225,   228,   231,   236,   242,
     248,   270,   277,   288,   297,   306,   317,   326,   335,   341,
     347,   357,   371,   380,   390,   401,   410,   419,   425,   431,
     441
  };

  // Print the state stack on the debug stream.
  void
  parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  parser::yy_reduce_print_ (int yyrule)
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


} // yy
#line 1811 "parser.cpp"

#line 454 "../src/parser.y"


void yy::parser::error (const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
};

