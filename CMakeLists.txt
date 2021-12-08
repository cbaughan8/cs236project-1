cmake_minimum_required(VERSION 3.15)
project(project-1)

set(CMAKE_CXX_STANDARD 17)

add_executable(project-1 main.cpp Automaton.h ColonAutomaton.cpp ColonAutomaton.h ColonDashAutomaton.cpp ColonDashAutomaton.h Lexer.cpp Lexer.h Token.cpp Token.h CommaAutomaton.h CommaAutomaton.cpp PeriodAutomaton.h PeriodAutomaton.cpp Q_MarkAutomaton.h Q_MarkAutomaton.cpp Left_ParenAutomaton.h Left_ParenAutomaton.cpp Right_ParenAutomaton.h Right_ParenAutomaton.cpp AddAutomaton.h AddAutomaton.cpp MultiplyAutomaton.h MultiplyAutomaton.cpp UndefinedAutomaton.h UndefinedAutomaton.cpp IDAutomaton.h IDAutomaton.cpp StringAutomaton.h StringAutomaton.cpp CommentAutomaton.h CommentAutomaton.cpp SchemesAutomaton.h SchemesAutomaton.cpp FactsAutomaton.h FactsAutomaton.cpp RulesAutomaton.h RulesAutomaton.cpp QueriesAutomaton.h QueriesAutomaton.cpp EOFAutomaton.h EOFAutomaton.cpp Parser.h Parser.cpp ParserHelper.h ParserHelper.cpp DatalogProgram.h DatalogProgram.cpp Predicates.h Predicates.cpp Rules.h Rules.cpp Parameters.h Parameters.cpp Tuple.h Tuple.cpp Database.cpp Database.h Relation.cpp Relation.h Header.cpp Header.h Interpreter.cpp Interpreter.h Graph.cpp Graph.h)
file(COPY resources DESTINATION ${CMAKE_BINARY_DIR})
file(COPY Lab1PassOffCases DESTINATION ${CMAKE_BINARY_DIR})
file(COPY Lab2PassOffCases DESTINATION ${CMAKE_BINARY_DIR})
file(COPY Lab3PassOffCases DESTINATION ${CMAKE_BINARY_DIR})